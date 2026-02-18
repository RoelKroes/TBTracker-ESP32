//============================================================================
// TBTracker-esp32 - roel@kroes.com
// 
//  FIRST THING YOU NEED TO DO IS ADJUST THE SETTINGS IN Settings.h
//  
//  Have FUN!
//============================================================================
#define TBTRACKER_VERSION_MAJOR  0
#define TBTRACKER_VERSION_MINOR  5
#define TBTRACKER_VERSION_PATCH  1
#define TBTRACKER_VERSION_EXTRA  0

#define TBTRACKER_VERSION (((TBTRACKER_VERSION_MAJOR) << 24) | ((TBTRACKER_VERSION_MINOR) << 16) | ((TBTRACKER_VERSION_PATCH) << 8) | (TBTRACKER_VERSION_EXTRA))

void write_version_info() 
{
   toSerialConsole("=======================================================================\n");
   toSerialConsole("Welcome to TBTracker-esp32 by Roel Kroes\n");
   toSerialConsole("Get the latest version at: https://github.com/RoelKroes/TBTracker-ESP32\n\n");
   toSerialConsole("TBTracker version: ");
   toSerialConsole(TBTRACKER_VERSION_MAJOR); toSerialConsole(".");
   toSerialConsole(TBTRACKER_VERSION_MINOR); toSerialConsole(".");
   toSerialConsole(TBTRACKER_VERSION_PATCH); toSerialConsole("\n");
   toSerialConsole(" Radiolib version: ");
   toSerialConsole(RADIOLIB_VERSION_MAJOR); toSerialConsole(".");
   toSerialConsole(RADIOLIB_VERSION_MINOR); toSerialConsole(".");
   toSerialConsole(RADIOLIB_VERSION_PATCH); toSerialConsole("\n");

   // RTTY
   toSerialConsole("RTTY ");   
   if (RTTY_ENABLED)
   {
      toSerialConsole("enabled -> ");
      toSerialConsole(RTTY_PAYLOAD_ID);toSerialConsole(" ");
      toSerialConsole(RTTY_FREQUENCY);toSerialConsole(" MHz"); 
      toSerialConsole(" shift: "); toSerialConsole(RTTY_SHIFT);
      toSerialConsole(" every "); toSerialConsole(RTTY_LOOPTIME); toSerialConsole(" seconds."); toSerialConsole("\n");
   }
   else
   {
      toSerialConsole("disabled.\n");
   }

   // LORA
   toSerialConsole("LoRa ");   
   if (LORA_ENABLED)
   {
      toSerialConsole("enabled -> ");
      toSerialConsole(LORA_PAYLOAD_ID);toSerialConsole(" ");
      toSerialConsole(LORA_FREQUENCY);toSerialConsole(" MHz"); 
      toSerialConsole(" LoRa mode: "); toSerialConsole(LORA_MODE);
      toSerialConsole(" every "); toSerialConsole(LORA_LOOPTIME); toSerialConsole(" seconds.\n");
   }
   else
   {
      toSerialConsole("disabled.\n");
   }

   // LORA APRS
   toSerialConsole("LoRa APRS ");   
   if (LORA_APRS_ENABLED)
   {
      toSerialConsole("enabled -> ");
      toSerialConsole(LORA_APRS_PAYLOAD_ID); toSerialConsole(LORA_APRS_SSID); toSerialConsole(" ");
      if (LORA_APRS_WORLD_ENABLED); toSerialConsole(LORA_APRS_FREQUENCY);toSerialConsole(" MHz "); 
      if (LORA_APRS_PL_ENABLED); toSerialConsole(LORA_APRS_FREQUENCY_PL);toSerialConsole(" MHz "); 
      if (LORA_APRS_UK_ENABLED); toSerialConsole(LORA_APRS_FREQUENCY_UK);toSerialConsole(" MHz "); 
      toSerialConsole(" every "); toSerialConsole(LORA_APRS_LOOPTIME); toSerialConsole(" seconds.\n");
   }
   else
   {
      toSerialConsole("disabled.\n");
   }

   // HORUS V1
   toSerialConsole("HORUS V1 ");   
   if (HORUS_V1_ENABLED)
   {
      toSerialConsole("enabled -> ");
      toSerialConsole("id: "); toSerialConsole(PAYLOAD_ID_V1); toSerialConsole(" ");
      toSerialConsole(HORUS_FREQUENCY_1);toSerialConsole(" MHz "); 
      toSerialConsole(HORUS_FREQUENCY_2);toSerialConsole(" MHz "); 
      toSerialConsole(" every "); toSerialConsole(HORUS_LOOPTIME); toSerialConsole(" seconds.\n");
   }
   else
   {
      toSerialConsole("disabled.\n");
   }

   // HORUS V2
   toSerialConsole("HORUS V2 ");   
   if (HORUS_V2_ENABLED)
   {
      toSerialConsole("enabled -> ");
      toSerialConsole("id: "); toSerialConsole(PAYLOAD_ID_V2); toSerialConsole(" ");
      toSerialConsole(HORUS_FREQUENCY_1);toSerialConsole(" MHz "); 
      toSerialConsole(HORUS_FREQUENCY_2);toSerialConsole(" MHz "); 
      toSerialConsole(" every "); toSerialConsole(HORUS_LOOPTIME); toSerialConsole(" seconds.\n");
   }
   else
   {
      toSerialConsole("disabled.\n");
   }

   // HORUS V3
   toSerialConsole("HORUS V3 ");   
   if (HORUS_V3_ENABLED)
   {
      toSerialConsole("enabled -> ");
      toSerialConsole("id: "); toSerialConsole(HORUS_V3_CALLSIGN); toSerialConsole(" ");
      toSerialConsole(HORUS_FREQUENCY_1);toSerialConsole(" MHz "); 
      toSerialConsole(HORUS_FREQUENCY_2);toSerialConsole(" MHz "); 
      toSerialConsole(" every "); toSerialConsole(HORUS_LOOPTIME); toSerialConsole(" seconds.\n");
   }
   else
   {
      toSerialConsole("disabled.\n");
   }


   // APRS
   toSerialConsole("APRS (AFSK) ");   
   if (APRS_AFSK_ENABLED)
   {
      toSerialConsole("enabled -> ");
      toSerialConsole(APRS_AFSK_CALLSIGN); toSerialConsole(" ");
      toSerialConsole(APRS_AFSK_FREQUENCY);toSerialConsole(" MHz "); 
      toSerialConsole(" every "); toSerialConsole(APRS_AFSK_LOOPTIME); toSerialConsole(" seconds.\n");
   }
   else
   {
      toSerialConsole("disabled.\n");
   }

   toSerialConsole("\n");

   // BME280
   toSerialConsole("BME280 sensor ");
   #if defined(USE_BME280)
   toSerialConsole("enabled.\n");
   #else
   toSerialConsole("disabled.\n");
   #endif

   // Voltage divider
   toSerialConsole("Voltage divider ");
   #if defined(USE_VOLTAGE_INFO)
   toSerialConsole("enabled.\n");
   #else
   toSerialConsole("disabled.\n");
   #endif

   toSerialConsole("=======================================================================\n\n");
}

