//============================================================================
// Radio rtelated functions
//============================================================================

// include the library
#include <RadioLib.h>

// max packet length
#define PACKETLEN 255

// Create radio modules depending on what RF chip you use
#if defined(USE_SX127X)
SX1278 radio = new Module(PIN_NSS, PIN_DIO0, PIN_RESET, PIN_DIO1);
#else
#if defined(USE_LLCC68)
LLCC68 radio = new Module(PIN_NSS, PIN_DIO1, PIN_RESET, PIN_BUSY);
#else
#if defined(USE_SX1268)
SX1268 radio = new Module(PIN_NSS, PIN_DIO1, PIN_RESET, PIN_BUSY);
#else
#if defined(USE_SX1262)
SX1262 radio = new Module(PIN_NSS, PIN_DIO1, PIN_RESET, PIN_BUSY);
#endif
#endif
#endif
#endif

// create RTTY client instance using the radio module
RTTYClient rtty(&radio);

//============================================================================
// this function is called when a complete packet is received by the radio module
// in receiving mode.
// IMPORTANT: this function MUST be 'void' type and MUST NOT have any arguments!
//============================================================================
void setFlag(void) {
  // we got a packet, set the flag
  receivedFlag = true;
}

//============================================================================
// Clear the interupt flag when in receiving mode
//============================================================================
void unsetFlag(void) {
#if defined(USE_SX127X)
  radio.clearDio0Action();
#else
  radio.clearDio1Action();
#endif
}

//============================================================================
// Do the setup for RTTY
//============================================================================
void SetupRTTY() {
  // First setup FSK
  SetupFSK();
  // RTTY
  toSerialConsole("RTTY init..");
  // Setup for RTTY
  Radiolib_assert(
    rtty.begin(RTTYSettings.Frequency,
               RTTYSettings.Shift,
               RTTYSettings.Baud,
               RTTYSettings.Encoding,
               RTTYSettings.StopBits));
}

//============================================================================
// Setup the radio for APRS and send an APRS packet
//============================================================================
void SendAPRS() {
  // PIN_DIO2 needs to be connected
  AFSKClient audio(&radio, PIN_DIO2);
  // create AX.25 client instance using the FSK module
  AX25Client ax25(&audio);
  // create APRS client instance using the AX.25 client
  APRSClient aprs(&ax25);

  
  toSerialConsole("\nSetting up radio for APRS...");
  Radiolib_assert(radio.beginFSK(APRS_AFSK_FREQUENCY + APRS_AFSK_FREQ_OFFSET));
  Radiolib_assert(radio.setOutputPower(APRS_AFSK_POWER));
  // If we get this far, the radio is initialized
  // initialize AX.25 client
  toSerialConsole("[AX.25] Initializing ... ");
  // Source call, ssid, preamble length
  Radiolib_assert(ax25.begin(APRS_AFSK_CALLSIGN, APRS_AFSK_SSID, APRS_AFSK_PREAMBLE));

  // Correct tone if necessary
  // Radiolib_assert(ax25.setCorrection(1, 2));

  // initialize APRS client
  toSerialConsole("[APRS] Initializing ... ");
  // symbol:'O' (Balloon)
  Radiolib_assert(aprs.begin('O'));

  // If we get here we are ready send an APRS packet using AFSK/AX.25
  String lStr;
  toSerialConsole("[APRS] Sending location report\n");
  // The DESTID that TBTracker was assigned. Do not change.
  char destination[] = "APETBT";
  // Get the current latitude
  char latitude[10];
  lStr = getAPRSlat(UGPS.Latitude);
  lStr.toCharArray(latitude, lStr.length() + 1);
  // Get thre current longitude
  char longitude[10];
  lStr = getAPRSlon(UGPS.Longitude);
  lStr.toCharArray(longitude, lStr.length() + 1);
  // Get the current altitude
  char altitude[10];
  lStr = getAPRSAlt(UGPS.Altitude);
  lStr.toCharArray(altitude, lStr.length() + 1);
  // Get the current time
  char timestamp[10];
  lStr = getAPRStimestamp();
  lStr.toCharArray(timestamp, lStr.length() + 1);

  // Send the actual APRS packet
  Radiolib_assert(aprs.sendPosition(destination, 0, latitude, longitude, altitude, timestamp));
}

