#include <SoftwareSerial.h>

#define RX_PIN 7
#define TX_PIN 8 

SoftwareSerial gsmSerial(TX_PIN, RX_PIN);

void setup() {
  Serial.begin(9600);      
  gsmSerial.begin(9600);   
  delay(3000);
    
  Serial.println("Initializing GSM module...");
  
  gsmSerial.println("AT+IPR=9600");
  
  send_sms();

}

void loop() {
  gsmSerial.println("AT+CREG?");
  String response = "";
  while (gsmSerial.available()) {
    char c = gsmSerial.read();
    response += c;
  }
  Serial.println("Response: " + response);
  gsmSerial.print("AT+CMGS=\"9182982118\"\r\n");
  String strength = "";
  while (gsmSerial.available()) {
    char a = gsmSerial.read();
    strength += a;
  }
  Serial.println("strength: " + strength);
  send_sms();
  delay(5000);

}

void send_sms()
{

Serial.println("Sending SMS...");
gsmSerial.println("AT");    
delay(1000);  
gsmSerial.println("ATE0");    
delay(1000);  
gsmSerial.println("AT+CMGF=1");    
delay(1000);   
gsmSerial.print("AT+CMGS=\"9182982118\"\r\n");// Replace x with mobile number
delay(1000);
gsmSerial.println("Alert: Gas level is below 100g");

delay(100);
gsmSerial.println((char)26);// ASCII code of CTRL+Z
delay(5000);
Serial.println("SMS sent!");

}

void send_sms1()
{

Serial.println("Sending SMS...");
gsmSerial.println("AT");    
delay(1000);  
gsmSerial.println("ATE0");    
delay(1000);  
gsmSerial.println("AT+CMGF=1");    
delay(1000);   
gsmSerial.print("AT+CMGS=\"9182982118\"\r\n");// Replace x with mobile number
delay(1000);
gsmSerial.println("Alert: Gas/fire detected");

delay(100);
gsmSerial.println((char)26);// ASCII code of CTRL+Z
delay(5000);
Serial.println("SMS sent!");

}