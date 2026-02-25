#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <GyverHX711.h>
#define DOUT_PIN 8
#define SCK_PIN 7
GyverHX711 scale(DOUT_PIN , SCK_PIN , HX_GAIN64_A);

#define RX_PIN 11
#define TX_PIN 10
SoftwareSerial gsmSerial(RX_PIN , TX_PIN);

#define buzzer A2
int gas_sensor=A3;
int flame_sensor=4; 
int gas_val=0;
int wsts=0,gsts=0,fsts=0;
int cnt=0,flame_val;
int fan=5;
int rly=13;
int kk=0,kk1=0,kk2=0;
long weight_val=0; 

void setup() {
  Serial.begin(115200); 

  gsmSerial.begin(115200);
  delay(500);

  lcd.init();
  lcd.begin(16 , 2);
  //Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("  WELCOME");

  

  pinMode(flame_sensor,INPUT);
  pinMode(buzzer,OUTPUT);  
  pinMode(fan,OUTPUT); 
  pinMode(rly,OUTPUT); 
  digitalWrite(rly,0);
  digitalWrite(buzzer,0); 
  delay(1000);
  
}


void loop() {


if (scale.available()) {
  weight_val = scale.read();
  weight_val = ((weight_val/55.9) - 3333);
}


  gas_val=(analogRead(gas_sensor)/10);
  flame_val=digitalRead(flame_sensor);
    
  lcd.clear();
  lcd.setCursor(0 , 0);
  lcd.print("G:"+ String(gas_val)+ " F:"+String(flame_val) );
  lcd.setCursor(0 , 1);
  lcd.print("W:"+ String(weight_val));
  lcd.setCursor(7 , 1);
  lcd.print("g");

  if(gas_val > 70)
  {
    digitalWrite(rly, 1);
    digitalWrite(fan, 1);
    delay(500);
    lcd.setCursor(10, 0);
    lcd.print("LEAK");
    gsts=1;
    digitalWrite(buzzer, 1);
    delay(300);
    digitalWrite(buzzer, 0);
    if(kk1 == 0)
    {
      kk1 = 1;
      send_sms1();
    } 
  }
  else
  {
    digitalWrite(fan , 0);
    digitalWrite(rly , 0);
    gsts = 0;
    kk1 = 0;
  }

  if(flame_val == 1)
  {
    digitalWrite(rly , 1);
    delay(500);
    digitalWrite(rly , 0);
    lcd.setCursor(10,0);
    lcd.print("fire");
    fsts = 1;
    if(kk2==0)
    {
      kk2 = 1;
      send_sms1();
    }
  }
  else
  {
    digitalWrite(rly , 0);
    fsts = 0;
    kk2 = 0;
  }

  if(weight_val<200)
  {
    lcd.setCursor(10,1);
    lcd.print("BOOK");
    wsts=1;
    digitalWrite(buzzer,1);
    delay(200);
    digitalWrite(buzzer,0);
    if(kk==0)
    {
      kk = 1;
      send_sms();
    }
  }
  else
  {
    wsts=0;
    kk = 0;
  }
  delay(1000);
  
  
}

void send_sms()
{

  Serial.println("Initializing GSM A7670C Module...");
  delay(1000);

  // Test if GSM module is responding
  gsmSerial.println("AT");
  updateSerial();

  // Set SMS mode to text
  gsmSerial.println("AT+CMGF=1");
  updateSerial();

  // Set SMS recipient and message
  gsmSerial.println("AT+CMGS=\"+919182982118\"");  // Replace with your number
  updateSerial();
  
  gsmSerial.print("Customer ID:12345678   Name:Vikas");  // Message body
  delay(100);
  
  gsmSerial.write(26);  // CTRL+Z to send SMS
  updateSerial();

  delay(5000);


}

void send_sms1()
{

  Serial.println("Initializing GSM A7670C ...");
  delay(1000);

  // Test if GSM module is responding
  gsmSerial.println("AT");
  updateSerial();

  // Set SMS mode to text
  gsmSerial.println("AT+CMGF=1");
  updateSerial();

  // Set SMS recipient and message
  gsmSerial.println("AT+CMGS=\"+919182982118\"");  // Replace with your number
  updateSerial();
  
  gsmSerial.print("Alert! Leak/Fire is detected");  // Message body
  delay(100);
  
  gsmSerial.write(26);  // CTRL+Z to send SMS
  updateSerial();

  delay(5000);


}

void updateSerial() {
  delay(500);
  while (Serial.available()) {
    gsmSerial.write(Serial.read());
  }
  while (gsmSerial.available()) {
    Serial.write(gsmSerial.read());
  }
}