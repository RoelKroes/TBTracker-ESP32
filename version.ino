//============================================================================
// TBTracker-esp32 - roel@kroes.com
// 
//  FIRST THING YOU NEED TO DO IS ADJUST THE SETTINGS IN Settings.h
//  
//  Have FUN!
//============================================================================
#define TBTRACKER_VERSION_MAJOR  0
#define TBTRACKER_VERSION_MINOR  3
#define TBTRACKER_VERSION_PATCH  3
#define TBTRACKER_VERSION_EXTRA  0

#define TBTRACKER_VERSION (((TBTRACKER_VERSION_MAJOR) << 24) | ((TBTRACKER_VERSION_MINOR) << 16) | ((TBTRACKER_VERSION_PATCH) << 8) | (TBTRACKER_VERSION_EXTRA))

void write_version_info() 
{
   Serial.println("=======================================================================");
   Serial.println("Welcome to TBTracker-esp32 by Roel Kroes");
   Serial.println("Get the latest version at: https://github.com/RoelKroes/TBTracker-ESP32");
   Serial.println(""); 
   Serial.print("TBTracker version: ");
   Serial.print(TBTRACKER_VERSION_MAJOR); Serial.print(".");
   Serial.print(TBTRACKER_VERSION_MINOR); Serial.print(".");
   Serial.println(TBTRACKER_VERSION_PATCH); 
   Serial.print(" Radiolib version: ");
   Serial.print(RADIOLIB_VERSION_MAJOR); Serial.print(".");
   Serial.print(RADIOLIB_VERSION_MINOR); Serial.print(".");
   Serial.println(RADIOLIB_VERSION_PATCH);Serial.println(); 

   // RTTY
   Serial.print("RTTY ");   
   if (RTTY_ENABLED)
   {
      Serial.print("enabled -> ");
      Serial.print(RTTY_PAYLOAD_ID);Serial.print(" ");
      Serial.print(RTTY_FREQUENCY);Serial.print(" MHz"); 
      Serial.print(" shift: "); Serial.print(RTTY_SHIFT);
      Serial.print(" every "); Serial.print(RTTY_LOOPTIME); Serial.println(" seconds.");
   }
   else
   {
      Serial.println("disabled.");
   }

   // LORA
   Serial.print("LoRa ");   
   if (LORA_ENABLED)
   {
      Serial.print("enabled -> ");
      Serial.print(LORA_PAYLOAD_ID);Serial.print(" ");
      Serial.print(LORA_FREQUENCY);Serial.print(" MHz"); 
      Serial.print(" LoRa mode: "); Serial.print(LORA_MODE);
      Serial.print(" every "); Serial.print(LORA_LOOPTIME); Serial.println(" seconds.");
   }
   else
   {
      Serial.println("disabled.");
   }

   // LORA APRS
   Serial.print("LoRa APRS ");   
   if (LORA_APRS_ENABLED)
   {
      Serial.print("enabled -> ");
      Serial.print(LORA_APRS_PAYLOAD_ID); Serial.print(LORA_APRS_SSID); Serial.print(" ");
      if (LORA_APRS_WORLD_ENABLED); Serial.print(LORA_APRS_FREQUENCY);Serial.print(" MHz "); 
      if (LORA_APRS_PL_ENABLED); Serial.print(LORA_APRS_FREQUENCY_PL);Serial.print(" MHz "); 
      if (LORA_APRS_UK_ENABLED); Serial.print(LORA_APRS_FREQUENCY_UK);Serial.print(" MHz "); 
      Serial.print(" every "); Serial.print(LORA_APRS_LOOPTIME); Serial.println(" seconds.");
   }
   else
   {
      Serial.println("disabled.");
   }

   // HORUS V1
   Serial.print("HORUS V1 ");   
   if (HORUS_V1_ENABLED)
   {
      Serial.print("enabled -> ");
      Serial.print("id: "); Serial.print(PAYLOAD_ID_V1); Serial.print(" ");
      Serial.print(HORUS_FREQUENCY_1);Serial.print(" MHz "); 
      Serial.print(HORUS_FREQUENCY_2);Serial.print(" MHz "); 
      Serial.print(" every "); Serial.print(HORUS_LOOPTIME); Serial.println(" seconds.");
   }
   else
   {
      Serial.println("disabled.");
   }

   // HORUS V2
   Serial.print("HORUS V2 ");   
   if (HORUS_V2_ENABLED)
   {
      Serial.print("enabled -> ");
      Serial.print("id: "); Serial.print(PAYLOAD_ID_V2); Serial.print(" ");
      Serial.print(HORUS_FREQUENCY_1);Serial.print(" MHz "); 
      Serial.print(HORUS_FREQUENCY_2);Serial.print(" MHz "); 
      Serial.print(" every "); Serial.print(HORUS_LOOPTIME); Serial.println(" seconds.");
   }
   else
   {
      Serial.println("disabled.");
   }

   // APRS
   Serial.print("APRS (AFSK) ");   
   if (APRS_AFSK_ENABLED)
   {
      Serial.print("enabled -> ");
      Serial.print(APRS_AFSK_CALLSIGN); Serial.print(" ");
      Serial.print(APRS_AFSK_FREQUENCY);Serial.print(" MHz "); 
      Serial.print(" every "); Serial.print(APRS_AFSK_LOOPTIME); Serial.println(" seconds.");
   }
   else
   {
      Serial.println("disabled.");
   }

   Serial.println();

   // BME280
   Serial.print("BME280 sensor ");
   #if defined(USE_BME280)
   Serial.println("enabled.");
   #else
   Serial.println("disabled.");
   #endif

   // Voltage divider
   Serial.print("Voltage divider ");
   #if defined(USE_VOLTAGE_INFO)
   Serial.println("enabled.");
   #else
   Serial.println("disabled.");
   #endif




   Serial.println("=======================================================================");
   Serial.println();

}

