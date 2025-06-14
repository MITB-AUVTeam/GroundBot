#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
#include <Wire.h>

// Motor control pins
int m2i1 = 26;
int m2i2 = 25;
int m2e = 27;
int m1i1 = 12;
int m1i2 = 14;
int m1e = 13;

const int pwmFreq = 5000;
const int pwmResolution = 8;

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

    Serial.print(imuData.ax);
    Serial.print(" , ");
    Serial.print(imuData.ay);
    Serial.print(" , ");
    Serial.print(imuData.az);
    Serial.print(" , ");
    Serial.print(imuData.gx);
    Serial.print(" , ");
    Serial.print(imuData.gy);
    Serial.print(" , ");
    Serial.println(imuData.gz);
}

void setup()
{
    Serial.begin(9600);

    pinMode(m1i1, OUTPUT);
    pinMode(m1i2, OUTPUT);
    pinMode(m2i1, OUTPUT);
    pinMode(m2i2, OUTPUT);

    // Initialize PWM on motor enable pins
    ledcAttach(m1e, pwmFreq, pwmResolution);
    ledcAttach(m2e, pwmFreq, pwmResolution);

    WiFi.mode(WIFI_STA); // Set ESP32 as Wi-Fi Station

    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register updated callback
    esp_now_register_recv_cb(OnDataRecv);

    delay(2000);

    digitalWrite(m2i1, LOW);
    digitalWrite(m2i2, HIGH);
    digitalWrite(m1i1, LOW);
    digitalWrite(m1i2, HIGH);

    ledcWrite(m1e, 150);
}

void loop()
{
}