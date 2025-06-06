#include <HX710AB.h>

#define DOUT 18  // Data pin
#define SCK  19  // Clock pin

HX710B sensor(DOUT, SCK);

void setup() {
  Serial.begin(115200);
  Serial.println("HX710B Test with ESP32");

  sensor.begin();
}

void loop() {
  // Read the raw value from HX710B
  long value = sensor.read();
  Serial.print("Raw ADC Value: ");
  Serial.println(value);
  delay(500);
}