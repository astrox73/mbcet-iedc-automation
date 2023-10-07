#include <ESP8266WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

#define WIFI_SSID       "IOT-2.4G"               // Your Wi-Fi SSID
#define WIFI_PASS       "2022iedcmbcet"         // Your Wi-Fi password

#define APP_KEY         "08bf5a87-3b03-469b-bc95-09d7af608707"    // Your SinricPro App Key
#define APP_SECRET      "c52e7831-4f1d-4b33-a4c4-415f73bb1ca1-534b55ca-e802-4c16-96c5-ccf490ecdfda" // Your SinricPro App Secret

#define SWITCH_ID_1     "65005548e2a1e41147659333"    // Device ID for Switch 1
#define SWITCH_ID_2     "6500557cb1deae87502153be"    // Device ID for Switch 2
#define SWITCH_ID_3     "65005591b1deae8750215407"    // Device ID for Switch 3

#define RELAY1_PIN        D1  // Define the GPIO pin connected to the first relay (device 1)
#define RELAY2_PIN        D2  // Define the GPIO pin connected to the second relay (device 2)
#define RELAY3_PIN        D3  // Define the GPIO pin connected to the third relay (device 3)

bool switch1State = false;
bool switch2State = false;
bool switch3State = false;

WiFiClientSecure net;

SinricProSwitch& switch1 = SinricPro[SOURCE_ID][SWITCH1_ID];
SinricProSwitch& switch2 = SinricPro[SOURCE_ID][SWITCH2_ID];
SinricProSwitch& switch3 = SinricPro[SOURCE_ID][SWITCH3_ID];

void setup() {
  Serial.begin(115200);
  Serial.println();

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  // Initialize SinricPro
  SinricPro.begin(net, APP_KEY, APP_SECRET);

  // Setup the switches
  switch1.onTurnOn([](TurnOnRequestData& request) {
    switch1State = true;
    digitalWrite(RELAY1_PIN, HIGH); // Turn on the relay 1
    switch1.sendPowerStateEvent(true); // Report the state change to Sinric Pro
    Serial.println("Device 1 turned on");
  });

  switch1.onTurnOff([](TurnOffRequestData& request) {
    switch1State = false;
    digitalWrite(RELAY1_PIN, LOW); // Turn off relay 1
    switch1.sendPowerStateEvent(false); // Report the state change to Sinric Pro
    Serial.println("Device 1 turned off");
  });

  switch2.onTurnOn([](TurnOnRequestData& request) {
    switch2State = true;
    digitalWrite(RELAY2_PIN, HIGH); // Turn on relay 2
    switch2.sendPowerStateEvent(true); // Report the state change to Sinric Pro
    Serial.println("Device 2 turned on");
  });

  switch2.onTurnOff([](TurnOffRequestData& request) {
    switch2State = false;
    digitalWrite(RELAY2_PIN, LOW); // Turn off relay 2
    switch2.sendPowerStateEvent(false); // Report the state change to Sinric Pro
    Serial.println("Device 2 turned off");
  });

  switch3.onTurnOn([](TurnOnRequestData& request) {
    switch3State = true;
    digitalWrite(RELAY3_PIN, HIGH); // Turn on relay 3
    switch3.sendPowerStateEvent(true); // Report the state change to Sinric Pro
    Serial.println("Device 3 turned on");
  });

  switch3.onTurnOff([](TurnOffRequestData& request) {
    switch3State = false;
    digitalWrite(RELAY3_PIN, LOW); // Turn off relay 3
    switch3.sendPowerStateEvent(false); // Report the state change to Sinric Pro
    Serial.println("Device 3 turned off");
  });

  // Initialize the relay pins
  pinMode(RELAY1_PIN, OUTPUT);
  digitalWrite(RELAY1_PIN, LOW); // Ensure relay 1 is initially off
  pinMode(RELAY2_PIN, OUTPUT);
  digitalWrite(RELAY2_PIN, LOW); // Ensure relay 2 is initially off
  pinMode(RELAY3_PIN, OUTPUT);
  digitalWrite(RELAY3_PIN, LOW); // Ensure relay 3 is initially off
}

void loop() {
  SinricPro.handle();
}
