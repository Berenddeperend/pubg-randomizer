/* 
This is an attempted rewrite of the nodeport, with more complex movement functions.
*/

#include <math.h>

#include <Servo.h>

Servo servo;

int pos = 0;

const int xLeft = 90;
const int xRight = 160;
const int yTop = 70;
const int yBottom = 100;

const int servoClock = 15;

void setup() {
  servo.attach(3);
  // servo.write(0);

  Serial.begin(9600);
  // Serial.println("hello");

  servo.write(0);

  createMovementSequence(0, 150, 2000);
  // doWhileOverTime(, 20);
}


void loop(){

}

//this one should be done
int createMovementSequence(int start, int end, int duration) {
  const int stepNums = floor (duration / servoClock);
  int sequence[stepNums] = {start};
  const int stepSize = (end - start) / stepNums;
  int currentVal = start;

  for (int i = 0; i < stepNums ; i++) {
    currentVal = currentVal + stepSize;  
    sequence[i] = currentVal;
  }

  return sequence;

}

// void doWhileOverTime(void (*), intiterations) {
//   for (int i = 0; i < iterations; i ++) {
//     *
//   }
// }