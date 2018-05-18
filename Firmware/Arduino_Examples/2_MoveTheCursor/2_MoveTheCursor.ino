// SparkFun Serial LCD example 2
// Format and display fake RPM and temperature data

// This sketch is for Arduino versions 1.0 and later
// If you're using an Arduino version older than 1.0, use
// the other example code available on the tutorial page.

// Use the Software Serial library to create a new "soft" serial port
// for the display. This prevents display corruption when uploading code.
#include <SoftwareSerial.h>

// Attach the serial enabld LCD's RX line to digital pin 11
SoftwareSerial LCD(10, 11); // Arduino SS_RX = pin 10 (unused), Arduino SS_TX = pin 11

void setup()
{ 
  LCD.begin(9600); // set up serial port for 9600 baud
  delay(500); // wait for display to boot up

  // cursor to beginning of first line
  LCD.write(254); 
  LCD.write(128);

  // clear display + legends
  LCD.write("RPM:            "); 
  LCD.write("TEMP:           ");
} 

int temp, rpm;
char tempstring[10], rpmstring[10]; // create string arrays

void loop() 
{ 
  temp = random(1000); // make some fake data
  rpm = random(10000);

  sprintf(tempstring,"%4d",rpm); // create strings from the numbers
  sprintf(rpmstring,"%4d",temp); // right-justify to 4 spaces

  LCD.write(254); // cursor to 7th position on first line
  LCD.write(134);

  LCD.write(rpmstring); // write out the RPM value

  LCD.write(254); // cursor to 7th position on second line
  LCD.write(198);

  LCD.write(tempstring); // write out the TEMP value

  delay(1000); // short delay
}