//============================================================================
// Set the radio for Horus 4FSK
//============================================================================
void SetupHorus(float lFreq) {
  toSerialConsole("\nSetting up radio for Horus...\n");
// Initialize the radio in FSK mode
#if defined(USE_SX1262)
  Radiolib_assert(radio.beginFSK(FSK_FREQUENCY, FSK_BITRATE, FSK_FREQDEV, FSK_RXBANDWIDTH_sx126, FSK_POWER, FSK_PREAMBLELENGTH, USE_TCXO, FSK_USERREGULATORLDO));
#else
#if defined(USE_SX1268)
   Radiolib_assert(radio.beginFSK(FSK_FREQUENCY, FSK_BITRATE, FSK_FREQDEV, FSK_RXBANDWIDTH_sx126, FSK_POWER, FSK_PREAMBLELENGTH, USE_TCXO, FSK_USERREGULATORLDO));
#else 
#if defined(USE_SX127X)  
  Radiolib_assert(radio.beginFSK(FSK_FREQUENCY, FSK_BITRATE, FSK_FREQDEV, FSK_RXBANDWIDTH_sx127, FSK_POWER, FSK_PREAMBLELENGTH, FSK_ENABLEOOK));
#else
#if defined (USE_LLCC68)  
  Radiolib_assert(radio.beginFSK(FSK_FREQUENCY, FSK_BITRATE, FSK_FREQDEV, FSK_RXBANDWIDTH_sx126, FSK_POWER, FSK_PREAMBLELENGTH, USE_TCXO, FSK_USERREGULATORLDO));
#endif
#endif
#endif
#endif


  toSerialConsole("[FSK4] Initializing ... ");
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
  // Set the outputpower for Horus
  Radiolib_assert(radio.setOutputPower(HORUS_POWER));
  // Setup everything for Horus
  Radiolib_assert(fsk4_setup(&radio, lFreq + HORUS_FREQ_OFFSET, HORUS_SPACING, HORUS_BAUD));
}

//============================================================================
// Set the radio for FSK modulation
//============================================================================
void SetupFSK() {

  toSerialConsole("\nSetting up radio for RTTY...");
// Initialize the radio in FSK mode
#if defined(USE_SX1262)
  Radiolib_assert(radio.beginFSK(FSK_FREQUENCY, FSK_BITRATE, FSK_FREQDEV, FSK_RXBANDWIDTH_sx126, FSK_POWER, FSK_PREAMBLELENGTH, USE_TCXO, FSK_USERREGULATORLDO));
#else
#if defined(USE_SX1268)
   Radiolib_assert(radio.beginFSK(FSK_FREQUENCY, FSK_BITRATE, FSK_FREQDEV, FSK_RXBANDWIDTH_sx126, FSK_POWER, FSK_PREAMBLELENGTH, USE_TCXO, FSK_USERREGULATORLDO));
#else 
#if defined(USE_SX127X)  
  Radiolib_assert(radio.beginFSK(FSK_FREQUENCY, FSK_BITRATE, FSK_FREQDEV, FSK_RXBANDWIDTH_sx127, FSK_POWER, FSK_PREAMBLELENGTH, FSK_ENABLEOOK));
#else
#if defined (USE_LLCC68)  
  Radiolib_assert(radio.beginFSK(FSK_FREQUENCY, FSK_BITRATE, FSK_FREQDEV, FSK_RXBANDWIDTH_sx126, FSK_POWER, FSK_PREAMBLELENGTH, USE_TCXO, FSK_USERREGULATORLDO));
#endif
#endif
#endif
#endif  
}

