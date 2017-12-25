/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo servoBottom;
Servo servoTop;

int pos = 0;

const int xLeft = 90;
const int xRight = 160;
const int yTop = 70;
const int yBottom = 100;

const int delayTime = 500;

void setup() {
  servoBottom.attach(3);
  servoTop.attach(5);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);

//  slowRectangle(15, 0, 0);
  drawRectangle(HIGH);
}


void loop(){
  drawRectangle(HIGH);
  }

void drawRectangle(int laserStatus) {
  digitalWrite(9, laserStatus);
  servoBottom.write(xLeft);
  servoTop.write(yBottom);
  
  delay(delayTime);

  servoBottom.write(xLeft);
  servoTop.write(yTop);

  delay(delayTime);
  
  servoBottom.write(xRight);
  servoTop.write(yTop);
  
  delay(delayTime);

  servoBottom.write(xRight);
  servoTop.write(yBottom);

  delay(delayTime);
}

void slowRectangle(int delayTime, int xStart, int yStart) {
    //start position
    servoBottom.write(xStart);
    servoTop.write(yStart);
    delay(1000);

    //go to top left
    for(pos = xStart; pos <= xLeft; pos++) {
      servoBottom.write(pos);
      delay(delayTime);
    }
    //go to top left
    for(pos = yStart; pos <= yTop; pos++) {
      servoTop.write(pos);
      delay(delayTime);
    }


    //go to top right
    for(pos = xLeft; pos <= xRight; pos++) {
      servoBottom.write(pos);
      delay(delayTime);
    }
    //go to top right
    for(pos = yTop; pos <= yTop; pos++) {
      servoTop.write(pos);
      delay(delayTime);
    }
}

