#include <SoftwareSerial.h>
#include <String.h>
#include <Keypad.h>
String number="";
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {3, 4, 5, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 8, 9, 12}; //connect to the column pinouts of the keypad
SoftwareSerial mySerial(10, 11); // RX, 
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int day,month,year,minute,second,hour;
char buf[100],sig[20];
String a="";
String s="";
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  delay(2000);
  mySerial.println("AT");delay(1000);
  getTimefromGSM();delay(5000);
  getSignalQuality();delay(5000);
}

void loop() { // run over and over
  char customKey = customKeypad.getKey();
  
  if (customKey){
    if(customKey !='A' && customKey !='B' && customKey !='C' && customKey !='D'){
    number += customKey;
    Serial.print(customKey);
    }
  }
  
    
  if(customKey == 'C')
    {
      
      mySerial.print("ATD");
      mySerial.print(number);
      mySerial.println(';');
      number="";
    }
  else if(customKey == 'D')
    {
      mySerial.print("ATH\r\n");
      //Serial.print(number);
      number="";
    }
}

void getTimefromGSM()
{
  mySerial.println("ATE0");delay(1000);
  mySerial.println("AT+CCLK?");delay(1000);
  if(mySerial.available()>0)
  {
  while(mySerial.read()!='"');
  for(int i=0;i<=99;i++)
  {
    buf[i]= mySerial.read();
    delay(10);
  }
  }
  //a=buf;
  for(int i=0;i<=99;i++)
  {
//  Serial.print(buf[i]);
  a += buf[i];
  }
  //Serial.print(a);Serial.println();
  a.substring(a.indexOf("\"")+1,a.lastIndexOf("\"")-1);
  year=a.substring(0,2).toInt();
  month= a.substring(3,5).toInt();
  day=a.substring(6,8).toInt();
  hour=a.substring(9,11).toInt();
  minute=a.substring(12,14).toInt();
  Serial.print(day);Serial.print('/');
  Serial.print(month);Serial.print('/');Serial.println(year);
  Serial.print(hour);Serial.print(":");Serial.println(minute);
  //delay(10000);
  //String k = GSM.signalQuality();
  //Serial.print("Signal:");Serial.print(k);Serial.println();
}

void getSignalQuality()
{
  mySerial.println("AT+CSQ");delay(1000);
  if(mySerial.available()>0)
  {
  while(mySerial.read()!=':');
  for(int i=0;i<=19;i++)
  {
    sig[i]= mySerial.read();
    delay(10);
  }
  }
  //a=buf;
  for(int i=0;i<=19;i++)
  {
//  Serial.print(buf[i]);
  s += sig[i];
  }
  //Serial.print(s);Serial.println();
  //a.substring(a.indexOf("\"")+1,a.lastIndexOf("\"")-1);
  int sigVal=s.substring(1,3).toInt();
  sigVal = map(sigVal,0,31,0,100);
  Serial.print("Signal Strength in %");Serial.println(sigVal);
}