//============================================================================
// Set the radio for LoRa modulation
//============================================================================
void SetupLoRa(int aMode) {
  // Initialize the SX1278
  toSerialConsole("[LoRA] Initializing ... ");

  ResetRadio();

  switch (aMode) {
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
      LoRaSettings.implicitHeader = 255;
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

    case 97:  // LORA-APRS UK Frequency
      LoRaSettings.CodeRate = 5;
      LoRaSettings.Bandwidth = 125;
      LoRaSettings.SpreadFactor = 12;
      LoRaSettings.Frequency = LORA_APRS_FREQUENCY_UK;
      break;

    case 98:  // LORA-APRS Poland frequency
      LoRaSettings.CodeRate = 7;
      LoRaSettings.Bandwidth = 125;
      LoRaSettings.SpreadFactor = 9;
      LoRaSettings.Frequency = LORA_APRS_FREQUENCY_PL;
      break;

    case 99:  // LORA-APRS world frequency
      LoRaSettings.CodeRate = 5;
      LoRaSettings.Bandwidth = 125;
      LoRaSettings.SpreadFactor = 12;
      LoRaSettings.Frequency = LORA_APRS_FREQUENCY;
      break;
  }

  //Add the frequency error from settings.h to the LoRa frequency
  if (aMode < 90) {
    LoRaSettings.Frequency += LORA_FREQ_OFFSET;
  } else {
    LoRaSettings.Frequency += LORA_APRS_FREQ_OFFSET;
  }

#if defined(USE_SX1262)
  Radiolib_assert(
    radio.begin(
      LoRaSettings.Frequency,
      LoRaSettings.Bandwidth,
      LoRaSettings.SpreadFactor,
      LoRaSettings.CodeRate,
      LoRaSettings.SyncWord,
      LoRaSettings.Power,
      LoRaSettings.PreambleLength,
      USE_TCXO));
#else
#if defined(USE_SX1268)
  Radiolib_assert(
    radio.begin(
      LoRaSettings.Frequency,
      LoRaSettings.Bandwidth,
      LoRaSettings.SpreadFactor,
      LoRaSettings.CodeRate,
      LoRaSettings.SyncWord,
      LoRaSettings.Power,
      LoRaSettings.PreambleLength,
      USE_TCXO));
#else
  Radiolib_assert(
    radio.begin(
      LoRaSettings.Frequency,
      LoRaSettings.Bandwidth,
      LoRaSettings.SpreadFactor,
      LoRaSettings.CodeRate,
      LoRaSettings.SyncWord,
      LoRaSettings.Power,
      LoRaSettings.PreambleLength,
      LoRaSettings.Gain));
#endif
#endif

  switch (LORA_MODE) {
    case 0:
      Radiolib_assert(radio.explicitHeader());
      Radiolib_assert(radio.forceLDRO(true));
      Radiolib_assert(radio.setCRC(true));
      break;
    case 1:
      Radiolib_assert(radio.implicitHeader(PACKETLEN));
      Radiolib_assert(radio.autoLDRO());
      Radiolib_assert(radio.setCRC(true));
      break;
    default:
      Radiolib_assert(radio.explicitHeader());
      Radiolib_assert(radio.autoLDRO());
      Radiolib_assert(radio.setCRC(true));
      break;
  }
}


//============================================================================
// Initial setup of radio (more or less deprecated, I have to look into that)
//============================================================================
void SetupRadio() {
  // Setting up the radio
  if (RTTY_ENABLED) { SetupRTTY(); }
  if (LORA_ENABLED) { SetupLoRa(LORA_MODE); }
}

//============================================================================
// Send RTTY over the radio
//============================================================================
void sendRTTY(String TxLine) {
  SetupRTTY();

  // Send only idle carrier to let people get their tuning right
  rtty.idle();
  delay(RTTY_IDLE_TIME);

  // Send the string
  toSerialConsole("Send RTTY: ");
  toSerialConsole(TxLine);toSerialConsole("\n");
  toSerialConsole(TxLine);toSerialConsole("\n");
  Radiolib_assert(rtty.standby());
}

