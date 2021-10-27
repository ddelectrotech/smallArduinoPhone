#include <Timer0.h>
#include <U8g2lib.h>
#include <Wire.h>
#define batValMax 14
#define sigValMax 4
Timer0 mytimer;
U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
int sigValue=0,batValue=0,value=0;
int flag=0,flag1=0;
void setup() {
  Serial.begin(9600);
  u8g2.begin();
  mytimer.Start(6);
  mytimer.attachInterruptT0(counter);
  delay(1000);
  startUp();
}

// fonts https://github.com/olikraus/u8g2/wiki/fntlistall#4-pixel-height

void loop()
{
  
  
  value = analogRead(A0);
  sigValue = value/250;
  batValue = value/100;
  if(sigValue<2)
    sigValue = 2;
  if(batValue<4)
    batValue = 4;
  showBatteryStatus(batValue);
  showSignalLines(sigValue);
  showClock();
  if(flag>=300)
  {
  u8g2.clearBuffer();flag=0;
  }
//  u8g2.clearBuffer();
//  u8g2.setBitmapMode(false /* solid */);
//  u8g2.setDrawColor(1);
//  //u8g2.drawXBM(0, 0,30, 30, bitmapArray_bits);
//  u8g2.setFont(u8g2_font_t0_11_tf);
//  u8g2.drawUTF8(7, 18, "SETTINGS");  
//  u8g2.sendBuffer();
//  delay(3000);
}

void startUp()
{
  /*************Show Logo String*************/
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_tenstamps_mf);  // choose a suitable font
  u8g2.drawStr(18, 12, "DD");  // write something to the internal memory
  u8g2.setFont(u8g2_font_t0_11_tf);
  u8g2.drawStr(0, 24, "ELECTROTECH");
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(3000);
  u8g2.clearBuffer();
  /*************End Logo String*************/
}


void showSignalLines(int k)
{
    
  for(int loopVal=1;loopVal<=k;loopVal++)
  {
    switch(loopVal)
    {
      case 1:u8g2.drawVLine(2, 6, 1);break;
      case 2:u8g2.drawVLine(4, 4, 3);break;
      case 3:u8g2.drawVLine(6, 2, 5);break;
      case 4:u8g2.drawVLine(8, 0, 7);break;
    }
  }
  u8g2.sendBuffer();
  //delay(5);
}

void showBatteryStatus(int m)
{
  //u8g2.clearBuffer();   // clear the internal memory
  u8g2.drawFrame(50,1,10,6); //x,y,w,h,r
  u8g2.drawBox(50,1,m,5); //x,y,w,h,r
  u8g2.drawBox(60,2,2,3);
  u8g2.sendBuffer();          // transfer internal memory to the display
  //delay(5);
}

void showClock()
{
  u8g2.setFont(u8g2_font_ncenB10_tr);
  u8g2.drawStr(13,19,"16:46");
  u8g2.setFont(u8g2_font_profont10_mn);
  u8g2.drawStr(13,27,"22/9/21");
  u8g2.sendBuffer();
  
}

void counter() //Timer ISR
{
  flag++;
  flag1++;
}
