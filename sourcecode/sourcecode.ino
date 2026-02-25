#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include<SoftwareSerial.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(2,3);

#include <GyverHX711.h>
GyverHX711 sensor(6, 7, HX_GAIN64_A);

#define buzzer A2

int gas_sensor=A0;
int flame_sensor=A1; 
int gas_val=0;
int wsts=0,gsts=0;
int cnt=0,weight_val=0,flame_val;
int fan=5;
int rly=4;
int kk=0,kk1=0;
void setup() {
  Serial.begin(9600); 

  mySerial.begin(9600); 
  delay(500);
  sensor.tare();
  lcd.begin();

 // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("   WELCOME");
  
  pinMode(flame_sensor,INPUT);
  pinMode(buzzer,OUTPUT);  
  pinMode(fan,OUTPUT); 
  pinMode(rly,OUTPUT); 
  digitalWrite(rly,0);
  digitalWrite(buzzer,0); 
  delay(1000);
  
}

void loop() {


if (sensor.available()) {
    weight_val=sensor.read();
    weight_val=weight_val/100;
    if(weight_val<50)
    weight_val=0;
}
    gas_val=(analogRead(gas_sensor)/10);
    flame_val=digitalRead(flame_sensor   
 lcd.clear();
 lcd.print("G:"+ String(gas_val)+ " F:"+String(flame_val) );
lcd.setCursor(0,1);
lcd.print("W:"+ String(weight_val));
 if(gas_val>70 || flame_val==1)
 {
  digitalWrite(rly,1);
  digitalWrite(fan,1);
   lcd.setCursor(10,1);
  lcd.print("LEAK/fire");
  gsts=1;
  digitalWrite(buzzer,1);
  delay(300);
  digitalWrite(buzzer,0);

  if(kk1==0)
  {
    kk1=1;
    send_sms1();
  }
 }
 else
 {
   gsts=0;
 }

 if(weight_val<100)
 {
  lcd.setCursor(10,1);
  lcd.print("BOOK");
    wsts=1;
  digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
  if(kk==0)
  {
    kk=1;
    send_sms();
  }
 }
 else
 {
   wsts=0;
 }
 delay(1000);


cnt=cnt+1;
if(cnt>15)
{

  cnt=0;
  mySerial.print("330502,SVUKJKOCYLO930KA,0,0,SRC 24G,src@internet,"+String(gval) +","+String(wval)+","+String(fval)+",\n");

}

}
void send_sms()
{


Serial.println("AT");    
delay(1000);  
Serial.println("ATE0");    
delay(1000);  
Serial.println("AT+CMGF=1");    
delay(1000);   
Serial.print("AT+CMGS=\"9533666836\"\r\n");// Replace x with mobile number
delay(1000);
Serial.println("Alert: Gas level is bellow 100g");

delay(100);
Serial.println((char)26);// ASCII code of CTRL+Z
delay(5000);


}

void send_sms1()
{


Serial.println("AT");    
delay(1000);  
Serial.println("ATE0");    
delay(1000);  
Serial.println("AT+CMGF=1");    
delay(1000);   
Serial.print("AT+CMGS=\"9533666836\"\r\n");// Replace x with mobile number
delay(1000);
Serial.println("Alert: Gas/fire detected");

delay(100);
Serial.println((char)26);// ASCII code of CTRL+Z
delay(5000);


}