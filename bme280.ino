//============================================================================
// Code to get info from the optional BME280 sensor
//============================================================================
#if defined(USE_BME280)

#include <Wire.h>
#include <SPI.h>
#include <BME280I2C.h>
//#include <Adafruit_Sensor.h>    // Can be downloaded from the library manager
//#include <Adafruit_BME280.h>    // Can be downloaded from the library manager

// Adafruit_BME280 bme;   

BME280I2C bme;    // Default : forced mode, standby time = 1000 ms
                  // Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,


//============================================================================
// setup the bme280 sensor
//============================================================================
void setup_bme280() {
  unsigned status;
  toSerialConsole("Setting up bme280.\n");
  Wire.begin(SDA_PIN, SCL_PIN);
  if (!bme.begin())
  {
    toSerialConsole("Could not find a valid BME280 sensor. Wrong wiring?\n");
    return;
  }
  
  switch(bme.chipModel())
 {
     case BME280::ChipModel_BME280:
       toSerialConsole("Found BME280 sensor! Success.\n");
       break;
     case BME280::ChipModel_BMP280:
       toSerialConsole("Found BMP280 sensor! No Humidity available.\n");
       break;
     default:
       toSerialConsole("Found UNKNOWN sensor! Error!\n");
  }
}

//============================================================================
// get the temperature in °C
//============================================================================
float bme280_temperature() {
  float temp(NAN), hum(NAN), pres(NAN);

   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_hPa);

   bme.read(pres, temp, hum, tempUnit, presUnit);

  return (temp);
}

//============================================================================
// get the pressure in hPa
//============================================================================
float bme280_pressure() {
  float temp(NAN), hum(NAN), pres(NAN);

   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_hPa);

   bme.read(pres, temp, hum, tempUnit, presUnit);

   return(pres);
}

//============================================================================
// get the relative humidity in %
//============================================================================
float bme280_humidity() {
  float temp(NAN), hum(NAN), pres(NAN);

   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_hPa);

   bme.read(pres, temp, hum, tempUnit, presUnit);

   return(hum);
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
