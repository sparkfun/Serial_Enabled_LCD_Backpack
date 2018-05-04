/***********************************************************************
SerLCD Demo Example Code
Written by: Joel Bartlettv @ SparkFun Electronics
Date: December 20, 2012 
Modified by: Ho Yun "Bobby" Chan @ SparkFun Electronics 
date: May 3, 2018

This code uses the information presented in the SerLCD Datasheet 
to create an Arduino example using the SerLCD from SparkFun Electonics. 
Each of the SerLCD's capabilities is broken up into seperate functions
within the sketch. Simply call each function with the correct parameters 
to get the desired result form the LCD screen. 

This code was developed for the Arduino IDE v102

To use, connect the following pins
VDD -> 5V
GND -> GND
LCD RX -> Arduino TX (pin 11)

    ***Don't forget to disconnect the LCD's RX pin from the TX pin of 
the Arduino's UART line while programming!***

You can also check out the SerLCD library from Arduino 
http://playground.arduino.cc/Code/SerLCD

*If you need to reprogram often, or need the UART for another device,
you can use the Software Serial libary to create a 
seperate UART for the LCD.
Arduino IDE -> Skecth -> Import Library ->Software Serial

To declare a new UART using SoftwareSerial, insert this line:
SoftwareSerial NAME(x,y); // RX, TX
where Name is the name of the new UART, x is the RX pin, and y is the TX     pin.

"THE BEER-WARE LICENSE"
As long as you retain this notice you can do whatever you want with this     stuff. 
If we meet some day, and you think this stuff is worth it, you can buy me     a beer.
************************************************************************/
#include <SoftwareSerial.h>

SoftwareSerial LCD(10, 11); // Arduino SS_RX = pin 10 (unused), Arduino SS_TX = pin 11

