
#include <VirtualWire.h>

const int RF_TX_PIN = 12;
const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;

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


void setup() {
  Serial.begin(19200);
  Serial.setTimeout(10); //Michael says this fixes a one second delay. Sure, we'll leave it in.
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  vw_set_tx_pin(RF_TX_PIN);
  vw_setup(2000); // Transmission speed in bits per second.
}

unsigned char buffer[64]; // buffer array for data recieve over serial port
int count = 0;     // counter for buffer array 

void loop() {
  buttonStateLogger();

  // if date is comming from softwareserial port ==> data is comming from gprs shield
  // if (Serial.available()) {
  //   Serial.println("dit is waar");

  //   while (Serial.available()) {
  //     buffer[count++] = Serial.read();
  //     if(count == 64) break;
  //   }

  //   vw_send(buffer, count);
  //   clearBufferArray();
  //   count = 0;
  // }    
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
         transmitMessage("button1");
      }
    }
  }
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != button2State) {
      button2State = reading2;

      if (button2State == HIGH) {
         transmitMessage("button2");
      }
    }
  }
  if ((millis() - lastDebounceTime3) > debounceDelay) {
    if (reading3 != button3State) {
      button3State = reading3;

      if (button3State == HIGH) {
        transmitMessage("button3");
      }
    }
  }

  lastButton1State = reading1;
  lastButton2State = reading2;
  lastButton3State = reading3;
}
