#include <WiFiNINA.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Wi-Fi credentials
const char* ssid = "Punchline";         // Replace with your Wi-Fi network name (SSID)
const char* password = "15072004"; // Replace with your Wi-Fi password

// Create a BME280 instance
Adafruit_BME280 bme;  // Default I2C address is 0x76. Some modules may use 0x77.

void setup() {
  // Start the Serial Monitor
  Serial.begin(9600);
  while (!Serial); // Wait for Serial to initialize
  delay(1000);     // Allow some time for the Serial Monitor

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize the BME280 sensor
  Serial.println("Connecting to BME280...");
  if (!bme.begin(0x76)) {  // Try 0x77 if 0x76 doesn't work
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);  // Stop here if the sensor is not found
  }
  Serial.println("BME280 sensor initialized successfully.");
}

void loop() {
  // Read sensor values
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F; // Convert from Pa to hPa

  // Print sensor values to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  delay(2000);  // Wait for 2 seconds before taking the next reading
}
