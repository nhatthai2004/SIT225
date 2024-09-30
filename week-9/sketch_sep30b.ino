#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);
  while (!Serial); // Wait for Serial to initialize

  Wire.setClock(100000);
  
  Serial.println("Initializing BME280 sensor...");
delay(1000);
bme.begin(0x7E);
  // if (!bme.begin()) {
  //   Serial.println("Could not find a valid BME280 sensor, check wiring!");
  //   while (1);
  // } else {
  //   Serial.println("BME280 sensor initialized successfully.");
  // }
}

void loop() {
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");

  delay(2000);
}