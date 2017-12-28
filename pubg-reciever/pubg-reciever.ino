#include <VirtualWire.h>
#include <Servo.h>


Servo servoBottom;
Servo servoTop;

int pos = 0;

const int xLeft = 90;
const int xRight = 160;
const int yTop = 70;
const int yBottom = 100;

const int delayTime = 1000;

const int servoBottomPin = 3;
const int servoTopPin = 5;
const int RF_RX_PIN = 11;

void setup() {
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);

  vw_set_rx_pin(RF_RX_PIN);  // Setup receive pin.
  vw_setup(2000); // Transmission speed in bits per second.
  vw_rx_start(); // Start the PLL receiver.
  
  drawRectangle(HIGH);
  drawRectangle(HIGH);
  drawRectangle(HIGH);
}


void loop(){
  String comdata = "";
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if(vw_get_message(buf, &buflen)) { // non-blocking I/O
  
    int i;
    // Message with a good checksum received, dump HEX
    Serial.print("Got: ");
   
    for(i = 0; i < buflen; ++i) {
      comdata += (char)buf[i];
      //Serial.print(" ");
	    //Serial.print(buf[i]);
    }
    Serial.print(comdata);
    Serial.println("");
  }
}

void goToPoint(int xpos, int ypos) {

}

void drawRectangle(int laserStatus) {
  digitalWrite(9, laserStatus);
  attachServos();


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

  detachServos();
}


void attachServos() {
  servoBottom.attach(servoBottomPin);
  servoTop.attach(servoTopPin);
}

void detachServos() {
  servoTop.detach();
  servoBottom.detach();
}