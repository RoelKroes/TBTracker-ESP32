//===============================================================================
// You will need to create your own code here.
// This is all optional.
// You only need to look at it if you want to include sensor data in your tracker
//===============================================================================

//===============================================================================
// Read the VCC voltage.
// Create your own code here
// Useful for checking battery voltage.
//===============================================================================
float ReadVCC() {
#if defined(USE_VOLTAGE_INFO)
  float in_voltage = 0.0;
  float adc_calibrated = 0.0;
  int Iterations = 16;
pinMode(VOLTAGE_IN_PIN,INPUT);

  // Measure a couple of times 
  
  for (int i=1; i<= Iterations;i++ )
  {
     adc_calibrated += analogReadMilliVolts(VOLTAGE_IN_PIN);
     delay(1);
  }   
  adc_calibrated = adc_calibrated / Iterations;
  adc_calibrated = adc_calibrated / 1000.0;
  in_voltage = adc_calibrated / (float(VOLTAGE_DIVIDER_R2) / (float(VOLTAGE_DIVIDER_R1) + float(VOLTAGE_DIVIDER_R2)));
  in_voltage += float(VOLTAGE_DEVIATION);
  return (in_voltage);
#else
  return (0.0);
#endif
}

//===============================================================================
// Read the temperature
// Create your own code here
//===============================================================================
float ReadTemp(void) {
#if defined(USE_BME280)
  // The returned temperature is in degrees Celcius.
  return (bme280_temperature());
#else
  return (0.0);
#endif
}

//===============================================================================
// Read the air pressure
// Create your own code here
//===============================================================================
float ReadPressure(void) {
#if defined(USE_BME280)
  // The returned pressure is in hPa
  return (bme280_pressure());
#else
  return (0.0);
#endif
}


//===============================================================================
// Read the air pressure
// Create your own code here
//===============================================================================
float ReadHumidity(void) {
#if defined(USE_BME280)
  // The returned pressure is in hPa
  return (bme280_humidity());
#else
  return (0.0);
#endif
}

//===============================================================================
// Write the Voltage information for debugging purposes to the Serial Console
//===============================================================================
void printVoltageInfo() {
#if defined(USE_VOLTAGE_INFO)
  toSerialConsole("    Voltage: ");
  toSerialConsole(ReadVCC());
  toSerialConsole(" V\n");
#endif
}
