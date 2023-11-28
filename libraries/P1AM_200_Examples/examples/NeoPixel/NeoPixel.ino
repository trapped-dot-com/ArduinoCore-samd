/*
	Example: NeoPixel
  Library Dependancy: Adafruit NeoPixel

	This example shows a use for the neopixel and is compatible with any P1 analog module.
	The neopixel is mapped to the analog's input signal. The neopixel will show red for a low value,
	amber for medium value, and green for a high value.

	This example works with all P1000 Series:
	 - Analog input modules such as P1-04ADL-1, P1-04ADL-2,etc.
	 - Analog combo modules such as P1-4ADL2DAL-1, P1-4ADL2DAL-2 etc.  
	 _____  _____ 
	|  P  ||  S  |
	|  1  ||  L  |
	|  A  ||  O  |
	|  M  ||  T  |
	|  -  ||     |
	|  2  ||  0  |
	|  0  ||  1  |
	|  0  ||     |
	 ¯¯¯¯¯  ¯¯¯¯¯ 
	Written by FACTS Engineering
	Copyright (c) 2023 FACTS Engineering, LLC
	Licensed under the MIT license.
*/
#include <P1AM.h>
#include <Adafruit_NeoPixel.h>

const int inputHigh = 8191;  //Analog Input's High Range
const int inputLow = 0;      //Analog Input's Low Range
const int pixelHigh = 255;      //Pixel Color High Range
const int pixelLow = 0;         //Pixel Color Low Range

int inputCounts = 0;            //Reading in Counts 
int pixelValue = 0;             //Pixel color value

//P1AM-200's pixel type is NEO_GRB + NEO_KHZ800
Adafruit_NeoPixel neoPixel(1, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

channelLabel analogSignal = {1,2};   //Input signal that is channel 2 of our analog module in slot 1

void setup(){

  Serial.begin(115200);         //initialize serial communication at 115200 bits per second
  while (!P1.init()){ 
    ;                           //Wait for Modules to Sign on   
  }
  neoPixel.begin();             //Start the NeoPixel object
  neoPixel.clear();             //Set NeoPixel color to black (0,0,0)
  neoPixel.setBrightness(30);   //Set BRIGHTNESS (max = 255)
  neoPixel.show();              //Update the pixel state
}

void loop(){  //the loop routine runs over and over again forever

  inputCounts = P1.readAnalog(analogSignal);  //Reads analog data from slot 1 channel 2 of the analog input module 
  pixelValue = map(inputCounts, inputLow, inputHigh, pixelLow, pixelHigh);  //Map the pixel color to analog data
  setNeoPixel(pixelValue);
  
}

void setNeoPixel (int g){
  int pixelNumber = 0;
  int r = pixelHigh - g;
  int b = 0;
  neoPixel.setPixelColor(pixelNumber, neoPixel.Color(r,g,b)); //Set pixel color
  neoPixel.show();  //Update pixel state
}