// This is a test for using the digital and analog pressure sensors for our project.
//
// Usage: Connect a phone to the bluetooth module.
//        If you have our GLove android app, then you'll be able to call by sending data 
//        through the pressure sensors.

// initialize the library with the numbers of the interface pins



//// Sensors
// Define the mappings in the sensor array
// ***NOTE IF YOU CHANGE THESE, CHANGE readSensorInputs() accordingly.
#define preshReadPin_0 A2
#define preshReadPin_1 A4
#define preshReadPin_2 A5
#define preshReadPin_3 A6
#define preshReadPin_4 A7
#define preshReadPin_MODE A0
#define preshReadPin_SEND_CALL A1
#define preshReadPin_BACKSPACE_END A3

#define preshReadPin_5 2
#define preshReadPin_6 3
#define preshReadPin_7 4
#define preshReadPin_8 5
#define preshReadPin_9 6

// Array of the sensor data for multiplexed inputs.
int sensorArray[13];

// The threshold for Analog Data
int preshAnalogThresh = 200;

//// LCD Control
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define LCD_BUFFER_SIZE 84

// Liquid Crystal display: 
//char lcdBuffer[LCD_BUFFER_SIZE]; // 14 x 6
String lcdData;

Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 9, 10, 8);

/* 
Pin Mappings:
Adafruit -> Arduino
1 VCC        VCC
2 GND        GND
3 SCE        D10
4 RST        D8
5 DC         D9
6 DN(MOSI)   D11
7 SCLK       D13
8 LED        VCC
*/

// Don't know what these do
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 48
#define LOGO16_GLCD_WIDTH  84


//// Configurable Parameters
// Character Tracking Variables
#define NO_INPUT_CHAR 'E'
#define MODE_CHAR 'M'
#define SEND_CALL_CHAR '#'
#define BACKSPACE_END_CHAR '*'

char lastCharRead = NO_INPUT_CHAR;
char currCharRead = NO_INPUT_CHAR;
int charCounter = 0;

#define LCD_DEBUG false

// DO NOT MAKE THESE EQUAL
#define MAX_COUNTER 1000
#define HOLD_THRESHOLD 50

// The digital pin for the led
#define boardled 13


/////// Temporary Variables (Replace these later!)
int numblinks = 0;
// WATCH OUT: This depends on cycle delay. It's not in seconds or ms.
boolean holdMessageSent = false;

int currBufferIndex = 0;

void setup() {
  // The board LED will not work while the LCD is in use because it's SCLK
  pinMode(boardled, OUTPUT);
  
  pinMode(preshReadPin_8, INPUT);
  pinMode(preshReadPin_9, INPUT);
  pinMode(preshReadPin_MODE, INPUT);
  pinMode(preshReadPin_SEND_CALL, INPUT);
  pinMode(preshReadPin_BACKSPACE_END, INPUT);  
   
  
  Serial.begin(9600);

  // Needs to happen after Serial.begin();  
  LCDsetup();
}

void loop() {

  readSensorInputs();
  
  // DEBUG: data reads from pressure inputs.
  //printPressureReads();

  parseSensorInputsAndSend();
  
  readSerialToLCD();

  delay(10);
}

void parseSensorInputsAndSend() {
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
      sendMessage(String(lastCharRead));
    }
    charCounter = 0;
  } 
  // Change Key Action
  else if (currCharRead != lastCharRead && currCharRead != NO_INPUT_CHAR) {
    charCounter = 0;
  }
  // Hold multiple keys Action
  else if (sensorArray[5] == HIGH && sensorArray[6] == HIGH && sensorArray[7] == HIGH) {
    //holdMessageSent = true;
  }
  // Key Hold Action
  else {  
    if (charCounter == HOLD_THRESHOLD && currCharRead != NO_INPUT_CHAR) {
      sendMessage(String(String('h') + String(lastCharRead)));
      //sendMessage(String(lastCharRead));
      holdMessageSent = true;
    }

    charCounter = charCounter + 1;
    // Accounts for overflow  
    charCounter = (charCounter < MAX_COUNTER) ? charCounter : MAX_COUNTER;
  } 
  lastCharRead = currCharRead;
     
  // Indicates if we have exceeded a hold threshold.
  if (charCounter > HOLD_THRESHOLD) {
    digitalWrite(boardled, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
    digitalWrite(boardled, LOW);  
  }
    
  if (currCharRead == NO_INPUT_CHAR) {
    holdMessageSent = false;
  }  
}



/*
void callModeLoop() {
    
}

void textModeLoop() {
  
}*/

void readSensorInputs() {
  sensorArray[0] = (analogRead(preshReadPin_0) > preshAnalogThresh) ? HIGH : LOW;
  sensorArray[1] = (analogRead(preshReadPin_1) > preshAnalogThresh) ? HIGH : LOW;
  sensorArray[2] = (analogRead(preshReadPin_2) > preshAnalogThresh) ? HIGH : LOW;
  sensorArray[3] = (analogRead(preshReadPin_3) > preshAnalogThresh) ? HIGH : LOW;
  sensorArray[4] = (analogRead(preshReadPin_4) > preshAnalogThresh) ? HIGH : LOW;
  sensorArray[10] = (analogRead(preshReadPin_MODE) > preshAnalogThresh) ? HIGH : LOW;
  sensorArray[11] = (analogRead(preshReadPin_SEND_CALL) > preshAnalogThresh) ? HIGH : LOW;
  sensorArray[12] = (analogRead(preshReadPin_BACKSPACE_END) > preshAnalogThresh) ? HIGH : LOW;

  sensorArray[5] = digitalRead(preshReadPin_5);
  sensorArray[6] = digitalRead(preshReadPin_6);
  sensorArray[7] = digitalRead(preshReadPin_7);
  sensorArray[8] = digitalRead(preshReadPin_8);
  sensorArray[9] = digitalRead(preshReadPin_9);
}

void sendMessage(String message) {
  Serial.println(message);
  
  if (LCD_DEBUG) {
    LCDprintToScreen(message);
  }
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

/*
void printPressureReads() {
  
}*/

// Be careful not to leave it on longer than you have to, else you will get pixel burn.
void LCDsetup() {  
  pinMode(boardled, INPUT);
  
  display.begin();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(50);

  display.display(); // show splashscreen
  delay(100);
  display.clearDisplay();   // clears the screen and buffer

  LCDprintToScreen("Welcome to GLove!");
}

// LCD Screen Control
void LCDprintToScreen(String lcdText)
{
  display.print(lcdText);
  display.display();
  delay(10);
  display.clearDisplay();
}

void readSerialToLCD() {  
  // send data only when you receive data:
  if (Serial.available() > 0) {

    // read the incoming byte:
    char incomingChar = Serial.read();  
    //sendMessage(String(incomingChar)); 

    if (incomingChar == 0) {
      lcdData += '\n';
    } else {
      lcdData += incomingChar;
    }

    currBufferIndex++;
    
    if (currBufferIndex >= LCD_BUFFER_SIZE || incomingChar == '\n') { 
      LCDprintToScreen(lcdData);
      lcdData = String("");
      currBufferIndex = 0;
    }
  }
}

// serialEvent
/*void serialEvent(){
//statements
}*/