//============================================================================
// Hardware reset of the radio
//============================================================================
void ResetRadio() {
  // Use for ESP based boards
  pinMode(PIN_RESET, OUTPUT);
  digitalWrite(PIN_RESET, LOW);
  delay(100);
  digitalWrite(PIN_RESET, HIGH);
  delay(100);
}

//============================================================================
// Send a LoRa packet over the radio
//============================================================================
void sendLoRa(String TxLine, int aMode) {
  SetupLoRa(aMode);
  toSerialConsole(TxLine);toSerialConsole("\n");

  switch (LORA_MODE) {
    case 1:
      int i;
      int j;
      // Send the string
      char buf[PACKETLEN];
      for (j = 0; j < PACKETLEN; j++) { buf[j] = '\0'; }
      for (i = 0; i < TxLine.length(); i++) { buf[i] = TxLine[i]; }
      Radiolib_assert(radio.transmit((uint8_t*)buf, PACKETLEN));
      break;
    default:
      // Send the string
      Radiolib_assert(radio.transmit(TxLine));
      break;
  }
}

//============================================================================
// Send a Horus V1 packet over the radio
//============================================================================
void sendHorusV1() {
  int pkt_len;
  int coded_len;

  // Start Horus Binary V1
  toSerialConsole("Generating Horus Binary v1 Packet");

  // Generate packet for V1
  pkt_len = build_horus_binary_packet_v1(rawbuffer);
  PrintHex(rawbuffer, pkt_len, debugbuffer);
  toSerialConsole("Uncoded Length (bytes): ");
  toSerialConsole(pkt_len);toSerialConsole("\n");
  toSerialConsole("Uncoded: ");
  toSerialConsole(debugbuffer);toSerialConsole("\n");

  // Apply Encoding
  coded_len = horus_l2_encode_tx_packet((unsigned char*)codedbuffer, (unsigned char*)rawbuffer, pkt_len);
  PrintHex(codedbuffer, coded_len, debugbuffer);
  toSerialConsole("Encoded Length (bytes): ");
  toSerialConsole(coded_len); toSerialConsole("\n");
  toSerialConsole("Coded: ");
  toSerialConsole(debugbuffer);toSerialConsole("\n");

  // Setup the radio for Horus communication of frequency 1
  if (HORUS_FREQUENCY_1 != 0.0) {
    SetupHorus(HORUS_FREQUENCY_1);
    // Transmit!
    toSerialConsole("Transmitting Horus Binary v1 Packet on: ");
    toSerialConsole(HORUS_FREQUENCY_1);
    toSerialConsole("MHz\n");
    fsk4_idle(&radio);
    delay(100);
    fsk4_preamble(&radio, 8);
    fsk4_write(&radio, codedbuffer, coded_len);
    toSerialConsole("\n");
  }

  // Setup the radio for Horus communication of frequency 2
  if (HORUS_FREQUENCY_2 != 0.0) {
    SetupHorus(HORUS_FREQUENCY_2);
    // Transmit!
    toSerialConsole(F("Transmitting Horus Binary v1 Packet on: "));
    toSerialConsole(HORUS_FREQUENCY_2);
    toSerialConsole("MHz\n");
    fsk4_idle(&radio);
    delay(100);
    fsk4_preamble(&radio, 8);
    fsk4_write(&radio, codedbuffer, coded_len);
    toSerialConsole("\n");
  }
}

