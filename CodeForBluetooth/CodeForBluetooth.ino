#include <SoftwareSerial.h>

/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

char val;
int led = 13; //built in led

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  int normalBaud = 9600;
  Serial.begin(normalBaud);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  Serial.println("starting");
}

// the loop routine runs over and over again forever:
void loop() {
  //Serial.println(Serial.available());

  if(Serial.available()) {
    val = Serial.read();
    Serial.println(val);
  }
  if (val == '1' ) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW); 
  }
  
  Serial.write("hello\n");
  delay(400);
  
  /*
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  
  analogWrite(led, (255*(sensorValue - 300))/1024);
  delay(10);        // delay in between reads for stability
  /*/
}
