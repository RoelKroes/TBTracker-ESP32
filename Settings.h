/***********************************************************************************
* Important: CHANGE THE SETTINGS BELOW so it matches your configuration
************************************************************************************/

/***********************************************************************************
* PIN NUMBERS for SX127x
*  
* Change if needed
* the default pins for my ESP32-S2 are: SCK=36, MISO=37, MOSI=35, NSS=34 
* But you can redefine the SPI pins by creating defines: 
* #define SCK 36
* #define MISO 37
* #define MOSI 35
* #define CS 34
************************************************************************************/
#define SCK 5
#define MISO 19
#define MOSI 27
#define CS 18

#define PIN_NSS   18
#define PIN_DIO0  26
#define PIN_BUSY  -1  // Not used in this sketch for sx1278
#define PIN_RESET 23  
#define PIN_DIO1  -1  // Not used in this sketch for sx1278

/***********************************************************************************
* Enable the different protocols for transmission.
* You can choose one, more or all
* See below for the settings for the different protocols
************************************************************************************/
#define RTTY_ENABLED false      // Set to true if you want RTTY transmissions
#define LORA_ENABLED true       // Set to true if you want LoRa transmissions
#define RECEIVING_ENABLED false // Set to true if you want the Tracker to listen on the LoRa frequency for incoming packets
#define HORUS_V1_ENABLED false  // Set to true if you want HorusBinary V1 transmissions
#define HORUS_V2_ENABLED false  // Set to true if you want HorusBinary V2 transmissions
#define LORA_APRS_ENABLED false // Set to true if you want LORA-APRS transmissions (experimental)

/***********************************************************************************
* RTTY SETTINGS
*  
* Personalize when you have RTTY_ENABLED set to true and you want RTTY transmissions
* Default RTTY setting is: 7,N,2 at 100 Baud.
************************************************************************************/
#define RTTY_PAYLOAD_ID  "MYCALL" // This will show on Sondehub. Payload ID for RTTY protocol. CHANGE THIS!
#define RTTY_FREQUENCY  433.775    // in MHz
#define RTTY_SHIFT 610             // in increments of 61. 610 is usually a good value.
#define RTTY_BAUD 100              // Baud rate. You should set this to 50 or 100 usually
#define RTTY_STOPBITS 2            // Usually leave this at 2 
#define RTTY_PREFIX "$$$$$$"       // As RTTY with the sx127x chip is challenging, prefix with at least 4x$   
#define RTTY_REPEATS 1             // number of RTTY transmits during a cycle, usually set to 1 
#define RTTY_LOOPTIME 45           // Transmit RTTY every xx seconds
#define RTTY_IDLE_TIME 4000        // Idle carrier in ms before sending actual RTTY string. 
                                   // Set to a low value (i.e. 1000 or lower) if you have a very frequency stable signal
                                   // Set to a high value (i.e. 5000 or even higher) if you have a hard time to tune the signal

/***********************************************************************************
* LORA SETTINGS
*  
* Personalize when you have LORA_ENABLED set to true and you want LORA transmissions
* About HAB modes:
* 0 = (normal for telemetry,     60 baud)  Explicit mode, Error coding 4:8, Bandwidth 20.8kHz, SF 11,Low data rate optimize on  - SUPPORTED
* 1 = (normal for SSDV,        1400 baud)  Implicit mode, Error coding 4:5, Bandwidth 20.8kHz, SF 6, Low data rate optimize off - SUPPORTED
* 2 = (normal for repeater,    2000 baud)  Explicit mode, Error coding 4:8, Bandwidth 62.5kHz, SF 8, Low data rate optimize off - SUPPORTED
* 3 = (normal for fast SSDV,   8000 baud)  Explicit mode, Error coding 4:6, Bandwidth 250kHz,  SF 7, Low data rate optimize off - SUPPORTED
* 4 = (Turbo SSDV,            16828 baud)  Explicit mode, Error coding 4:5, Bandwidth 250kHz,  SF 6, Low data rate optimize off - SUPPORTED
* 5 = (normal for calling mode, 200 baud)  Explicit mode, Error coding 4:8, Bandwidth 41.7kHz, SF 11,Low data rate optimize off - SUPPORTED
* 6 = (uplink 868,             2800 baud)  Explicit mode, Error coding 4:5, Bandwidth 41.7kHz, SF 6, Low data rate optimize off - SUPPORTED
* 7 = (Telnet comms 434,       2800 baud)  Explicit mode, Error coding 4:5, Bandwidth 20.8kHz, SF 7, Low data rate optimize off - SUPPORTED
* 8 = (SSDV repeater,          4500 baud)  Explicit mode, Error coding 4:5, Bandwidth 62.5kHz, SF 6, Low data rate optimize off - SUPPORTED
* 99 = (World wide LoRa-APRS mode at 433.775MHz, Explicit mode, Error coding 4:5, Bandwidth 125kHz, SF 12,Low data rate optimize off - SUPPORTED  )
************************************************************************************/
#define LORA_PAYLOAD_ID  "MYCALL-L"  // This will show on Sondehub. Payload ID for LoRa protocol. CHANGE THIS!
#define LORA_FREQUENCY  432.662     // in MHz
#define LORA_MODE 2                 // Mode 2 is usually used for simple telemetry data
#define LORA_REPEATS 1              // number of LoRa transmits during a cycle
#define LORA_LOOPTIME 120            // Transmit LoRa every xx seconds

