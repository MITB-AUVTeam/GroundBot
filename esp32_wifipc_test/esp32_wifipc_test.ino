#include <WiFi.h>

const char* ssid = "Katam_raju";
const char* password = "123321123";

WiFiServer server(3333);
float values[6] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      for (int i = 0; i < 6; i++) {
        client.print(values[i], 3);
        if (i < 5) client.print(",");
      }
      client.println();
      delay(1000);
    }
    client.stop();
  }
}
