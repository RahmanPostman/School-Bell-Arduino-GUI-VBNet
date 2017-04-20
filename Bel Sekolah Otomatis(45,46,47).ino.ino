#include <Wire.h>
#include "RTClib.h"
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String data = "",Cobas="",input[32],split[16];
boolean dataOK = false;
int b,nilai=0,i=0,s=0, hr=0;
int senin[32],selasa[32],rabu[32],kamis[32],jumat[32],sabtu[32];
char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
SoftwareSerial portTwo(6,7);
RTC_DS3231 rtc;

void setup()
{ 
  Serial.begin(9600,SERIAL_8N1);
  
  #ifndef ESP8266
    while (!Serial); // for Leonardo/Micro/Zero
  #endif
  delay(3000); // wait for console opening

  lcd.begin(16, 2);
  
  if (! rtc.begin()) {
    //Serial.println("Couldn't find RTC");
    while (1);
  }
  portTwo.begin(4800);
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
          for(int b=0;b<=31;b++){ //setting nilai default !=0-24 . 
                    senin[b]=25;  //jika nilai default 0, alarm akan berbunyi pukul 12 malam
                    selasa[b]=25;
                    rabu[b]=25;
                    kamis[b]=25;
                    jumat[b]=25;
                    sabtu[b]=25;
          }
  
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    data += inChar;
    if (inChar == '+') {
      dataOK = true;
    }
  }
}

void isi(){
    int j;
    Cobas="";
    while(data.charAt(i)!=','){
      input[j]=data.charAt(i);
      i++;
      j++;
    }  
 }

void parsing(){ //PARSING DATA
    //Serial.print("Parsing........%" );
    //Serial.println();
    delay(500);
     if(data.startsWith("SENIN"))
       {
            hr=1;
            i=5;
            isi();
        }
      else if(data.startsWith("SELASA"))
       {
            hr=2;
            i=6;
            isi();
        }
      else if(data.startsWith("RABU"))
       {
            hr=3;
            i=4;
            isi();
        }
      else if(data.startsWith("KAMIS"))
       {
            hr=4;i=5; isi();
        }
      else if(data.startsWith("JUMAT"))
       {
            hr=5;
            i=5;
            isi();
        }
      else if(data.startsWith("SABTU"))
       {
            hr=6;
            i=5;
            isi();
        }
    else{
      //Serial.print("wrong..turn!!!......%" ); 
        }
}

void loop()
{
    DateTime now = rtc.now();
    if(dataOK){
    parsing();
    split[0] =input[0]+=input[1];//menyatukan input tiap dua digit
    split[1] =input[3]+=input[4];
    split[2] =input[5];
    split[3] =input[6]+=input[7];
    split[4] =input[9]+=input[10];
    split[5] =input[11];
    
     if(hr==1)  //merubah isi array split ke array hari
       {
          for(s=0;s<48;s++){
              senin[s] =split[s].toInt();
          }
          s=0;
        }
      else if(hr==2)  
       {
          for(s=0;s<48;s++){
            selasa[s] =split[s].toInt();
          }
          s=0;          
        }
      else if(hr==3)
       {
          for(s=0;s<48;s++){
            rabu[s] =split[s].toInt();
          }
          s=0;          
        }
      else if(hr==4)
       {
          for(s=0;s<48;s++){
            kamis[s] =split[s].toInt();
          }
          s=0;          
        }
      else if(hr==5)
       {
          for(s=0;s<48;s++){
            jumat[s] =split[s].toInt();
          }
          s=0;          
        }
      else if(hr==6)
       {
          for(s=0;s<48;s++){
            sabtu[s] =split[s].toInt();
          }
          s=0;          
        }
    else{  
        }
      
    lcd.setCursor(0, 0);
    lcd.print("setting ok! --");
    lcd.print(hr);
    lcd.print(" ");
    lcd.print(now.dayOfTheWeek());
    
    hr=0;
    delay(500);
  lcd.clear();
    data = "";
    dataOK = false;
    }
    //###########################################################
    //cek setting alarm, ketika jam sama alarm bunyi
    if(now.dayOfTheWeek()==1){
          for(int b=0;b<=18;b+3){
                 while(now.hour()==senin[b] & now.minute()==senin[b+1])
                {
                    portTwo.write(senin[b+2]);
                    lcd.setCursor(0, 0);
                    lcd.print("Bel bunyi");
                    delay(16000);
                    portTwo.write(0xEF);
                    delay(45000);
                    break;
                 }
          }
    }
    else if(now.dayOfTheWeek()==2){
          for(int b=0;b<=18;b+3){
                 while(now.hour()==selasa[b] & now.minute()==selasa[b+1])
                {
                    portTwo.write(selasa[b+2]);
                    lcd.setCursor(0, 0);
                    lcd.print("Bel bunyi");
                    delay(16000);
                    portTwo.write(0xEF);
                    delay(45000);
                    break;
                 }
          }
    }
    else if(now.dayOfTheWeek()==3){
          for(int b=0;b<=18;b+3){
                 while(now.hour()==rabu[b] & now.minute()==rabu[b+1])
                {
                    portTwo.write(rabu[b+2]);
                    lcd.setCursor(0, 0);
                    lcd.print("Bel bunyi");
                    delay(16000);
                    portTwo.write(0xEF);
                    delay(45000);
                    break;
                 }
          }
    }
    else if(now.dayOfTheWeek()==4){
          for(int b=0;b<=18;b+3){
                 while(now.hour()==kamis[b] & now.minute()==kamis[b+1])
                {
                    portTwo.write(kamis[b+2]);
                    lcd.setCursor(0, 0);
                    lcd.print("Bel bunyi");
                    delay(16000);
                    portTwo.write(0xEF);
                    delay(45000);
                    break;
                 }
          }
    }
    else if(now.dayOfTheWeek()==5){
          for(int b=0;b<=18;b+3){
                 while(now.hour()==jumat[b] & now.minute()==jumat[b+1])
                {
                    portTwo.write(jumat[b+2]);
                    lcd.setCursor(0, 0);
                    lcd.print("Bel bunyi");
                    delay(16000);
                    portTwo.write(0xEF);
                    delay(45000);
                    break;
                 }
          }
    }
    else if(now.dayOfTheWeek()==6){
          for(int b=0;b<=18;b+3){
                 while(now.hour()==sabtu[b] & now.minute()==sabtu[b+1])
                {
                    portTwo.write(sabtu[b+2]);
                    lcd.setCursor(0, 0);
                    lcd.print("Bel bunyi");
                    delay(16000);
                    portTwo.write(0xEF);
                    delay(45000);
                    break;
                 }
          }
    }
    lcd.setCursor(0, 0);
    lcd.print(now.year(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.day(), DEC);
    lcd.print("      ");
    lcd.setCursor(0, 1);
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.print("  ");
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);
    lcd.print("  ");
    delay(1000);   
}