/***********************************************************************************
* LORA-APRS SETTINGS
*  
* Personalize when you have LORA_APRS_ENABLED set to true and you want LORA-APRS transmissions
************************************************************************************/
#define LORA_APRS_PAYLOAD_ID  "MYCALL"  // CHANGE THIS. This will show on Sondehub. For LORA-APRS this should be a HAM call without SSID.
#define LORA_APRS_SSID "-11"            // 11 is the symbol for balloon
#define LORA_APRS_MODE 99                     
#define LORA_APRS_FREQUENCY  433.775  // LORA-APRS is worldwide on 433.775 MHz, do not change
#define LORA_APRS_LOOPTIME 120        // Set this rather high (>120s), so you won't be flagged for misusing the APRS network


/***********************************************************************************
* HORUSBINARY SETTINGS
*  
* Personalize when you have HORUS_V*_ENABLED set to true and you want HORUS transmissions
************************************************************************************/
//**********************************************************************************
// Set your Payload IDs
// Please refer to: https://github.com/projecthorus/horusdemodlib/blob/master/payload_id_list.txt
//
// If you do not have a payload ID, you can use 0 (=4FSKTEST) for V1 and 256 (=4FSKTEST-V2) for V2:
//#define PAYLOAD_ID_V1  0
//#define PAYLOAD_ID_V2   256
//**********************************************************************************
#define PAYLOAD_ID_V1  0
#define PAYLOAD_ID_V2   256
#define HORUS_FREQUENCY 437.600
#define HORUS_POWER        10   // In dBm. Valid values +2 to +17 dBm. 10dBm = 10mW, 13dBm=20mW
#define HORUS_BAUD         100  // recommended 50 (8MHz processor) or 100 baud (16MHz or better processor)
#define HORUS_SPACING      270  // NOTE: This results in a shift of 244 Hz due to the PLL Resolution of the SX127x which is 61Hz
#define HORUS_LOOPTIME     45   // Transmit Horus every xx seconds

/***********************************************************************************
* GPS SETTINGS
*  
* Change if needed
************************************************************************************/
// GPS Serial device
static const int Rx = 15, Tx = 12;  // This will probably be different for your board
static const uint32_t GPSBaud = 9600;

/***********************************************************************************
* TRANSMISSIONS SETTINGS
*   
* Change if needed
************************************************************************************/
#define SENTENCE_LENGTH 100     // Maximum length of telemetry line to send

/***********************************************************************************
* SONDEHUB EXTRA FIELDS SETTINGS
*  
* For displaying extra fields at sondehub, we need to define which fields are
* in the telemetry after the lat, lon, alt fields
* This can be done by adding a specific string after the last telemetry field
* This is supported by the various receivers made by Dave Akerman,
* See: https://www.daveakerman.com/?page_id=2410
* 
* 0  PayloadID
* 1 Counter
* 2 Time
* 3 Latitude
* 4 Longitude
* 5 Altitude
* 6 Satellites
* 7 Speed
* 8 Heading
* 9 Battery Voltage
* A InternalTemperature
* B ExternalTemperature
* C PredictedLatitude
* D PredictedLongitude
* E CutdownStatus
* F LastPacketSNR
* G LastPacketRSSI
* H ReceivedCommandCount
* I-N ExtraFields
* O MaximumAltitude
* P Battery Current
* Q External Temperature 2
* R Pressure
* S Humidity
* T CDA
* U Predicted Landing Speed
* V Time Till Landing
* W Last Command Received
* 
* Our string would be: "01234568A9"
* You can disable FIELDSTR by undefining it, if you want.
************************************************************************************/
#define USE_FIELDSTR
#define FIELDSTR "01234568A9"

/***********************************************************************************
* DEFAULT RTTY SETTINGS
*  
* Normally needs no change
************************************************************************************/  
#define RTTY_ASCII 0               // 7 data bits 
#define RTTY_ASCII_EXTENDED 1      // 8 data bits
#define RTTY_ITA2  2               // Baudot 

/***********************************************************************************
* DEFAULT LORA SETTINGS
*  
* Normally needs no change
************************************************************************************/
#define LORA_BANDWIDTH 125.0         // Do not change, change LORA_MODE instead
#define LORA_SPREADFACTOR 9          // Do not change, change LORA_MODE instead
#define LORA_CODERATE 7              // Do not change, change LORA_MODE instead
#define LORA_PREFIX "$$"             // Prefix for "Telemetry". Some older LoRa software does not accept a prefix of more than 2x "$"
#define LORA_SYNCWORD 0x12           // Default syncword
#define LORA_POWER 13                // in dBm between 2 and 17. 10 = 10mW (recommended)
#define LORA_CURRENTLIMIT 100
#define LORA_PREAMBLELENGTH 8
#define LORA_GAIN 0

/***********************************************************************************
* DEFAULT FSK SETTINGS
*  
* Normally needs no change
************************************************************************************/
#define FSK_FREQUENCY 432.662
#define FSK_BITRATE 100.0
#define FSK_FREQDEV 50.0
#define FSK_RXBANDWIDTH 125.0
#define FSK_POWER 13   // in dBm between 2 and 17. 10 = 10mW (recommended). Sets also RTTY power
#define FSK_PREAMBLELENGTH 16
#define FSK_ENABLEOOK false
#define FSK_DATASHAPING 0.5
