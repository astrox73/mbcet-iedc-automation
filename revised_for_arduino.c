#include <ArduinoIoTCloud.h>
#include <Arduino_LSM6DS3.h>
#include <WiFiNINA.h>  // Use WiFiNINA library for compatibility with NodeMCU

// Define your Wi-Fi credentials
const char WIFI_SSID[] = "YourWiFiSSID";       // Replace with your Wi-Fi network SSID
const char WIFI_PASS[] = "YourWiFiPassword";   // Replace with your Wi-Fi network password

// Define your IoT Cloud Thing ID
const char THING_ID[] = "YourThingID";  // Replace with your IoT Cloud Thing ID

// Define three switch properties
CloudSwitchProperty switch1Property;
CloudSwitchProperty switch2Property;
CloudSwitchProperty switch3Property;

bool switch1 = false;
bool switch2 = false;
bool switch3 = false;

// Define three relay pins
const int RELAY1_PIN = D1; // Replace with the actual pin numbers for your setup
const int RELAY2_PIN = D2;
const int RELAY3_PIN = D3;

void onSwitch1Change();
void onSwitch2Change();
void onSwitch3Change();

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);

  // Initialize IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreference.autoReconnect);

  // Set your IoT Cloud Thing ID
  ArduinoCloud.setThingId(THING_ID);

  // Initialize switch properties
  switch1Property = ArduinoCloud.addProperty(switch1, "boolean", "Switch1", READ_WRITE);
  switch2Property = ArduinoCloud.addProperty(switch2, "boolean", "Switch2", READ_WRITE);
  switch3Property = ArduinoCloud.addProperty(switch3, "boolean", "Switch3", READ_WRITE);

  // Register callback functions for switch changes
  ArduinoCloud.onChange(switch1Property, onSwitch1Change);
  ArduinoCloud.onChange(switch2Property, onSwitch2Change);
  ArduinoCloud.onChange(switch3Property, onSwitch3Change);
}

void loop() {
  ArduinoCloud.update();
  // Your additional code can go here if needed
}

void onSwitch1Change() {
  // Handle switch1 change here
  if (switch1) {
    // Switch 1 is turned on, perform corresponding action
    digitalWrite(RELAY1_PIN, HIGH); // Turn on relay 1
  } else {
    // Switch 1 is turned off, perform corresponding action
    digitalWrite(RELAY1_PIN, LOW); // Turn off relay 1
  }
}

void onSwitch2Change() {
  // Handle switch2 change here
  if (switch2) {
    // Switch 2 is turned on, perform corresponding action
    digitalWrite(RELAY2_PIN, HIGH); // Turn on relay 2
  } else {
    // Switch 2 is turned off, perform corresponding action
    digitalWrite(RELAY2_PIN, LOW); // Turn off relay 2
  }
}

void onSwitch3Change() {
  // Handle switch3 change here
  if (switch3) {
    // Switch 3 is turned on, perform corresponding action
    digitalWrite(RELAY3_PIN, HIGH); // Turn on relay 3
  } else {
    // Switch 3 is turned off, perform corresponding action
    digitalWrite(RELAY3_PIN, LOW); // Turn off relay 3
  }
}
