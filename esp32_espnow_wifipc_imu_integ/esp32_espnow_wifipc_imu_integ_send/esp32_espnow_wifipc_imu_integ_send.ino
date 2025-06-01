#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

const char *ssid = "Katam raju";
const char *password = "123321123";

WiFiServer server(3333);

// REPLACE WITH YOUR RECEIVER MAC Address

uint8_t broadcastAddress[] = {0x24, 0x62, 0xab, 0xdd, 0x92, 0x9c};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message
{
    float ax, ay, az, gx, gy, gz;
} struct_message;

// Create a struct_message called imuData
struct_message imuData;
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup()
{
    // Init Serial Monitor
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.begin();

    Wire.begin(21, 22); // SDA, SCL for ESP32

    byte status = mpu.begin();
    Serial.print("MPU6050 status: ");
    Serial.println(status);
    while (status != 0)
    {
        Serial.println("MPU6050 not connected. Retrying...");
        delay(1000);
        status = mpu.begin();
    }

    Serial.println("MPU6050 initialized successfully!");
    delay(1000);

    mpu.calcOffsets(true, true); // Calibrate both gyro and accel

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Transmitted packet
    esp_now_register_send_cb(OnDataSent);

    // Register peer
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }
}

void loop()
{
    WiFiClient client = server.available();
    if (client)
    {
        while (client.connected())
        {
            mpu.update();

            imuData.ax = mpu.getAccX();
            imuData.ay = mpu.getAccY();
            imuData.az = mpu.getAccZ();
            imuData.gx = mpu.getGyroX();
            imuData.gy = mpu.getGyroY();
            imuData.gz = mpu.getGyroZ();

            client.print(imuData.ax, 3);
            client.print(",");
            client.print(imuData.ay, 3);
            client.print(",");
            client.print(imuData.az, 3);
            client.print(",");
            client.print(imuData.gx, 3);
            client.print(",");
            client.print(imuData.gy, 3);
            client.print(",");
            client.print(imuData.gz, 3);
            client.println();

            esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&imuData, sizeof(imuData));

            if (result == ESP_OK)
            {
                Serial.println("Sent with success");
            }
            else
            {
                Serial.println("Error sending the data");
            }
            delay(1000);

        }
        client.stop();
    }
    // Send message via ESP-NOW
}