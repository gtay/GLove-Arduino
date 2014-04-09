// This is a test for using the digital and analog pressure sensors for our project.
//
// Usage: Connect a phone to the bluetooth module.
//        If you have our GLove android app, then you'll be able to call by sending data 
//        through the pressure sensors.

// initialize the library with the numbers of the interface pins

#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

// Define the mappings in the sensor array
#define preshReadPin_0 A0
#define preshReadPin_1 A1
#define preshReadPin_2 A2
#define preshReadPin_3 A3
#define preshReadPin_4 A4
#define preshReadPin_5 A5
#define preshReadPin_6 A6
#define preshReadPin_7 A7
#define preshReadPin_8 6
#define preshReadPin_9 5
#define preshReadPin_MODE 4
#define preshReadPin_SEND_CALL 3
#define preshReadPin_BACKSPACE_END 2

// Array of the sensor data for multiplexed inputs.
int sensorArray[13];

// The threshold for Analog Data
int preshAnalogThresh = 200;
// WATCH OUT: This depends on cycle delay. It's not in seconds or ms.
boolean holdMessageSent = false;

// The digital pin for the led
#define boardled 13

// Liquid Crystal display: 
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
char lcdBuffer[34]; // 16 + \n + 16 + \n

// Character Tracking Variables
#define NO_INPUT_CHAR 'W'
#define MODE_CHAR 'X'
#define SEND_CALL_CHAR 'Y'
#define BACKSPACE_END_CHAR 'Z'

char lastCharRead = NO_INPUT_CHAR;
char currCharRead = NO_INPUT_CHAR;
int charCounter = 0;

// DO NOT MAKE THESE EQUAL
#define MAX_COUNTER 1000
#define HOLD_THRESHOLD 50


// Temporary Variables (Replace these later!)
int numblinks = 0;

void setup() {
  // set up the LCD's number of columns and rows: 
  pinMode(boardled, OUTPUT);
  
  lcd.begin(16, 2);
  
  pinMode(preshReadPin_8, INPUT);
  pinMode(preshReadPin_9, INPUT);
  pinMode(preshReadPin_MODE, INPUT);
  pinMode(preshReadPin_SEND_CALL, INPUT);
  pinMode(preshReadPin_BACKSPACE_END, INPUT);  
  
  Serial.begin(9600);
}

void loop() {

  readInputs();
  
  // DEBUG: data reads from pressure inputs.
  //printPressureReads();

  // Translate the reading to a character.
  // This is where the character priorities are defined.
  if (sensorArray[10] == HIGH) {
    currCharRead = MODE_CHAR; // MODE Switch
  } else if (sensorArray[0] == HIGH) {
    currCharRead = '0';
  } else if (sensorArray[1] == HIGH) {
    currCharRead = '1';    
  } else if (sensorArray[2] == HIGH) {
    currCharRead = '2';    
  } else if (sensorArray[3] == HIGH) {
    currCharRead = '3';    
  } else if (sensorArray[4] == HIGH) {
    currCharRead = '4';    
  } else if (sensorArray[5] == HIGH) {
    currCharRead = '5';    
  } else if (sensorArray[6] == HIGH) {
    currCharRead = '6';    
  } else if (sensorArray[7] == HIGH) {
    currCharRead = '7';    
  } else if (sensorArray[8] == HIGH) {
    currCharRead = '8';    
  } else if (sensorArray[9] == HIGH) {
    currCharRead = '9';    
  } else if (sensorArray[11] == HIGH) {
    currCharRead = SEND_CALL_CHAR; // CALL
  } else if (sensorArray[12] == HIGH) {
    currCharRead = BACKSPACE_END_CHAR;    
  } else {
    currCharRead = NO_INPUT_CHAR;
  }

  // Key Down Action
  if (currCharRead != lastCharRead && lastCharRead == NO_INPUT_CHAR) {
    charCounter = 0;
  } 
  // Key Up Action
  else if (currCharRead != lastCharRead && currCharRead == NO_INPUT_CHAR) {
    if (!holdMessageSent) {
      Serial.println(lastCharRead);
    }
    charCounter = 0;
  } 
  // Change Key Action
  else if (currCharRead != lastCharRead && currCharRead == NO_INPUT_CHAR) {
    charCounter = 0;
  }
  // Hold multiple keys Action
  else if (sensorArray[5] == HIGH && sensorArray[6] == HIGH && sensorArray[7] == HIGH) {
    holdMessageSent = true;
  }
  // Key Hold Action
  else {  
    if (charCounter == HOLD_THRESHOLD && currCharRead != NO_INPUT_CHAR) {
      Serial.print("H");
      Serial.println(lastCharRead);
      holdMessageSent = true;
    }

    charCounter = charCounter + 1;
    // Accounts for overflow  
    charCounter = (charCounter < MAX_COUNTER) ? charCounter : MAX_COUNTER;
  } 
  lastCharRead = currCharRead;
  //Serial.println(charCounter);
   
  
  // Indicates if we have exceeded a hold threshold.
  if (charCounter > HOLD_THRESHOLD) {
    digitalWrite(boardled, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
    digitalWrite(boardled, LOW);  
  }
  
  
  
  if (currCharRead == NO_INPUT_CHAR) {
    holdMessageSent = false;
  }
  
  
  
  //updateLCD();
  delay(10);
}

/*
void callModeLoop() {
    
}

void textModeLoop() {
  
}*/

void updateLCD() {
  // Check how to print on both lines.
  lcd.print(lcdBuffer);
}

void readInputs() {
  sensorArray[0] = (analogRead(preshReadPin_0) > preshAnalogThresh) ? HIGH : LOW;
  sensorArray[1] = (analogRead(preshReadPin_1) > preshAnalogThresh) ? HIGH : LOW;
  sensorArray[2] = (analogRead(preshReadPin_2) > preshAnalogThresh) ? HIGH : LOW;
  sensorArray[3] = (analogRead(preshReadPin_3) > preshAnalogThresh) ? HIGH : LOW;
  sensorArray[4] = (analogRead(preshReadPin_4) > preshAnalogThresh) ? HIGH : LOW;
  sensorArray[5] = (analogRead(preshReadPin_5) > preshAnalogThresh) ? HIGH : LOW;
  sensorArray[6] = (analogRead(preshReadPin_6) > preshAnalogThresh) ? HIGH : LOW;
  sensorArray[7] = (analogRead(preshReadPin_7) > preshAnalogThresh) ? HIGH : LOW;

  sensorArray[8] = digitalRead(preshReadPin_8);
  sensorArray[9] = digitalRead(preshReadPin_9);
  sensorArray[10] = digitalRead(preshReadPin_MODE);
  sensorArray[11] = digitalRead(preshReadPin_SEND_CALL);
  sensorArray[12] = digitalRead(preshReadPin_BACKSPACE_END);
}

void blink(int numBlinks, int bDelay) {
  while (numBlinks > 0){
    digitalWrite(boardled, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(bDelay);
    digitalWrite(boardled, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(bDelay);
    numBlinks--;
  }
}

void printPressureReads() {
  
}
