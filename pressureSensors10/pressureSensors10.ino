// This is a test for using the digital and analog pressure sensors for our project.
//
// Usage: If you squeeze the pressure sensor, pin13 LED should blink a certain number of times.

// initialize the library with the numbers of the interface pins
int preshAnalog0 = 0;
int preshAnalog0Read;

int preshAnalog1 = 1;
int preshAnalog1Read;

int preshAnalog2 = 2;
int preshAnalog2Read;

int preshAnalog3 = 3;
int preshAnalog3Read;

int preshAnalog4 = 4;
int preshAnalog4Read;

int preshDigi2 = 2;
int preshDigi2Read;

int preshDigi3 = 3;
int preshDigi3Read;

int preshDigi4 = 4;
int preshDigi4Read;

int preshDigi5 = 5;
int preshDigi5Read;

int preshDigi6 = 6;
int preshDigi6Read;

// The threshold for Analog Data
int preshAnalogThresh = 500;

// The digital pin for the led
int boardled = 13;

// Character Tracking Variables
char defaultChar = 'Z';
char lastCharRead = defaultChar;
char currCharRead = defaultChar;

// Temporary Variables (Replace these later!)
int numblinks = 0;

void setup() {
  // set up the LCD's number of columns and rows: 
  pinMode(boardled, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  preshAnalog0Read = analogRead(preshAnalog0);
  preshAnalog1Read = analogRead(preshAnalog1);
  preshAnalog2Read = analogRead(preshAnalog2);
  preshAnalog3Read = analogRead(preshAnalog3);
  preshAnalog4Read = analogRead(preshAnalog4);

  preshDigi2Read = digitalRead(preshDigi2);
  preshDigi3Read = digitalRead(preshDigi3);
  preshDigi4Read = digitalRead(preshDigi4);
  preshDigi5Read = digitalRead(preshDigi5);
  preshDigi6Read = digitalRead(preshDigi6);

  printAnalogReads();

  // Translate the reading to a character.
  if (preshAnalog0Read > preshAnalogThresh) {
    currCharRead = '0';
  } else if (preshAnalog1Read > preshAnalogThresh) {
    currCharRead = '1';    
  } else if (preshAnalog2Read > preshAnalogThresh) {
    currCharRead = '2';    
  } else if (preshAnalog3Read > preshAnalogThresh) {
    currCharRead = '3';    
  } else if (preshAnalog4Read > preshAnalogThresh) {
    currCharRead = '4';    
  } else if (preshDigi6Read == HIGH) {
    currCharRead = '5';    
  } else if (preshDigi5Read == HIGH) {
    currCharRead = '6';    
  } else if (preshDigi4Read == HIGH) {
    currCharRead = '7';    
  } else if (preshDigi3Read == HIGH) {
    currCharRead = '8';    
  } else if (preshDigi2Read == HIGH) {
    currCharRead = '9';    
  } else {
    currCharRead = 'Z';
  }
  
  // If we detect a character change.
  if (currCharRead != lastCharRead) {
    Serial.print("State Change = ");
    Serial.print(currCharRead);
    Serial.print("\n");

    switch (currCharRead) {
      case '0':
        numblinks = 0;
        break;
      case '1':
        numblinks = 1;
        break;
      case '2':
        numblinks = 2;
        break;
      case '3':
        numblinks = 3;
        break;
      case '4':
        numblinks = 4;
        break;
      case '5':
        numblinks = 5;
        break;
      case '6':
        numblinks = 6;
        break;
      case '7':
        numblinks = 7;
        break;
      case '8':
        numblinks = 8;
        break;
      case '9':
        numblinks = 9;
        break;        
      case 'Z': // Default Character
        numblinks = 0;
        break;        
      default:
        numblinks = 0;
        Serial.print("Unknown Char Detected: ");        
        Serial.print(currCharRead);
        Serial.print("\n");
    }
    
    blink(numblinks);

    lastCharRead = currCharRead;
  }
  
  delay(10);
}

void blink(int numBlinks) {
  while (numBlinks > 0){
    digitalWrite(boardled, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);
    digitalWrite(boardled, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(50);
    numBlinks--;
  }
}

void printAnalogReads() {
  Serial.print(preshAnalog0Read);
  Serial.print(", ");
  Serial.print(preshAnalog1Read);
  Serial.print(", ");
  Serial.print(preshAnalog2Read);
  Serial.print(", ");
  Serial.print(preshAnalog3Read);
  Serial.print(", ");
  Serial.print(preshAnalog4Read);
  Serial.print("\n");
}
