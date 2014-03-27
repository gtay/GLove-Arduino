#include <SoftwareSerial.h>

static const int ITERATIONS = 200;
/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

char val;
int led = 13; //built in led
int numberOfTestLoops = ITERATIONS;
unsigned long times[ITERATIONS];
int startTime;
int endTime;
int done = 0;
String helloString = "43556";
int helloIndex = 0;

void loop() {
  if (numberOfTestLoops >= 0) {
    numberOfTestLoops--;
    startTime = millis();
    if (helloIndex == 5) {
      helloIndex = 0;
      Serial.write("0\n");
    }
    Serial.write(helloString[helloIndex]);
    Serial.write("\n");
    helloIndex++;
    while (Serial.available() == 0);
    // read the string
    char c;
    while (c != '\n') {
      if (Serial.available() > 0) {
        c = Serial.read();
      }
    }
    
    endTime = millis();
    times[numberOfTestLoops] = endTime - startTime;

  } else {
    if (done == 0) { // prevents the success message from showing every loop
      done = 1;
      Serial.write("Successful!\n");
      for (int i = ITERATIONS - 1; i >= 0; i--) {
        Serial.print(times[i]);
        Serial.print("\n");
      }
    }
  }
}

void setup() {
  int normalBaud = 9600;
  Serial.begin(normalBaud);
  Serial.write("0\n");
}