//============================================================================
// Send a Horus V2 packet over the radio
//============================================================================
void sendHorusV2() {
  int pkt_len;
  int coded_len;
  // Start Horus Binary V2
  toSerialConsole("Generating Horus Binary v2 Packet");

  // Generate packet for V2
  pkt_len = build_horus_binary_packet_v2(rawbuffer);
  PrintHex(rawbuffer, pkt_len, debugbuffer);
  toSerialConsole("Uncoded Length (bytes): ");
  toSerialConsole(pkt_len);toSerialConsole("\n");
  toSerialConsole("Uncoded: ");
  toSerialConsole(debugbuffer);toSerialConsole("\n");

  // Apply Encoding
  coded_len = horus_l2_encode_tx_packet((unsigned char*)codedbuffer, (unsigned char*)rawbuffer, pkt_len);
  PrintHex(codedbuffer, coded_len, debugbuffer);
  toSerialConsole("Encoded Length (bytes): ");
  toSerialConsole(coded_len); toSerialConsole("\n");
  toSerialConsole("Coded: ");
  toSerialConsole(debugbuffer); toSerialConsole("\n");


  // Setup the radio for Horus communication of frequency 1
  if (HORUS_FREQUENCY_1 != 0.0) {
    SetupHorus(HORUS_FREQUENCY_1);
    // Transmit!
    toSerialConsole("Transmitting Horus Binary v2 Packet on: ");
    toSerialConsole(HORUS_FREQUENCY_1);
    toSerialConsole("MHz\n");
    fsk4_idle(&radio);
    delay(100);
    fsk4_preamble(&radio, 8);
    fsk4_write(&radio, codedbuffer, coded_len);
    toSerialConsole("\n");
  }

  // Setup the radio for Horus communication of frequency 2
  if (HORUS_FREQUENCY_2 != 0.0) {
    SetupHorus(HORUS_FREQUENCY_2);
    // Transmit!
    toSerialConsole("Transmitting Horus Binary v2 Packet on: ");
    toSerialConsole(HORUS_FREQUENCY_2);
    toSerialConsole("MHz\n");
    fsk4_idle(&radio);
    delay(100);
    fsk4_preamble(&radio, 8);
    fsk4_write(&radio, codedbuffer, coded_len);
    toSerialConsole("\n");
  }
}

//============================================================================
// Send a Horus V3 packet over the radio
//============================================================================
void sendHorusV3() {
  int pkt_len;
  int coded_len;
  // Start Horus Binary V2
  toSerialConsole("Generating Horus Binary v3 Packet");

  // Generate packet for V3
  pkt_len = build_horus_binary_packet_v3(rawbuffer);
  PrintHex(rawbuffer, pkt_len, debugbuffer);
  toSerialConsole("Uncoded Length (bytes): ");
  toSerialConsole(pkt_len);toSerialConsole("\n");
  toSerialConsole("Uncoded: ");
  toSerialConsole(debugbuffer);toSerialConsole("\n");

  // Apply Encoding
  coded_len = horus_l2_encode_tx_packet((unsigned char*)codedbuffer, (unsigned char*)rawbuffer, pkt_len);
  PrintHex(codedbuffer, coded_len, debugbuffer);
  toSerialConsole("Encoded Length (bytes): ");
  toSerialConsole(coded_len); toSerialConsole("\n");
  toSerialConsole("Coded: ");
  toSerialConsole(debugbuffer);toSerialConsole("\n");

  // Setup the radio for Horus communication of frequency 1
  if (HORUS_FREQUENCY_1 != 0.0) {
    SetupHorus(HORUS_FREQUENCY_1);
    // Transmit!
    toSerialConsole("Transmitting Horus Binary v3 Packet on: ");
    toSerialConsole(HORUS_FREQUENCY_1);
    toSerialConsole("MHz\n");
    fsk4_idle(&radio);
    delay(100);
    fsk4_preamble(&radio, 8);
    fsk4_write(&radio, codedbuffer, coded_len);
    toSerialConsole("\n");
  }

  // Setup the radio for Horus communication of frequency 2
  if (HORUS_FREQUENCY_2 != 0.0) {
    SetupHorus(HORUS_FREQUENCY_2);
    // Transmit!
    toSerialConsole("Transmitting Horus Binary v3 Packet on: ");
    toSerialConsole(HORUS_FREQUENCY_2);
    toSerialConsole("MHz\n");
    fsk4_idle(&radio);
    delay(100);
    fsk4_preamble(&radio, 8);
    fsk4_write(&radio, codedbuffer, coded_len);
    toSerialConsole("\n");
  }
  
}


