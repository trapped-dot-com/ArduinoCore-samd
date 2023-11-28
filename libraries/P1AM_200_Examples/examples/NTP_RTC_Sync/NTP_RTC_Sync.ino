/*
  Example: NTP_RTC_Sync

  This example gets the current time from an NTP server (pool.ntp.org).
  The ethernet connection is initialized using the CPUs unique MAC as read
  from its EEPROM.
  The RTC is set to the Unix time stamp read from the server.

  The current Unix time stamp is measured as seconds since January 1st, 1970 and can be
  found here. https://www.unixtimestamp.com/index.php

  This example uses an ethernet shield.

  created 4 Sep 2010
  by Michael Margolis
  modified 9 Apr 2012
  by Tom Igoe

  Modified by FACTS Engineering
*/

#include <Ethernet.h>
#include <EEPROM.h> // FACTS Engineering AT24MAC_EEPROM Library https://github.com/facts-engineering/AT24MAC_EEPROM/
#include <PCF8563.h> // FACTS Engineering PCF8563 RTC Library https://github.com/facts-engineering/PCF8563_RTC
#include <NTPClient.h> // Arduino NTP Client https://github.com/arduino-libraries/NTPClient

EthernetClient    ethernetClient;            // Used for the TCP socket connection

EthernetUDP udp;
NTPClient timeClient(udp);

static unsigned long lastMillis = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  delay(1000);

  connectEthernet();
  timeClient.begin();
  syncTime();
}

void loop() {


  // print epoch roughly every 5 seconds.
  if (millis() - lastMillis > 5000) {
    lastMillis = millis();
    Serial.print("Current epoch: ");
    Serial.println(PCF8563_RTC.getEpoch());
  }
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

void syncTime() {
  timeClient.update(); // Update time from NTP server
  PCF8563_RTC.setEpoch(timeClient.getEpochTime()); // Update RTC
}
