#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
typedef struct struct_message
{
    float ax, ay, az, gx, gy, gz;
} struct_message;

// Create a struct_message called imuData
struct_message imuData;

// Updated callback function with correct signature for ESP32 core v3.2.0+
void OnDataRecv(const esp_now_recv_info_t *recvInfo, const uint8_t *incomingData, int len)
{
    memcpy(&imuData, incomingData, sizeof(imuData));

    Serial.print("Accel X: ");
    Serial.print(imuData.ax);
    Serial.print(" | ");
    Serial.print("Y: ");
    Serial.print(imuData.ay);
    Serial.print(" | ");
    Serial.print("Z: ");
    Serial.print(imuData.az);
    Serial.print(" || ");

    Serial.print("Gyro X: ");
    Serial.print(imuData.gx);
    Serial.print(" | ");
    Serial.print("Y: ");
    Serial.print(imuData.gy);
    Serial.print(" | ");
    Serial.print("Z: ");
    Serial.println(imuData.gz);
}

void setup()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_STA); // Set ESP32 as Wi-Fi Station

    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register updated callback
    esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
    // Nothing to do here
}