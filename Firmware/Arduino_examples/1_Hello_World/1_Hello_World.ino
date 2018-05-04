// SparkFun Serial LCD example 1
// Clear the display and say "Hello World!"

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
}

void loop()
{
  // move cursor to beginning of first line
  LCD.write(254); 
  LCD.write(128);

  // clear display by sending spaces
  LCD.write("                "); 
  LCD.write("                ");

 // move cursor to beginning of first line
  LCD.write(254); 
  LCD.write(128);

  LCD.write("Hello, world!");

  while(1); // wait forever
}
