//============================================================================
// The function CreateTXLine generates two payload sentences to transmit. One
// for RTTY and one for LoRa. These sentences are compatible with the habhub tracker.
// 
// Run the software and decode your payload sentences. Then go to 
// http://habitat.habhub.org/genpayload/ and register your payload there by
// generating a payload configuration document. You will need the generated sentences
// to create a payload configuration document. When you do that, other people will be
// able to see your tracker on the map at https://tracker.habhub.org
//
// Sample of a RTTY payload sentence this software will generate:
// 
// $$RTTY-ID,5,12:11:10,53.16307,6.16444,12,3,12.0,4.61,3.71*109F 
// 
// This sentence contains the following fields, separated by comma's:
//     $$        = prefix
//     RTTY-ID   = callsign
//    5         = sequence number
//     12:11:10  = Time (UTC)
//     53.163067 = Latitude
//     6.16444   = Longitude
//     12        = Altitude
//     3         = Number of satellites
//    12.0      = Internal (chip) temperature in Celsius
//     4.61      = VCC voltage
//     3.71      = External voltage on analog pin A1
//     *         = seprator
//     109F      = Checksum
//     
// The LoRa payload looks the same, except for the callsign (if you changed that).     
//============================================================================

void CreateTXLine(const char *PayloadID, unsigned long aCounter, const char *aPrefix) {
  char Sen[5];
  int Count, i, j;
  unsigned char c;
  unsigned int CRC, xPolynomial;
  char LatitudeString[16], LongitudeString[16], CRCString[8];
  char ExternalTemp[10];
  char BattVoltage[10];
  char ExtVoltage[10];
  char ExtPressure[10];
  char Humidity[10];

  // Get the temperature
  dtostrf(ReadTemp(), -3, 1, ExternalTemp);
  Serial.print("Temperature: ");
  Serial.println(ExternalTemp);

  // Get the battery voltage
  dtostrf(ReadVCC(), -4, 2, BattVoltage);
  Serial.print("Voltage:     ");
  Serial.println(BattVoltage);

  // Get the external air Pressure
  dtostrf(ReadPressure(), -4, 0, ExtPressure);
  Serial.print("Pressure:    ");
  Serial.println(ExtPressure);

  // Get the relative humidity
  dtostrf(ReadHumidity(), -2, 0, Humidity);
  Serial.print("Humidity:    ");
  Serial.println(Humidity);


  dtostrf(UGPS.Latitude, 7, 5, LatitudeString);
  dtostrf(UGPS.Longitude, 7, 5, LongitudeString);

#if defined(USE_FIELDSTR)
  sprintf(Sentence, "%s%s,%ld,%02d:%02d:%02d,%s,%s,%ld,%u,%s,%s,%s,%s,%s",
          aPrefix,
          PayloadID,
          aCounter,
          UGPS.Hours, UGPS.Minutes, UGPS.Seconds,
          LatitudeString,
          LongitudeString,
          UGPS.Altitude,
          UGPS.Satellites,
          BattVoltage,
          ExternalTemp,
          ExtPressure,
          Humidity,
          FIELDSTR);
#else
  sprintf(Sentence, "%s%s,%ld,%02d:%02d:%02d,%s,%s,%ld,%u,%s",
          aPrefix,
          PayloadID,
          aCounter,
          UGPS.Hours, UGPS.Minutes, UGPS.Seconds,
          LatitudeString,
          LongitudeString,
          UGPS.Altitude,
          UGPS.Satellites,
          "0123456");
#endif

  Count = strlen(Sentence);

  // Calc CRC
  CRC = 0xffff;  // Seed
  xPolynomial = 0x1021;

  for (i = strlen(aPrefix); i < Count; i++) {  // For speed, repeat calculation instead of looping for each bit
    CRC ^= (((unsigned int)Sentence[i]) << 8);
    for (j = 0; j < 8; j++) {
      if (CRC & 0x8000)
        CRC = (CRC << 1) ^ 0x1021;
      else
        CRC <<= 1;
    }
  }

  Sentence[Count++] = '*';
  Sentence[Count++] = Hex((CRC >> 12) & 15);
  Sentence[Count++] = Hex((CRC >> 8) & 15);
  Sentence[Count++] = Hex((CRC >> 4) & 15);
  Sentence[Count++] = Hex(CRC & 15);
  Sentence[Count++] = '\n';
  Sentence[Count++] = '\0';
}

//============================================================================
// Get the hex character, given the index
//============================================================================
char Hex(char Character) {
  char HexTable[] = "0123456789ABCDEF";

  return HexTable[Character];
}
