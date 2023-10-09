#include <ArduinoIoTCloud.h>
#include <WiFiConnectionManager.h>

const char THING_ID[] = "486ca265-3779-43dd-8d6a-723e7fda6466";  // Replace with your IoT Cloud Thing ID

void onSwitch1Change();
void onSwitch2Change();
void onSwitch3Change();

bool switch1State = false;
bool switch2State = false;
bool switch3State = false;

bool lastSwitch1State = false;
bool lastSwitch2State = false;
bool lastSwitch3State = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);

  // Connect to WiFi
  WiFiConnectionManager.begin();
  while (!WiFiConnectionManager.isConnected()) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  // Initialize IoT Cloud
  ArduinoCloud.setThingId(THING_ID);
  ArduinoCloud.addProperty(switch1State, "boolean");
  ArduinoCloud.addProperty(switch2State, "boolean");
  ArduinoCloud.addProperty(switch3State, "boolean");
  
  // Register callback functions for property changes
  ArduinoCloud.onChange(switch1State, onSwitch1Change);
  ArduinoCloud.onChange(switch2State, onSwitch2Change);
  ArduinoCloud.onChange(switch3State, onSwitch3Change);
  
  ArduinoCloud.begin(ArduinoIoTPreference.autoReconnect);
}

void loop() {
  ArduinoCloud.update();
}

void onSwitch1Change() {
  if (switch1State != lastSwitch1State) {
    digitalWrite(RELAY1_PIN, switch1State ? HIGH : LOW);
    lastSwitch1State = switch1State;
  }
}

void onSwitch2Change() {
  if (switch2State != lastSwitch2State) {
    digitalWrite(RELAY2_PIN, switch2State ? HIGH : LOW);
    lastSwitch2State = switch2State;
  }
}

void onSwitch3Change() {
  if (switch3State != lastSwitch3State) {
    digitalWrite(RELAY3_PIN, switch3State ? HIGH : LOW);
    lastSwitch3State = switch3State;
  }
}
