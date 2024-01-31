// include the library
#include <RadioLib.h>

#define PACKETLEN 255

// Change 'SX1278' in the line below to 'SX1276' if you have a SX1276 module.
SX1278 radio = new Module(PIN_NSS, PIN_DIO0, PIN_DIO1);

// create RTTY client instance using the radio module
RTTYClient rtty(&radio);


//===============================================================================
void SetupRTTY()
{

  // First setup FSK
  SetupFSK();

  Serial.print(F("RTTY init.."));

  int16_t state = rtty.begin(RTTYSettings.Frequency,
                     RTTYSettings.Shift,
                     RTTYSettings.Baud,
                     RTTYSettings.Encoding,
                     RTTYSettings.StopBits  );
                     
  if(state == RADIOLIB_ERR_NONE) // Change this to (state == ERR_NONE) if you use an older radiolib library
  {

    Serial.println(F("done"));
  } else 
  {

    Serial.print(F("failed, code "));
    Serial.println(state);
    while(true);
  }
}

//===============================================================================
void SetupHorus()
{
  Serial.println();
  Serial.print("Setting up radio for Horus...");
  // Initialize the radio in FSK mode
  int16_t state = radio.beginFSK();
  // Only continue if there is no error state
  if(state == RADIOLIB_ERR_NONE) 
  {
    Serial.println(F("success!"));
  } else 
  {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while(true);
  }

  state = radio.setOutputPower(HORUS_POWER);

  Serial.print(F("[FSK4] Initializing ... ")); 

  // initialize FSK4 transmitter
  // NOTE: FSK4 frequency shift will be rounded
  //       to the nearest multiple of frequency step size.
  //       The exact value depends on the module:
  //         SX127x/RFM9x - 61 Hz
  //         RF69 - 61 Hz
  //         CC1101 - 397 Hz
  //         SX126x - 1 Hz
  //         nRF24 - 1000000 Hz
  //         Si443x/RFM2x - 156 Hz
  //         SX128x - 198 Hz
  state = fsk4_setup(&radio, HORUS_FREQUENCY, HORUS_SPACING, HORUS_BAUD);

  if(state == RADIOLIB_ERR_NONE) 
  {
    Serial.println(F("success!"));
  } else 
  {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while(true);
  }
}

//===============================================================================
void SetupFSK()
{
  // Initialize the SX1278
  Serial.print(F("[SX1278] init.."));

 // int16_t state = radio.beginFSK();
 
  int16_t state = radio.beginFSK(FSKSettings.Frequency,
                               FSKSettings.BitRate,
                               FSKSettings.FreqDev,
                               FSKSettings.RXBandwidth,
                               FSKSettings.Power,
                               FSKSettings.PreambleLength,
                               FSKSettings.EnableOOK);


  if(state == RADIOLIB_ERR_NONE) // Change this to (state == ERR_NONE) if you use an older radiolib library
  {
    Serial.println(F("done"));
  } 
  else 
  {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while(true);
  }
}


