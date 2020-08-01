/*
  This code is based on the LiquidCrystal Library example code
  (described below), and a tutorial "Controlling an Arduino from Unity"
  by Darrenlloyd (http://r3dstar.co.uk/?p=211)
*/

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservoRL;
Servo myservoUD;
Servo myservoFB;
int posRL = 0;
int posUD = 0;
int posFB = 0;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char myColX[20];//holds x value from serial
char myColY[20];//holds y value from serial
char myColZ[20];//holds z value from serial
char Garbage[100];//holds unneeded characters

void setup() {
  Serial.begin (9600); 
  //attaching servos to digital pins 22, 23, 24
  //(for Arduino Mega - change the pin numbers
  //if your Arduino doesn't have those)
  myservoRL.attach(22);
  myservoUD.attach(23);
  myservoFB.attach(24);
  lcd.begin(16, 2);
}

void loop() {
  /*the input is of the format
    *.*x/*.*y/*.*z/n
    where * is any number of digits and possibly a "-", for example
    0.1567x/-0.13y/1.664z/n
    gives coordinates (0.1567, -0.13, 1.664)

    n means a new set of coordinates,
    / is added, because a value might have more
    charactes than a given table might hold,
    and then it would start assigning
    characters into the table holding
    the next coordinate
  */
  Serial.readBytesUntil('x', myColX, 20);
  Serial.readBytesUntil('/', Garbage, 100);
  Serial.readBytesUntil('y', myColY, 20);
  Serial.readBytesUntil('/', Garbage, 100);
  Serial.readBytesUntil('z', myColZ, 20);
  Serial.readBytesUntil('/', Garbage, 100);
  Serial.readBytesUntil('n', Garbage, 100);
  
  float x=0;
  float y=0;
  float z=0;

  if(myColX[0] == '-') {//three digit precision
    x = -(myColX[1]-'0') - 0.1*(myColX[3]-'0') - 0.01*(myColX[4]-'0') - 0.001*(myColX[5]-'0');
  }
  else
    x = (myColX[0]-'0') + 0.1*(myColX[2]-'0') + 0.01*(myColX[3]-'0') + 0.001*(myColX[4]-'0');

  if(myColY[0] == '-') {
    y = -(myColY[1]-'0') - 0.1*(myColY[3]-'0') - 0.01*(myColY[4]-'0') - 0.001*(myColY[5]-'0');
  }
  else
    y = (myColY[0]-'0') + 0.1*(myColY[2]-'0') + 0.01*(myColY[3]-'0') + 0.001*(myColY[4]-'0');

  if(myColZ[0] == '-') {
    z = -(myColZ[1]-'0') - 0.1*(myColZ[3]-'0') - 0.01*(myColZ[4]-'0') - 0.001*(myColZ[5]-'0');
  }
  else
    z = (myColZ[0]-'0') + 0.1*(myColZ[2]-'0') + 0.01*(myColZ[3]-'0') + 0.001*(myColZ[4]-'0');

      
  lcd.setCursor(0, 0);
  lcd.print(x);
  lcd.print(";");
  lcd.print(y);
  lcd.print(";");
  lcd.print("       ");
  lcd.setCursor(0, 1);
  lcd.print(z);
  lcd.print("         ");
      
      
  if(x < 0.2 && x > -0.2){//cut the range
    x+=0.2;//make sure the value is always positive and starting at 0
    posRL = x*120./0.4+30;//scale to give an angle between 30 and 150
  }
  if(y < 0.2 && y > -0.2){
    y+=0.2;
    posUD = y*120./0.4+30;
  }
  if(z < 2.4 && z > 1.7){
    z-=1.7;
    posFB = z*120./0.7+30;
  }
  
  myservoRL.write(posRL);
  myservoUD.write(posUD);
  myservoFB.write(posFB);

  //optional delay to better observe the numbers on the LCD screen
  //greater delay gives more noticeable errors in reading data from serial
  //delay(500);
}
