//============================================================================
// This file contains some functions to allow transmissions in specific
// parts of the world.
// It needs still a lot of work, but it is a beginning
//============================================================================


//============================================================================
// Check if we are in Poland (approximately)
// Used to transmit LoRa-APRS on the Polish frequency
//============================================================================
bool inPoland() {
  if (UGPS.validPosition && UGPS.Longitude >= 14.11 && UGPS.Longitude <= 24.15 && UGPS.Latitude >= 49.0 && UGPS.Latitude <= 54.83)
    return true;
  else
    return false;
}

//============================================================================
// Check if we are in the UK (approximately)
// Used to transmit LoRa-APRS on the UK frequency
//============================================================================
bool inUK() {
  if (UGPS.validPosition && UGPS.Longitude >= -6.2 && UGPS.Longitude <= 1.76 && UGPS.Latitude >= 49.96 && UGPS.Latitude <= 58.64)
    return true;
  else
    return false;
}
