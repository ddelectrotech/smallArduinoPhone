#include <U8g2lib.h>
#include <Wire.h>
#include <Keypad.h>
#define batValMax 14
#define sigValMax 4
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
uint8_t flag=0;
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad
U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
int sigValue=0,batValue=0,value=0;
int i=1;

void setup() {
  Serial.begin(9600);
  u8g2.begin();
  u8g2.clearBuffer();
  delay(1000);
  
}


// fonts https://github.com/olikraus/u8g2/wiki/fntlistall#4-pixel-height

void loop()
{
  firstContact();
  secondContact();
  thirdContact();
  char customKey = customKeypad.getKey();
  if (customKey){
    //u8g2.userInterfaceSelectionList("Contacts",i,contact_list);
    Serial.println(customKey);
    Serial.println(i);
    if(customKey == '#')
    {
      u8g2.clearBuffer();
      i++;
    }
    if(customKey == '*')
    {
      u8g2.clearBuffer();delay(500);
      u8g2.setDrawColor(1);
      u8g2.setFont(u8g2_font_6x12_tr);
      u8g2.drawUTF8(5, 12, "Calling");
      callToPerson(i);
      u8g2.sendBuffer();
      delay(5000);u8g2.clearBuffer();
    }
    if(i > 3)
      i = 1; 
 }
 
 
  //u8g2.clearBuffer();
  //u8g2.setBitmapMode(false /* solid */);
  //u8g2.setDrawColor(1);
  //u8g2.setFont(u8g2_font_t0_11_tf);
  //u8g2.drawUTF8(7, 18, "SETTINGS");  
  //u8g2.sendBuffer();
  //delay(3000);
}

void firstContact()
{
  if(i==1)
  {
    u8g2.setDrawColor(1);
    u8g2.drawBox(0,1,60,10);
    u8g2.setDrawColor(0);u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawUTF8(2, 9, "Mom");
    u8g2.sendBuffer();
  }
  else if(i!=1)
  {
    u8g2.setDrawColor(1);
    //u8g2.drawBox(0,1,60,10);
    //u8g2.setDrawColor(0);
    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawUTF8(2, 9, "Mom");
    u8g2.sendBuffer();
  }
}

void secondContact()
{
  if(i==2)
  {
    u8g2.setDrawColor(1);
    u8g2.drawBox(0,9,60,10);
    u8g2.setDrawColor(0);u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawUTF8(2, 18, "Dad");
    u8g2.sendBuffer();
  }
  else if(i!=2)
  {
    u8g2.setDrawColor(1);
    //u8g2.drawBox(0,12,60,10);
    //u8g2.setDrawColor(0);
    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawUTF8(2, 18, "Dad");
    u8g2.sendBuffer();
  }
}

void thirdContact()
{
  if(i==3)
  {
    u8g2.setDrawColor(1);
    u8g2.drawBox(0,19,60,10);
    u8g2.setDrawColor(0);u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawUTF8(2, 28, "Wife");
    u8g2.sendBuffer();
  }
  else if(i!=3)
  {
    u8g2.setDrawColor(1);
    //u8g2.drawBox(0,23,60,10);
    //u8g2.setDrawColor(0);
    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawUTF8(2, 27, "Wife");
    u8g2.sendBuffer();
  }
}

void callToPerson(int cal)
{
  switch(cal)
  {
    case 1: u8g2.drawUTF8(5, 20, "Mom");break;
    case 2: u8g2.drawUTF8(5, 20, "Dad");break;
    case 3: u8g2.drawUTF8(5, 20, "Wife");break;
  }
}