//============================================================================
// Send a LoRa APRS packet over the radio
//============================================================================
void sendLoRaAprs() {
  String aprs_packet;
  String lat = "";
  String lon = "";
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
  aprs_packet += "APETBT";  // destination callsign_APRS_DEST;
  // start of "real" data (Coordinates with timestamp)
  aprs_packet += ":@";
  // get the APRS timestamp
  aprs_packet += getAPRStimestamp();
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
  // Add the voltage only if it was defined in the settings file
#if defined(USE_VOLTAGE_IN_APRS)
  aprs_packet += " " + String(ReadVCC(),2) + "V";
#endif
#if defined(USE_BME280_TEMP_IN_APRS)
  aprs_packet += " " + String(bme280_temperature(),0) + "C"; 
#endif
#if defined(USE_BME280_PRESSURE_IN_APRS)
  aprs_packet += " " + String(bme280_pressure(),0) + "hPa"; 
#endif
#if defined(USE_BME280_HUMIDITY_IN_APRS)
  aprs_packet += " " + String(bme280_humidity(),0) + "%"; 
#endif
  aprs_packet += " " ;
  aprs_packet += LORA_APRS_CUSTOM_MESSAGE;


  if (LORA_APRS_WORLD_ENABLED) {
    toSerialConsole("Sending LoRa APRS packet on the world frequency\n");
    sendLoRa(aprs_packet, LORA_APRS_MODE);
  }

  if (LORA_APRS_PL_ENABLED && inPoland()) {
    toSerialConsole("Sending LoRa APRS packet on the Poland frequency\n");
    sendLoRa(aprs_packet, LORA_APRS_MODE_PL);
  }

  if (LORA_APRS_UK_ENABLED && inUK()) {
    toSerialConsole("Sending LoRa APRS packet on the UK frequency\n");
    sendLoRa(aprs_packet, LORA_APRS_MODE_UK);
  }
}


//============================================================================
// Send a tone on a specific frequency for calibration purposes
// You can enable this in the settings.h file
//============================================================================
void FreqCalibration(float Frequency) {
  toSerialConsole("Starting calibration...");

  // create FSK4 client instance using the FSK module
  FSK4Client fsk4(&radio);
  Radiolib_assert(radio.beginFSK());

  // Starting fsk4
  toSerialConsole("Starting Radio...");
  Radiolib_assert(fsk4.begin(Frequency, 270, 100));

  // Send a carrier for 10 seconds, wait 5 seconds, loop.
  while (true) {
    fsk4.idle();
    delay(10000);
    fsk4.standby();
    delay(5000);
  }  // go on forever
}

//============================================================================
// Put the radio in RX mode. enable this in settings. 
// LoRa should be enabled
//============================================================================
void StartReceiveLoRaPacket() {
  SetupLoRa(LORA_MODE);
#if defined(USE_SX127X)
  radio.setDio0Action(setFlag, RISING);  // As of RadioLib 6.0.0 all methods to attach interrupts no longer have a default level change direction
#else
  radio.setDio1Action(setFlag);
#endif

  if (LORA_MODE == 1) {
    Radiolib_assert(radio.startReceive(LoRaSettings.implicitHeader));
  } else {
    Radiolib_assert(radio.startReceive());
  }
  // If we get here, we are listening on the frequency
  toSerialConsole("[LoRa] Waiting for packets on: ");
  toSerialConsole(LoRaSettings.Frequency, 3);
  toSerialConsole(" MHz\n");
  toSerialConsole("----------------------------\n");
}

