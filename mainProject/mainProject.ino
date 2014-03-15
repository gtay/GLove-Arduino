// This is a test for using the digital and analog pressure sensors for our project.
//
// Usage: Connect a phone to the bluetooth module.
//        If you have our GLove android app, then you'll be able to call by sending data 
//        through the pressure sensors.

// initialize the library with the numbers of the interface pins

#include <SoftwareSerial.h>

// Defined mappings on the multiplexer inputs.
#define preshReadPin_0 0
#define preshReadPin_1 1
#define preshReadPin_2 2
#define preshReadPin_3 3
#define preshReadPin_4 4
#define preshReadPin_5 5
#define preshReadPin_6 6
#define preshReadPin_7 7
#define preshReadPin_8 8
#define preshReadPin_9 9
#define preshReadPin_MODE 10
#define preshReadPin_SEND_CALL 11
#define preshReadPin_BACKSPACE_END 12

// Array of the sensor data for multiplexed inputs.
int sensorArray[16];

// The analog input pin for the multiplexer
#define multiRead A0
// The digital pins used to select the line for the multiplexer
#define multiSelectPin_0 2  // Most significant
#define multiSelectPin_1 3
#define multiSelectPin_2 4
#define multiSelectPin_3 5  // Least significant

// The threshold for Analog Data
int preshAnalogThresh = 500;

// The digital pin for the led
#define boardled 13

// Character Tracking Variables
#define NO_INPUT_CHAR 'W'
#define MODE_CHAR 'X'
#define SEND_CALL_CHAR 'Y'
#define BACKSPACE_END_CHAR 'Z'

char lastCharRead = NO_INPUT_CHAR;
char currCharRead = NO_INPUT_CHAR;

// Temporary Variables (Replace these later!)
int numblinks = 0;

void setup() {
  // set up the LCD's number of columns and rows: 
  pinMode(boardled, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {

  readMultiplexedInputs();
  
  // DEBUG: data reads from pressure inputs.
  //printPressureReads();

  // Translate the reading to a character.
  // This is where the character priorities are defined.
  if (sensorArray[preshReadPin_MODE] > preshAnalogThresh) {
    currCharRead = MODE_CHAR; // MODE Switch
  } else if (sensorArray[preshReadPin_0] > preshAnalogThresh) {
    currCharRead = '0';
  } else if (sensorArray[preshReadPin_1] > preshAnalogThresh) {
    currCharRead = '1';    
  } else if (sensorArray[preshReadPin_2] > preshAnalogThresh) {
    currCharRead = '2';    
  } else if (sensorArray[preshReadPin_3] > preshAnalogThresh) {
    currCharRead = '3';    
  } else if (sensorArray[preshReadPin_4] > preshAnalogThresh) {
    currCharRead = '4';    
  } else if (sensorArray[preshReadPin_5] > preshAnalogThresh) {
    currCharRead = '5';    
  } else if (sensorArray[preshReadPin_6] > preshAnalogThresh) {
    currCharRead = '6';    
  } else if (sensorArray[preshReadPin_7] > preshAnalogThresh) {
    currCharRead = '7';    
  } else if (sensorArray[preshReadPin_8] > preshAnalogThresh) {
    currCharRead = '8';    
  } else if (sensorArray[preshReadPin_9] > preshAnalogThresh) {
    currCharRead = '9';    
  } else if (sensorArray[preshReadPin_SEND_CALL] > preshAnalogThresh) {
    currCharRead = SEND_CALL_CHAR; // CALL
  } else if (sensorArray[preshReadPin_BACKSPACE_END] > preshAnalogThresh) {
    currCharRead = BACKSPACE_END_CHAR;    
  } else {
    currCharRead = NO_INPUT_CHAR;
  }
  
  // If we detect a character change.
  if (currCharRead != lastCharRead) {
    /*
    Serial.print("State Change = ");
    Serial.print(currCharRead);
    Serial.print("\n");
    */
    
    if ( currCharRead != NO_INPUT_CHAR) {
      Serial.write(currCharRead);
      Serial.write("\n");
      //Serial.print(currCharRead);
      //Serial.print("\n");
      // Indicates a character change
      blink(1, 500);
    }

    lastCharRead = currCharRead;
  }
  
  delay(10);
}

int readMultiplexedInputs() {
  int currentInput = 0;
  
  // BEWARE THE INDENTATION IS MISLEADING HERE FOR READABILITY.  
  // Countdown Optimization
  for(int select_0 = 1; select_0 == 0; select_0--){
    if (select_0 == 1) { digitalWrite(multiSelectPin_0, LOW);}
    else {               digitalWrite(multiSelectPin_0, HIGH);}
  for(int select_1 = 1; select_1 == 0; select_1--){
    if (select_1 == 1) { digitalWrite(multiSelectPin_1, LOW);}
    else {               digitalWrite(multiSelectPin_1, HIGH);}    
  for(int select_2 = 1; select_2 == 0; select_2--){
    if (select_2 == 1) { digitalWrite(multiSelectPin_2, LOW);}
    else {               digitalWrite(multiSelectPin_2, HIGH);}
  for(int select_3 = 1; select_3 == 0; select_3--){
    if (select_3 == 1) { digitalWrite(multiSelectPin_3, LOW);}
    else {               digitalWrite(multiSelectPin_3, HIGH);}
    // MAIN READ LOOP
    
    sensorArray[currentInput] = analogRead(multiReadPin);

    currentInput++;
  }}}}  
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
