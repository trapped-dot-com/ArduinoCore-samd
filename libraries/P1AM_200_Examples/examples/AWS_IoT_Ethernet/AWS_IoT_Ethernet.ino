/*
  AWS IoT Ethernet

  This sketch securely connects to an AWS IoT using MQTT over Ethernet on the P1AM-200
  It uses a private key stored in the ATECC608A and a public
  certificate for SSL/TLS authetication.

  If you have not done so, generate a CSR following the example File>Examples>ArduinoECCX08>ECCX08CSR 

  It publishes a message every 5 seconds to arduino/outgoing
  topic and subscribes to messages on the arduino/incoming
  topic.

  The circuit:
  - P1AM-200
  - P1AM-ETH

  This example was based on the tutorial below by Arduino. The tutorial on Arduino Project Hub can be used
  to setup your AWS account and the MKR board:

 https://docs.arduino.cc/tutorials/mkr-wifi-1010/securely-connecting-an-arduino-mkr-wifi-1010-to-aws-iot-core

  This example code is in the public domain.

    Troubleshooting tips:
     - Make sure you have generated a CSR and follow the certificate process on AWS. 
     The certificate from AWS will be used in the arduino_secrets.h file, not the CSR.
     - Check that the certificate is "Active" in AWS. If it is "Inactive" you will need 
     to activate it by clicking the "Actions" button and selecting "Activate".
     - Check that your endpoint is correct in the arduino_secrets.h file. The endpoint
    can be found in the AWS console under "Settings" for your thing.
    - Check that your certificate has a policy attached to it. For testing purposes you
    can set "Policy Action" to "*" to allow all actions and the "Policy Resource" to "*"
    to allow all resources. 


  Example modified by FACTS Engineering for use with P1AM-200
*/

#include <ArduinoBearSSL.h>
#include <ArduinoECCX08.h>
#include <ArduinoMqttClient.h>
#include <Ethernet.h>
#include <EEPROM.h> // FACTS Engineering AT24MAC_EEPROM Library https://github.com/facts-engineering/AT24MAC_EEPROM/
#include <PCF8563.h> // FACTS Engineering PCF8563 RTC Library https://github.com/facts-engineering/PCF8563_RTC
#include <NTPClient.h> // Arduino NTP Client https://github.com/arduino-libraries/NTPClient
#include "arduino_secrets.h"
#include <P1AM.h>
/////// Enter your sensitive data in arduino_secrets.h
const char broker[]      = SECRET_BROKER;
const char* certificate  = SECRET_CERTIFICATE;

EthernetClient    ethernetClient;            // Used for the TCP socket connection
BearSSLClient sslClient(ethernetClient); // Used for SSL/TLS connection, integrates with ECC508
MqttClient    mqttClient(sslClient);

EthernetUDP udp;
NTPClient timeClient(udp);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  delay(1000);
  Serial.println("AWS IoT Ethernet");

  if (!ECCX08.begin()) {
    Serial.println("No ECCX08 present!");
    while (1);
  }

  pinMode(SWITCH_BUILTIN, INPUT);

  connectEthernet();
  timeClient.begin();
  syncTime();

  // Set a callback to get the current time
  // used to validate the servers certificate
  ArduinoBearSSL.onGetTime(getTime);

  // Set the ECCX08 slot to use for the private key
  // and the accompanying public certificate for it
  sslClient.setEccSlot(0, certificate);

  // Optional, set the client id used for MQTT,
  // each device that is connected to the broker
  // must have a unique client id. The MQTTClient will generate
  // a client id for you based on the millis() value if not set
  //
  // mqttClient.setId("clientId");

  // Set the message callback, this function is
  // called when the MQTTClient receives a message
  mqttClient.onMessage(onMessageReceived);
}

void loop() {

  static unsigned long lastMillis = 0;

  if (!mqttClient.connected()) {
    // MQTT client is disconnected, connect
    connectMQTT();
  }

  // poll for new MQTT messages and send keep alives
  mqttClient.poll();

  // publish a message roughly every 5 seconds.
  if (millis() - lastMillis > 5000) {
    lastMillis = millis();

    publishMessage();
  }
}

void publishMessage() {
  Serial.println("Publishing message");

  // send message, the Print interface can be used to set the message contents
  mqttClient.beginMessage("arduino/outgoing");
  mqttClient.print("Switch is ");
  if (digitalRead(SWITCH_BUILTIN)){
    mqttClient.print("ON @ ");
  }
  else{
    mqttClient.print("OFF @ ");
  }
  mqttClient.print(timeClient.getFormattedTime());
  mqttClient.endMessage();
}

void onMessageReceived(int messageSize) {
  // we received a message, print out the topic and contents
  Serial.print("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    Serial.print((char)mqttClient.read());
  }
  Serial.println();
  Serial.println();
}


unsigned long getTime() {
  return PCF8563_RTC.getEpoch(); // get the current time from the RTC module 
}

void connectEthernet() {

  uint8_t mac[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };   //array to store mac address
  EEPROM.readMacAddress(mac); // Get MAC address from on-board EEPROM
  Ethernet.init(5);   // P1AM-ETH shield
  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
  }
  else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  
}

void connectMQTT() {
  Serial.print("Attempting to MQTT broker: ");
  Serial.print(broker);
  Serial.println(" ");

  while (!mqttClient.connect(broker, 8883)) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }
  Serial.println();

  Serial.println("You're connected to the MQTT broker");
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe("arduino/incoming");
}



void syncTime() {
  timeClient.update(); // Update time from NTP server
  PCF8563_RTC.setEpoch(timeClient.getEpochTime()); // Update RTC
}

