#include <ESP8266WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

#define WIFI_SSID       "YourWiFiSSID"
#define WIFI_PASS       "YourWiFiPassword"
#define APP_KEY         "YourAppKey"
#define APP_SECRET      "YourAppSecret"
#define SWITCH_ID_1     "YourSwitch1DeviceID"
#define SWITCH_ID_2     "YourSwitch2DeviceID"
#define SWITCH_ID_3     "YourSwitch3DeviceID"

#define RELAY_PIN_1     D1  // GPIO pin for Relay 1
#define RELAY_PIN_2     D2  // GPIO pin for Relay 2
#define RELAY_PIN_3     D3  // GPIO pin for Relay 3

bool stateSwitch1 = false;
bool stateSwitch2 = false;
bool stateSwitch3 = false;

// Define a callback function to control the relays
bool onPowerState(const String& deviceId, bool& state) 
{
    if (deviceId == SWITCH_ID_1) 
    {
        digitalWrite(RELAY_PIN_1, state ? HIGH : LOW);
        stateSwitch1 = state;
    }
    else if (deviceId == SWITCH_ID_2) 
    {
        digitalWrite(RELAY_PIN_2, state ? HIGH : LOW);
        stateSwitch2 = state;
    } 
    else if (deviceId == SWITCH_ID_3) 
    {
        digitalWrite(RELAY_PIN_3, state ? HIGH : LOW);
        stateSwitch3 = state;
    }
    return true;
}

void setup() 
{
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    pinMode(RELAY_PIN_1, OUTPUT);
    pinMode(RELAY_PIN_2, OUTPUT);
    pinMode(RELAY_PIN_3, OUTPUT);

    // Initialize SinricPro
    SinricPro.begin(APP_KEY, APP_SECRET);

    // Setup switches
    mySwitch1.onPowerState(onPowerState);
    mySwitch2.onPowerState(onPowerState);
    mySwitch3.onPowerState(onPowerState);

    // Restore saved states (if any)
    mySwitch1.setState(stateSwitch1);
    mySwitch2.setState(stateSwitch2);
    mySwitch3.setState(stateSwitch3);

    SinricPro.restoreDeviceStates(true);
}

void loop() {
    // Handle SinricPro tasks
    SinricPro.process();
}
