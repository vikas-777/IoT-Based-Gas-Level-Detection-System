#define FLAME_ANALOG A0
#define FLAME_DIGITAL D1

void setup() {
  Serial.begin(115200);
  pinMode(FLAME_DIGITAL, INPUT);

}

void loop() {
  int flameValue = analogRead(FLAME_ANALOG);
  int flameDetected = digitalRead(FLAME_DIGITAL);

  Serial.print("Flame Level: ");
  Serial.println(flameValue);

  if(flameDetected == HIGH) {
    Serial.println("Flame Detected! ");

  }
  else {
    Serial.println("No Flame ");

  }

  delay(1000);

}
