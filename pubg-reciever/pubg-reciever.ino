#include <VirtualWire.h>
// #include <Servo.h>
#include <ServoTimer2.h>  // the servo library


// default min is 544, max is 2400  


ServoTimer2 servoX;
ServoTimer2 servoY;

int pos = 0;

const int delayTime = 1000;
const int laserFlickerDelay = 100;

const int xMin = 1200; //tweak these values
const int xMax = 1900; //tweak these values
const int yMin = 1200; //tweak these values
const int yMax = 2000; //tweak these values

const int servoXPin = 5;
const int servoYPin = 3;
const int laserPin = 9;
const int RF_RX_PIN = 11;

void setup() {
  Serial.begin(9600);
  pinMode(laserPin, OUTPUT);
  vw_set_rx_pin(RF_RX_PIN);  // Setup receive pin.
  vw_setup(2000); // Transmission speed in bits per second.
  vw_rx_start(); // Start the PLL receiver.
  
  drawRectangle();
  // goToPoint(50, 50); //x, y, between 0 and 100. Works 0-0 is bottom-left, 100-100 is top-right
 
}


void loop(){
  String comdata = "";
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if(vw_get_message(buf, &buflen)) {
    int i;
    // Serial.print("Got: ");

    for(i = 0; i < buflen; ++i) {
      comdata += (char)buf[i];
    }
    // Serial.print(comdata);
    // Serial.println("");

    goToPoint(parseDataX(comdata), parseDataY(comdata));
  }
}

void goToPoint(int xpos, int ypos) {

  drawRectangle();

  attachServos();
  digitalWrite(laserPin, HIGH);


  servoX.write(xpos);
  servoY.write(ypos);

  delay(delayTime);
  detachServos(); 
}

void attachServos() {
  servoX.attach(servoXPin);
  servoY.attach(servoYPin);
}

void detachServos() {
  servoY.detach();
  servoX.detach();
}


// https://youtu.be/_P24em7Auq0?t=380
int parseDataX(String data) {
  // Serial.println("Parsing X");
  data.remove(data.indexOf("y"));
  data.remove(data.indexOf("x"), 1);
  return data.toInt();
}

int parseDataY(String data) {
  // Serial.println("Parsing Y");
  data.remove(0, data.indexOf("y") + 1);
  return data.toInt();
}

void drawRectangle() {
  digitalWrite(laserPin, HIGH);
  attachServos();

  int rectangleDelay = 200;

  //topleft
  servoX.write(map(25, 0, 100, xMin, xMax));
  servoY.write(map(75, 0, 100, xMin, xMax));
  delay(rectangleDelay);

  //topright
  servoX.write(map(75, 0, 100, xMin, xMax));
  servoY.write(map(75, 0, 100, xMin, xMax));
  delay(rectangleDelay);

  //bottomright
  servoX.write(map(75, 0, 100, xMin, xMax));
  servoY.write(map(25, 0, 100, xMin, xMax));
  delay(rectangleDelay);

  //bottomleft
  servoX.write(map(25, 0, 100, xMin, xMax));
  servoY.write(map(25, 0, 100, xMin, xMax));
  delay(rectangleDelay);

  flickerLaser(8);

  detachServos();
  digitalWrite(laserPin, LOW);

}

void flickerLaser(int times) {
  for (int i = 0; i < times; i ++) {
      digitalWrite(laserPin, HIGH);
      delay(laserFlickerDelay);
      digitalWrite(laserPin, LOW);
      delay(laserFlickerDelay);
  }
}