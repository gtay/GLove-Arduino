// This is a test for analog reading the pressure sensors for our project.
// The pressure sensor is a really high resistance resistor when untouched.
// As pressure is applied, the resistance decreases.
//
// Circuit: +5V -> Pressure Sensor -> 10kOm resistor -> GND
//                                 -> Digital Pin 2
// Analog In reads the voltage difference across the resistor. 
// If you use 20 kOm for the resistor it's pretty good.
//
// Usage: If you squeeze the pressure sensor, pin13 LED should light up.

// initialize the library with the numbers of the interface pins
int fsrin = 2;
int fsrRead;

int fsrThresh = 500;
int boardled = 13;

void setup() {
  // set up the LCD's number of columns and rows: 
  pinMode(boardled, OUTPUT);
  pinMode(fsrin, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  fsrRead = digitalRead(fsrin);
  
  Serial.print("Digital reading = ");
  Serial.print(fsrRead);
  Serial.print("\n" );

  // HIGH is set to > 3V
  if (fsrRead == HIGH) {
    digitalWrite(boardled, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
    digitalWrite(boardled, LOW);   // turn the LED on (HIGH is the voltage level)    
  }
  delay(10);
}
