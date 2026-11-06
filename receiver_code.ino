
#include <esp_now.h>
#include <WiFi.h>

// Data structure
typedef struct struct_message {
  char message[32];
  float temperature;
  uint32_t counter;
} struct_message;

struct_message receivedData;

// Callback: Runs when data arrives
void OnDataRecv(const esp_now_recv_info_t *info,
                const uint8_t *incomingData,
                int len) {

  if (len != sizeof(receivedData)) {
    Serial.println("Invalid data size!");
    return;
  }

  memcpy(&receivedData, incomingData, sizeof(receivedData));

  receivedData.message[31] = '\0';

  Serial.println("\n--- Data Received ---");

  Serial.print("Message: ");
  Serial.println(receivedData.message);

  Serial.print("Temperature: ");
  Serial.println(receivedData.temperature);

  Serial.print("Counter: ");
  Serial.println(receivedData.counter);

  Serial.println("---------------------");
}

void setup() {
  Serial.begin(115200);

  // WiFi Station mode
  WiFi.mode(WIFI_STA);

  Serial.println("ESP32 Receiver Started");

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed!");
    return;
  }

  // Register receive callback
  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("Receiver Ready!");
}

void loop() {
}
