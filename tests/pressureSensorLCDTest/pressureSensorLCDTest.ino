
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 11, 12);
int fsr1 = 0;
int fsr1Read;
int fsr2 = 1;
int fsr2Read;
int fsr3 = 2;
int fsr3Read;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("18-549 Team 10");
  Serial.begin(9600);
}

void loop() {
  fsr1Read = analogRead(fsr1);
  fsr2Read = analogRead(fsr2);
  fsr3Read = analogRead(fsr3);
  
  Serial.print("Analog reading = ");
  Serial.print(fsr1Read);
  Serial.print("," );
  Serial.print(fsr2Read);
  Serial.print("," );
  Serial.print(fsr3Read);
  
  lcd.setCursor(0, 1);
  if ((fsr1Read < 800) && (fsr2Read < 800) && (fsr3Read < 800)) {
    lcd.print("TOUCHING ALL");
  } else if (fsr1Read < 800) {
    lcd.print("top             ");
  } else if (fsr2Read < 800) {
    lcd.print("middle          ");
  } else if (fsr3Read < 800) {
    lcd.print("bottom          ");
  } else {
    lcd.print("");
  }
  delay(10);
}
