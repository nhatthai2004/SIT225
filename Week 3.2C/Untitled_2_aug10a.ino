#include <DHT.h>
#include "thingProperties.h"


// Define DHT sensor pin and type
#define DHTPIN 2
#define DHTTYPE DHT22

// Create an instance of the DHT class
DHT dht(DHTPIN, DHTTYPE);

// Define temperature threshold
const float TEMP_THRESHOLD = 50.0;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  delay(1500); // Delay for Serial Monitor

  // Initialize the DHT sensor
  dht.begin();

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  // Set up debugging information
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();

  // Read temperature from DHT sensor
  float temperature = dht.readTemperature();

  // Check if the reading is valid
  if (!isnan(temperature)) {
    // Update alarmStatus and alarmMessage based on temperature
    if (temperature > TEMP_THRESHOLD) {
      alarmStatus = true;
      alarmMessage = "Temperature Alert! Current temperature: " + String(temperature) + "°C";
    } else {
      alarmStatus = false;
      alarmMessage = "";
    }
  } else {
    // Handle error in reading temperature
    alarmStatus = false;
    alarmMessage = "Error reading temperature";
  }

  // Update cloud variables
  ArduinoCloud.update();

  delay(5000); // Wait 5 seconds before the next loop iteration
}

/*
  Since AlarmStatus is READ_WRITE variable, onAlarmStatusChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onAlarmStatusChange() {
  // Code to act upon AlarmStatus change if needed
}

/*
  Since AlarmMessage is READ_WRITE variable, onAlarmMessageChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onAlarmMessageChange() {
  // Code to act upon AlarmMessage change if needed
}
