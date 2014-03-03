// This is a test for analog reading the pressure sensors for our project.
// The pressure sensor is a really high resistance resistor when untouched.
// As pressure is applied, the resistance decreases.
//
// Circuit: +5V -> Pressure Sensor -> 10kOm resistor -> GND
//                                 -> Analog In 0
// Analog In reads the voltage difference across the resistor. 
// If you use a 10 KOm, the range of values goes from 0 -> 700
//
// Usage: If you squeeze the pressure sensor, pin13 LED should light up.

// initialize the library with the numbers of the interface pins
int fsr0 = 0;
int fsr0Read;

int fsrThresh = 500;
int boardled = 13;

int lastCharRead = '0';
int currCharRead = '0';

void setup() {
  // set up the LCD's number of columns and rows: 
  pinMode(boardled, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  fsr0Read = analogRead(fsr0);
  
  Serial.print("Analog reading = ");
  Serial.print(fsr0Read);
  Serial.print("\n" );

  // Translate the reading to a character.
  if (fsr0Read > fsrThresh) {
    currCharRead = '1';
  } else {
    currCharRead = '0';
  }
  
  // If we detect a character change.
  if (currCharRead != lastCharRead) {
    Serial.print("State Change = ");
    Serial.print(currCharRead);
    Serial.print("\n");
    if (currCharRead == '1') { // If we changed to on, blink once
       blink();
    }
    else if (currCharRead == '0') { // If we changed to off, blink twice
       blink(); blink();
    }
    lastCharRead = currCharRead;
  }
  
  delay(10);
}

void blink() {
  digitalWrite(boardled, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);
  digitalWrite(boardled, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(50);
}
