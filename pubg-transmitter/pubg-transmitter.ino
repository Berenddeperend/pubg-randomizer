
#include <VirtualWire.h>

const int RF_TX_PIN = 12;
const int piezoPin = 8;
const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;

//544 - 2400
const int xMin = 1200; //tweak these values
const int xMax = 1900; //tweak these values
const int yMin = 1200; //tweak these values
const int yMax = 2000; //tweak these values
const int delayTime = 1000; //tweak these values

const int notes[] = {262, 294, 330, 349};
const int musicDelay = 80;

int button1State;
int button2State;
int button3State;
int lastButton1State = LOW;
int lastButton2State = LOW;
int lastButton3State = LOW;
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;

unsigned long debounceDelay = 10;

unsigned long clock = 0; // use for RNG


void setup() {
  clock = millis();

  Serial.begin(19200);
  Serial.setTimeout(10); //Michael says this fixes a one second delay. Sure, we'll leave it in.
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  vw_set_tx_pin(RF_TX_PIN);
  vw_setup(2000); // Transmission speed in bits per second.

  tone(piezoPin, notes[0]);
  delay(musicDelay);
  tone(piezoPin, notes[1]);
  delay(musicDelay);
  tone(piezoPin, notes[3]);
  delay(musicDelay);
  tone(piezoPin, notes[4]);
  noTone(piezoPin);
}

unsigned char buffer[64]; // buffer array for data recieve over serial port
int count = 0;     // counter for buffer array 

void loop() {
  buttonStateLogger();
}

void clearBufferArray() {
  for (int i = 0; i < count; i++) {
    buffer[i] = NULL;
  }
}

void transmitMessage(String(input)) {
  const char *msg = input.c_str(); //convert input string to char array
  vw_send((uint8_t *)msg, strlen(msg));
}

void buttonStateLogger() {
  int reading1 = digitalRead(button1Pin);
  int reading2 = digitalRead(button2Pin);
  int reading3 = digitalRead(button3Pin);


  if (reading1 != lastButton1State) {
    lastDebounceTime1 = millis();
  }
  if (reading2 != lastButton2State) {
    lastDebounceTime2 = millis();
  }
  if (reading3 != lastButton3State) {
    lastDebounceTime3 = millis();
  }


 if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != button1State) {
      button1State = reading1;

      if (button1State == HIGH) {
        transmitMessage(buildPositionString(0, 0));
        Serial.println(buildPositionString(0, 0));
      }
    }
  }
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != button2State) {
      button2State = reading2;

      if (button2State == HIGH) {
        transmitMessage(buildPositionString(50, 50));
        Serial.println(buildPositionString(50, 50));
      }
    }
  }
  if ((millis() - lastDebounceTime3) > debounceDelay) {
    if (reading3 != button3State) {
      button3State = reading3;

      if (button3State == HIGH) {
        transmitMessage(generateRandomPosition());
        Serial.println(generateRandomPosition());
      }
    }
  }

  lastButton1State = reading1;
  lastButton2State = reading2;
  lastButton3State = reading3;
}

String buildPositionString(int xPos, int yPos){
  String mappedX = String(map(xPos, 0, 100, xMin, xMax));
  String mappedY = String(map(yPos, 0, 100, yMin, yMax));

  return String("x" + mappedX + "y" + mappedY);
}

String generateRandomPosition(){
  randomSeed(clock);
  Serial.println(clock);
  return buildPositionString(random(0, 100), random(0, 100));
}