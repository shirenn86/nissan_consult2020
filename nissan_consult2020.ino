#include <Wire.h>                 //LCD
#include <LiquidCrystal_I2C.h>    //LCD

LiquidCrystal_I2C lcd(0x27, 16, 2);

// lcd is HD44780[16x2 line] + I2C connect GND and VCC(+5V)
// Lcd(SDA) -> sda pin (SDA)(A4)
// Lcd(SCL) -> scl pin (SCL)(A5)

int c = 0;
int e = 0;      //water temp

void setup() {
  Serial.begin( 9600 );

  lcd.backlight();                // Set Backlight
  lcd.init();                     //clear Screen
  lcd.setCursor(0, 0);            // Line 2
    delay (1000);
  lcd.print("Nissan Consult");           // Output on the LCD

  lcd.setCursor(3, 1);            // Line 2
  lcd.print("Water Temp");           // Output on the LCD


  pinMode(2, OUTPUT); digitalWrite(2, HIGH);  //+5v out

}


void loop() {

  if ( Serial.available() > 0 ) {
    c = Serial.read();
//    lcd.setCursor(0, 0);            // Line 0
//    lcd.print( c, HEX );
  }

  if (c == 0xff) {Serial.flush();}
  
    e = Serial.read();                //dummy
    e = Serial.read();
    
    e=e-50;
    if (e <= 0) {goto N10;}           //lower 0
    if (e >= 105) {goto N10;}         //upper 105
    lcd.setCursor(14, 1);
    lcd.print( e );
N10:

  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xef);
  Serial.write(0x5a);
  Serial.write(0x08);
  Serial.write(0xf0); 
  Serial.flush();
  delay(10);

}
