#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <MPU6050_light.h>
#include <HardwareSerial.h>

MPU6050 mpu(Wire);

// REPLACE WITH YOUR RECEIVER MAC Address

uint8_t broadcastAddress[] = {0xfc, 0xf5, 0xc4, 0x31, 0x51, 0x10};

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

    Serial1.begin(9600, SERIAL_8N1, 5, 4); // RX=16, TX=17
    Serial.begin(9600);

    unsigned long startMillis = millis(); // time starts at 0

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
    unsigned long elapsedMillis = millis() - startMillis;
    unsigned long seconds = elapsedMillis / 1000;
    unsigned long minutes = seconds / 60;
    unsigned long hours = minutes / 60;

    seconds %= 60;
    minutes %= 60;

    char buffer[9];
    sprintf(buffer, "%02lu:%02lu:%02lu", hours, minutes, seconds);
    Serial1.println(buffer);

    mpu.update();

    // Set values to send
    imuData.ax = mpu.getAccX();
    imuData.ay = mpu.getAccY();
    imuData.az = mpu.getAccZ();
    imuData.gx = mpu.getGyroX();
    imuData.gy = mpu.getGyroY();
    imuData.gz = mpu.getGyroZ();

    Serial1.print(imuData.ax);
    Serial1.print(" , ");
    Serial1.print(imuData.ay);
    Serial1.print(" , ");
    Serial1.print(imuData.az);
    Serial1.print(" , ");
    Serial1.print(imuData.gx);
    Serial1.print(" , ");
    Serial1.print(imuData.gy);
    Serial1.print(" , ");
    Serial1.println(imuData.gz);

    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&imuData, sizeof(imuData));

    if (result == ESP_OK)
    {
        Serial.println("Sent with success");
    }
    else
    {
        Serial.println("Error sending the data");
    }
    delay(50);
}