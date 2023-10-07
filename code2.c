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

#define RELAY_PIN_1     D1  // GPIO pin for Relay 1
#define RELAY_PIN_2     D2  // GPIO pin for Relay 2
#define RELAY_PIN_3     D3  // GPIO pin for Relay 3

bool stateSwitch1 = false;
bool stateSwitch2 = false;
bool stateSwitch3 = false;

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

    SinricPro.begin(APP_KEY, APP_SECRET);

    mySwitch1.onPowerState(onPowerState);
    mySwitch2.onPowerState(onPowerState);
    mySwitch3.onPowerState(onPowerState);

    mySwitch1.setState(stateSwitch1);
    mySwitch2.setState(stateSwitch2);
    mySwitch3.setState(stateSwitch3);

    SinricPro.restoreDeviceStates(true);
}

void loop() {
    SinricPro.process();
}
