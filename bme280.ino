//============================================================================
// Code to get info from the optional BME280 sensor
//============================================================================
#if defined(USE_BME280)

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>    // Can be downloaded from the library manager
#include <Adafruit_BME280.h>    // Can be downloaded from the library manager

Adafruit_BME280 bme;   

//============================================================================
// setup the bme280 sensor
//============================================================================
void setup_bme280() {
  unsigned status;
  Serial.println("Setting up bme280.");
  Wire.begin(SDA_PIN, SCL_PIN);
  status = bme.begin(0x76, &Wire);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x");
    Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    Serial.println();
  }
}

//============================================================================
// get the temperature in °C
//============================================================================
float bme280_temperature() {
  return (bme.readTemperature());
}

//============================================================================
// get the pressure in hPa
//============================================================================
float bme280_pressure() {
  return (bme.readPressure() / 100.0F);
}

//============================================================================
// get the relative humidity in %
//============================================================================
float bme280_humidity() {
  return (bme.readHumidity());
}

#endif

//============================================================================
// Print the BME280 values for debugging purposes
//============================================================================
void printbme280Data() {
#if defined(USE_BME280)
  Serial.print(F("Temperature: "));
  Serial.print(bme280_temperature());
  Serial.println(" °C");
  Serial.print(F("   Pressure: "));
  Serial.print(bme280_pressure());
  Serial.println(" hPa");
  Serial.print(F("   Humidity: "));
  Serial.print(bme280_humidity());
  Serial.println(" %");
#endif
}
