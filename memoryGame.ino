#include <U8g2lib.h>
#include <String.h>
#include <Wire.h>
U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
long int number,num;
//String number = "";
String Num = "";
void setup() {
  Serial.begin(9600);
  u8g2.begin();
  randomSeed(analogRead(0));
  delay(1000);
  number = random(100000,999999);
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_t0_11_tf);
  u8g2.setCursor(12, 12);
  /************** Blinking Text **************/
  //u8g2.drawStr(0,24,"987654");
  u8g2.print(number);
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(500);
  u8g2.clearDisplay();
  delay(1000);u8g2.setFont(u8g2_font_t0_11_tf);
  u8g2.setCursor(12, 12);
  u8g2.print(number);
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(500);
  u8g2.clearDisplay();delay(1000);
  u8g2.setFont(u8g2_font_t0_11_tf);
  u8g2.setCursor(12, 12);
  u8g2.print(number);
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(500);
  u8g2.clearDisplay();delay(1000);
  /************** Blinking Text **************/
}

// fonts https://github.com/olikraus/u8g2/wiki/fntlistall#4-pixel-height

void loop()
{
  
  if(Serial.available())
  {
    Num = Serial.readStringUntil('\r');
    num = Num.toInt();
    if(num == number)
    {
      u8g2.drawStr(0, 24, "Success");
      u8g2.sendBuffer();          // transfer internal memory to the display
      delay(1000);
      u8g2.clearDisplay();
      //break;
    }
    else
    {
      u8g2.drawStr(0, 24, "Try Again");
      u8g2.sendBuffer();          // transfer internal memory to the display
      delay(1000);
      u8g2.clearDisplay();
      //break;
    }
  }
  
  
  
}