//===============================================================================
void SetupLoRa(int aMode)
{
  // Initialize the SX1278
  Serial.print(F("[LoRA] Initializing ... "));

  ResetRadio(); 

  switch (aMode)
  {
    case 0: 
      LoRaSettings.CodeRate = 8;
      LoRaSettings.Bandwidth = 20.8;
      LoRaSettings.SpreadFactor = 11;
      LoRaSettings.Frequency = LORA_FREQUENCY;
      break;   

    case 1:
      LoRaSettings.CodeRate = 5;
      LoRaSettings.Bandwidth = 20.8;      
      LoRaSettings.SpreadFactor = 6;      
      LoRaSettings.Frequency = LORA_FREQUENCY;
    break;   
    
    case 2:
      LoRaSettings.CodeRate = 8;
      LoRaSettings.Bandwidth = 62.5;      
      LoRaSettings.SpreadFactor = 8;
      LoRaSettings.Frequency = LORA_FREQUENCY;      
      break;   

    case 3:
      LoRaSettings.CodeRate = 6;
      LoRaSettings.Bandwidth = 250;      
      LoRaSettings.SpreadFactor = 7;            
      LoRaSettings.Frequency = LORA_FREQUENCY;
      break;   
    
    case 4:
      LoRaSettings.CodeRate = 5;
      LoRaSettings.Bandwidth = 250;      
      LoRaSettings.SpreadFactor = 6;            
      LoRaSettings.Frequency = LORA_FREQUENCY;
      break;   

    case 5:
      LoRaSettings.CodeRate = 8;
      LoRaSettings.Bandwidth = 41.7;      
      LoRaSettings.SpreadFactor = 11;            
      LoRaSettings.Frequency = LORA_FREQUENCY;
    break;

    case 6:
      LoRaSettings.CodeRate = 5;
      LoRaSettings.Bandwidth = 41.7;      
      LoRaSettings.SpreadFactor = 6;            
      LoRaSettings.Frequency = LORA_FREQUENCY;
    break;

    case 7:
      LoRaSettings.CodeRate = 5;
      LoRaSettings.Bandwidth = 20.8;      
      LoRaSettings.SpreadFactor = 7;            
      LoRaSettings.Frequency = LORA_FREQUENCY;
    break;

    case 8:
      LoRaSettings.CodeRate = 5;
      LoRaSettings.Bandwidth = 62.5;      
      LoRaSettings.SpreadFactor = 6;            
      LoRaSettings.Frequency = LORA_FREQUENCY;
    break;


    case 99:  // LORA-APRS
      LoRaSettings.CodeRate = 5;
      LoRaSettings.Bandwidth = 125;      
      LoRaSettings.SpreadFactor = 12;              
      LoRaSettings.Frequency = LORA_APRS_FREQUENCY;
    break;
  }

  
  
  int16_t state = radio.begin
  (
    LoRaSettings.Frequency,
    LoRaSettings.Bandwidth,
    LoRaSettings.SpreadFactor,
    LoRaSettings.CodeRate,
    LoRaSettings.SyncWord,
    LoRaSettings.Power,
    LoRaSettings.PreambleLength, 
    LoRaSettings.Gain
  );
  
  switch(LORA_MODE) 
  {
    case 0:
      radio.forceLDRO(true);
      radio.setCRC(true);  
    break;
    case 1:
      radio.implicitHeader(PACKETLEN);
      //radio.forceLDRO(true);
      radio.setCRC(true);
    break;
    default:
      radio.explicitHeader();
      //radio.autoLDRO();
      radio.setCRC(true);
    break;
  }  
  
  if(state == RADIOLIB_ERR_NONE) // Change this to (state == ERR_NONE) if you use an older radiolib library
  {
    Serial.println(F("done"));
  } 
  else 
  {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while(true);
  }
}


//===============================================================================
void SetupRadio()
{
  // Setting up the radio
  if (RTTY_ENABLED) {SetupRTTY();}
  if (LORA_ENABLED) {SetupLoRa(LORA_MODE);}
}

//===============================================================================
void sendRTTY(String TxLine)
{
   // Disable the GPS on the softwareserial temporarily 
   // SerialGPS.end();
   
   SetupRTTY();
   
   // Send only idle carrier to let people get their tuning right
   rtty.idle();     
   delay(RTTY_IDLE_TIME);

   // Send the string 
   Serial.print(F("Send RTTY: "));
   Serial.println(TxLine);

   int state = rtty.println(TxLine); 
   rtty.standby();   
   // Enable the GPS again.  
   //SerialGPS.begin(GPSBaud);
}

//===============================================================================
void ResetRadio()
{
  // Use for ESP based boards
  pinMode(PIN_RESET,OUTPUT);
  digitalWrite(PIN_RESET, LOW);
  delay(100);
  digitalWrite(PIN_RESET,HIGH);
  delay(100);
}


//===============================================================================
void sendLoRa(String TxLine, int aMode)
{
   int state;

   SetupLoRa(aMode);
   Serial.println(TxLine);

  switch (LORA_MODE)
  {
    case 1:
      int i;
      int j; 
      // Send the string 
      char buf[PACKETLEN];
      for (j=0; j<PACKETLEN; j++) { buf[j] = '\0';}
      for (i=0; i<TxLine.length(); i++) {buf[i] = TxLine[i];}
      state = radio.transmit((uint8_t*)buf,PACKETLEN);       
    break;
    default:
      // Send the string 
      state = radio.transmit(TxLine); 
    break;      
  }   

  if(state == RADIOLIB_ERR_NONE) // Change this to (state == ERR_NONE) if you use an older radiolib library
  {
    Serial.println(F("done"));
  } else 
  {
    Serial.print(F("failed, code "));
    Serial.println(state);
  } 
}