//-------------------------------------------------------------------------------------------
void setup()
{
LCD.begin(9600);// all SerLCDs come at 9600 Baud by default
}
//-------------------------------------------------------------------------------------------
void loop()
{
  scrollingMarquee();
  tempAndHumidity();
  counter();
  backlight();
  cursors();
}
//-------------------------------------------------------------------------------------------
void clearScreen()
{
  //clears the screen, you will use this a lot!
  LCD.write(0xFE);
  LCD.write(0x01); 
}
//-------------------------------------------------------------------------------------------
void selectLineOne()
{ 
  //puts the cursor at line 0 char 0.
  LCD.write(0xFE); //command flag
  LCD.write(128); //position
}
//-------------------------------------------------------------------------------------------
void selectLineTwo()
{ 
  //puts the cursor at line 0 char 0.
  LCD.write(0xFE); //command flag
  LCD.write(192); //position
}
//-------------------------------------------------------------------------------------------
void moveCursorRightOne()
{
  //moves the cursor right one space
  LCD.write(0xFE); //command flag
  LCD.write(20); // 0x14
}
//-------------------------------------------------------------------------------------------
void moveCursorLeftOne()
{
  //moves the cursor left one space
  LCD.write(0xFE); //command flag
  LCD.write(16); // 0x10
}
//-------------------------------------------------------------------------------------------
void scrollRight()
{
  //same as moveCursorRightOne
  LCD.write(0xFE); //command flag
  LCD.write(20); // 0x14
}
//-------------------------------------------------------------------------------------------
void scrollLeft()
{
  //same as moveCursorLeftOne
  LCD.write(0xFE); //command flag
  LCD.write(24); // 0x18
}
//-------------------------------------------------------------------------------------------
void turnDisplayOff()
{
  //this tunrs the display off, but leaves the backlight on. 
  LCD.write(0xFE); //command flag
  LCD.write(8); // 0x08
}
//-------------------------------------------------------------------------------------------
void turnDisplayOn()
{
  //this turns the dispaly back ON
  LCD.write(0xFE); //command flag
  LCD.write(12); // 0x0C
}
//-------------------------------------------------------------------------------------------
void underlineCursorOn()
{
  //turns the underline cursor on
  LCD.write(0xFE); //command flag
  LCD.write(14); // 0x0E
}
//-------------------------------------------------------------------------------------------
void underlineCursorOff()
{
  //turns the underline cursor off
  LCD.write(0xFE); //command flag
  LCD.write(12); // 0x0C
}
//-------------------------------------------------------------------------------------------
void boxCursorOn()
{
  //this turns the box cursor on
  LCD.write(0xFE); //command flag
  LCD.write(13); // 0x0D
}
//-------------------------------------------------------------------------------------------
void boxCursorOff()
{
  //this turns the box cursor off
  LCD.write(0xFE); //command flag
  LCD.write(12); // 0x0C
}
//-------------------------------------------------------------------------------------------
void toggleSplash()
{
  //this toggles the spalsh screenif off send this to turn onif on send this to turn off
  LCD.write(0x7C); //command flag = 124 dec
  LCD.write(9); // 0x09
}
//-------------------------------------------------------------------------------------------
int backlight(int brightness)// 128 = OFF, 157 = Fully ON, everything inbetween = varied brightnbess 
{
  //this function takes an int between 128-157 and turns the backlight on accordingly
  LCD.write(0x7C); //NOTE THE DIFFERENT COMMAND FLAG = 124 dec
  LCD.write(brightness); // any value between 128 and 157 or 0x80 and 0x9D
}
//-------------------------------------------------------------------------------------------
void scrollingMarquee()
{
//This function scroll text across the screen on both lines
  clearScreen(); // it's always good to clear the screen before movonh onto a new print
  for(int j = 0; j < 17; j++)
  {
    selectLineOne();
    for(int i = 0; i < j;i++)
      moveCursorRightOne();
    LCD.print("SPARK");
    selectLineTwo();
    for(int i = 0; i < j;i++)
      moveCursorRightOne();
    LCD.print(" FUN");
    delay(500); // you must have a delay, otherwise the screen will print and clear before you can see the text
    clearScreen();
  }
}
//-------------------------------------------------------------------------------------------
void counter()
{
  //this function prints a simple counter that counts to 10
  clearScreen();
  for(int i = 0; i <= 10; i++)
  {
    LCD.print("Counter = ");
    LCD.print(i, DEC);
    delay(500);
        clearScreen();
  }
}
//-------------------------------------------------------------------------------------------
void tempAndHumidity()
{
  //this function shows how you could read the data from a temerature and humidity 
  //sensro and then print that data to the SerLCD.

  //these could be varaibles instead of static numbers 
  float tempF = 77.0; 
  float tempC = 25.0;
  float humidity = 67.0;

  clearScreen();
  selectLineOne();
  LCD.print(" Temp = ");
  LCD.print((long)tempF, DEC);
  LCD.print("F ");
  LCD.print((long)tempC, DEC);
  LCD.print("C");
  selectLineTwo();
  LCD.print(" Humidity = ");
  LCD.print((long)humidity, DEC); 
  LCD.print("%");
  delay(2500);
}
//-------------------------------------------------------------------------------------------
void backlight()
{
  //this function shows the different brightnesses to which the backlight can be set 
      clearScreen();
  for(int i = 128; i < 158; i+=2)// 128-157 are the levels from off to full brightness
  {
    backlight(i);
    delay(100);
    LCD.print("Backlight = ");
    LCD.print(i, DEC);
    delay(500);
    clearScreen();
  }
}
//-------------------------------------------------------------------------------------------
void cursors()
{
  //this function shows the different cursors avaiable on the SerLCD
  clearScreen();

  boxCursorOn();
  LCD.print("Box On");
  delay(1500);
  clearScreen();

  boxCursorOff();
  LCD.print("Box Off");
  delay(1000);
  clearScreen();

  underlineCursorOn();
  LCD.print("Underline On");
  delay(1500);
  clearScreen();

  underlineCursorOff();
  LCD.print("Underline Off");
  delay(1000);
  clearScreen();
}
