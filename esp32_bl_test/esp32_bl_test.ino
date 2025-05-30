#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int LED_PIN = 2;  // Built-in LED (on most ESP32 dev boards)

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Optional: Reset BT stack to ensure clean startup
  btStop();
  delay(100);
  btStart();

  // Start Bluetooth with name and PIN
  SerialBT.setPin("1234", 4);  // PIN: 1234, length: 4
  SerialBT.begin("ESP32_LED");  // Bluetooth device name
  Serial.println("Bluetooth started. Waiting for connection...");
}

void loop() {
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n');
    command.trim();  // Remove whitespace

    Serial.print("Received: ");
    Serial.println(command);

    if (command == "on") {
      digitalWrite(LED_PIN, HIGH);
      SerialBT.println("LED ON");
    } else if (command == "off") {
      digitalWrite(LED_PIN, LOW);
      SerialBT.println("LED OFF");
    } else {
      SerialBT.println("Unknown command");
    }
  }
}
