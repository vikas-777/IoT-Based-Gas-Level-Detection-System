#define MQ2_ANALOG A0
#define MQ2_DIGITAL 4

void setup() {
  Serial.begin(9600);
  pinMode(MQ2_DIGITAL, INPUT);

}

void loop() {
  int gasValue = analogRead(MQ2_ANALOG);
  int gasDetected = digitalRead(MQ2_DIGITAL);

  Serial.print("Gas Level: ");
  Serial.println(gasValue);

  if(gasDetected == LOW) {
    Serial.println("Gas Leak Detected!");

  }

  delay(1000);

}