//===============================================================================
void sendHorusV1()
{
  int pkt_len;
  int coded_len;

  // Setup the radio for Horus communication 
  SetupHorus();

  // Start Horus Binary V1
  Serial.println(F("Generating Horus Binary v1 Packet"));

 // Generate packet for V1
  pkt_len = build_horus_binary_packet_v1(rawbuffer);
  PrintHex(rawbuffer, pkt_len, debugbuffer);
  Serial.print(F("Uncoded Length (bytes): "));
  Serial.println(pkt_len);
  Serial.print(F("Uncoded: ")); 
  Serial.println(debugbuffer);

 // Apply Encoding
  coded_len = horus_l2_encode_tx_packet((unsigned char*)codedbuffer,(unsigned char*)rawbuffer,pkt_len);
  PrintHex(codedbuffer, coded_len, debugbuffer);
  Serial.print(F("Encoded Length (bytes): "));
  Serial.println(coded_len);
  Serial.print(F("Coded: "));
  Serial.println(debugbuffer);

  // Transmit!
  Serial.println(F("Transmitting Horus Binary v1 Packet"));
  // send out idle condition for 1000 ms
  fsk4_idle(&radio);
  delay(1000);
  fsk4_preamble(&radio, 8);
  fsk4_write(&radio, codedbuffer, coded_len);
  Serial.println();
}

//===============================================================================
void sendHorusV2()
{
  int pkt_len;
  int coded_len;

  // Setup the radio for Horus communication 
  SetupHorus();

     // Start Horus Binary V1
  Serial.println(F("Generating Horus Binary v2 Packet"));

  // Generate packet for V1
  pkt_len = build_horus_binary_packet_v2(rawbuffer);
  PrintHex(rawbuffer, pkt_len, debugbuffer);
  Serial.print(F("Uncoded Length (bytes): "));
  Serial.println(pkt_len);
  Serial.print(F("Uncoded: ")); 
  Serial.println(debugbuffer);

  // Apply Encoding
  coded_len = horus_l2_encode_tx_packet((unsigned char*)codedbuffer,(unsigned char*)rawbuffer,pkt_len);
  PrintHex(codedbuffer, coded_len, debugbuffer);
  Serial.print(F("Encoded Length (bytes): "));
  Serial.println(coded_len);
  Serial.print("Coded: ");
  Serial.println(debugbuffer);
  
  // Transmit!
  Serial.println(F("Transmitting Horus Binary v2 Packet"));

  // send out idle condition for 1000 ms
  fsk4_idle(&radio);
  delay(1000);
  fsk4_preamble(&radio, 8);
  fsk4_write(&radio, codedbuffer, coded_len);
}

//===============================================================================
void sendLoRaAprs()
{
   String aprs_packet;
   String lat="";
   String lon="";
   int deg;
   int min;
   float minute_remainder;
   float second_remainder;


   aprs_packet = "";
   aprs_packet += "<\xff\x01";
   // Add Source
   aprs_packet += LORA_APRS_PAYLOAD_ID;
   // Add SSID
   aprs_packet += LORA_APRS_SSID;
   //Add Destination (do not use digipeating)
   aprs_packet += ">";
   aprs_packet += LORA_APRS_DEST;
   // start of "real" data (Coordinates without timestamp)
   aprs_packet += ":=";
   // get the APRS latitude
   aprs_packet += getAPRSlat(UGPS.Latitude);
   // Add the symbol for the primary symbol table
   aprs_packet += "/";
   // Add the longitude
   aprs_packet += getAPRSlon(UGPS.Longitude);
   // Add the symbol for balloon
   aprs_packet += "O";
   // Add the altitude
   aprs_packet += getAPRSAlt(UGPS.Altitude);
   // Add a meesage
   aprs_packet += " LoRa-APRS HAB-NL";

   Serial.println("Sending LoRa APRS packet...");
   sendLoRa(aprs_packet,LORA_APRS_MODE);

}
