
#include <VirtualWire.h>

const int RF_TX_PIN = 12;
const int piezoPin = 8;
const int button1Pin = 4;
const int button2Pin = 2;
const int button3Pin = 3;

//544 - 2400
const int xMin = 2400; //tweak these values, done
const int xMax = 544; //tweak these values
const int yMin = 2400; //tweak these values, done
const int yMax = 544; //tweak these values

const int notes[] = {262, 294, 330, 349};
const int musicDelay = 80;

int button1State;
int button2State;
int button3State;
int lastButton1State = HIGH;
int lastButton2State = HIGH;
int lastButton3State = HIGH;
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;

unsigned long debounceDelay = 10;

unsigned long clock = 0; // use for RNG


const int greenSpawnsLength = 6;
const int greenSpawns[6][2] = {
  {60, 48}, //ruins             //done
  {51, 51}, //pochinkiSchool    //done
  {48, 54}, //pochinkiFarm      //done
  {16, 45}, //myltaPrison       //done
  {21, 22}, //stalber           //done
  {80, 52}  //quarry            //done
};

const int redSpawnsLength = 12;
const int redSpawns[12][2] = {
  {80, 22}, //zharki          //done
  {60, 33}, //shootingRange   //DONE
  {50, 26}, //severny         //done
  {51 ,46}, //rozhok          //done
  {17, 38}, //mansion         //done
  {10, 35}, //lipovka         //done
  {10, 40}, //myltaPower      //done
  {19, 49}, //mylta           //done
  {75, 56}, //ferryPier       //DONE
  {82, 53}, //pirmorsk        //done
  {18, 53}, //novorepnoye     //done
  {26, 56}  //sosnovkaBaseMountain //done
};

const int blackSpawnsLength = 6;
const int blackSpawns[6][2] = {
  {76, 37}, //georgopol         //done
  {48, 49}, //school            //done
  {25, 36}, //yasnayaPolyana    //done
  {16, 42}, //prison            //done
  {60, 54}, //pochinki          //done
  {51, 60} //sosnovkaBase       //done
};



void setup() {
  Serial.begin(19200);
  Serial.setTimeout(10); //Michael says this fixes a one second delay. Sure, we'll leave it in.
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  vw_set_tx_pin(RF_TX_PIN);
  vw_setup(2000); // Transmission speed in bits per second.

  //play intro tune
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

      if (button1State == LOW) {

        // transmitMessage(buildPositionString(greenSpawns[0][0], greenSpawns[0][1]));
        // transmitMessage(buildPositionString(49, 54));
        transmitMessage(pickRandomPosition("green"));
      }
    }
  }
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != button2State) {
      button2State = reading2;

      if (button2State == LOW) {
        // transmitMessage(buildPositionString(48, 54));
        transmitMessage(pickRandomPosition("red"));
        // transmitMessage(buildPositionString(greenSpawns[1][0], greenSpawns[1][1]));
      }
    }
  }
  if ((millis() - lastDebounceTime3) > debounceDelay) {
    if (reading3 != button3State) {
      button3State = reading3;

      if (button3State == LOW) {
        // transmitMessage(buildPositionString(49, 53));
        transmitMessage(pickRandomPosition("black"));
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

// String pickPosition(int spawnsArray, int place) {
//   return buildPositionString(spawnsArray[place][0], spawnsArray[place][1]);
// }

String pickRandomPosition(String color){
  int clock = millis();
  randomSeed(clock);

  if(color == "green") {      
    int placeIndex = random(greenSpawnsLength);
    return buildPositionString(greenSpawns[placeIndex][0], greenSpawns[placeIndex][1]);
  }

  if(color == "red") {      
    int placeIndex = random(redSpawnsLength);
    return buildPositionString(redSpawns[placeIndex][0], redSpawns[placeIndex][1]);
  }
  
  if(color == "black") {      
    int placeIndex = random(blackSpawnsLength);
    return buildPositionString(blackSpawns[placeIndex][0], blackSpawns[placeIndex][1]);
  }

  // return buildPositionString(random(0, 100), random(0, 100));
}