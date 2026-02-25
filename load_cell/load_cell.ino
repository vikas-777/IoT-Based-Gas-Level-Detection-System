#include "HX711.h"

#define DT_PIN 1
#define SCK_PIN 2

HX711 scale;

float calibrationfactor = 250;

void setup() {
  Serial.begin(9600);
  scale.begin(DT_PIN, SCK_PIN);
  delay(1000);
  scale.tare();

}

void loop() {
  float rawdata = scale.get_units(5);
  Serial.print("rawdata ");
  Serial.println(rawdata);
  Serial.print("weight ");
  Serial.print(rawdata / calibrationfactor);
  Serial.println(" g");

  delay(1000);
}
