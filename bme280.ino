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
  toSerialConsole("Setting up bme280.\n");
  Wire.begin(SDA_PIN, SCL_PIN);
  status = bme.begin(0x76, &Wire);
  if (!status) {
    toSerialConsole("Could not find a valid BME280 sensor, check wiring, address, sensor ID!\n");
    toSerialConsole("SensorID was: 0x");
    toSerialConsole(bme.sensorID(), 16); toSerialConsole("\n");
    toSerialConsole("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    toSerialConsole("   ID of 0x56-0x58 represents a BMP 280,\n");
    toSerialConsole("        ID of 0x60 represents a BME 280.\n");
    toSerialConsole("        ID of 0x61 represents a BME 680.\n\n");
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
// Write the BME280 values for debugging purposes to the serial console
//============================================================================
void printbme280Data() {
#if defined(USE_BME280)
  toSerialConsole("Temperature: ");
  toSerialConsole(bme280_temperature());
  toSerialConsole(" °C\n");
  toSerialConsole("   Pressure: ");
  toSerialConsole(bme280_pressure());
  toSerialConsole(" hPa\n");
  toSerialConsole("   Humidity: ");
  toSerialConsole(bme280_humidity());
  toSerialConsole(" %\n");
#endif
}
