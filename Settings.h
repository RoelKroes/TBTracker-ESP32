//============================================================================
// Important: CHANGE THE SETTINGS BELOW so it matches your configuration
//============================================================================

//============================================================================
// Comment out the line below if you do NOT want Serial console output
// If ALLOWDEBUG is defined, the program will output data to the serial
// console for debugging and general info
// It is recommended you leave this defined when testing your tracker
//============================================================================
#define ALLOWDEBUG

//============================================================================
// PIN NUMBERS for the RF modules and SPI interface
//  
// Change if needed
// the default pins for my ESP32-S2 are: SCK=36, MISO=37, MOSI=35, CS=34 
//
// But you can redefine the SPI pins by creating defines: 
// #define SCK 36
// #define MISO 37
// #define MOSI 35
// #define CS 34
//
// SPI interface pins for Freenove ESP32-S3 WROOM with camera
//#define SCK 47
//#define MISO 14
//#define MOSI 21
//#define CS 1
//============================================================================
// SPI interface pin numbers
#define SCK 36
#define MISO 37
#define MOSI 35
#define CS 34

//============================================================================
// Define which radiochip you use
// Comment out the one you do not use
// Currently sx1278, sx1262, sx1268, LLCC68 and the RF69 are supported
//
//  sx1278: RTTY, Horus, LoRa, LoRa-APRS, APRS, RX, SSDV LoRa mode 1 and 2 
//  sx1276: RTTY, Horus, LoRa, LoRa-APRS, APRS, RX, SSDV LoRa mode 1 and 2  
//  sx1262: RTTY, Horus, LoRa, LoRa-APRS, APRS, RX, SSDV LoRa mode 2 (recommended RF module for all Horus modes)
//  sx1268: RTTY, Horus, LoRa, LoRa-APRS, APRS, RX, SSDV LoRa mode 2 (recommended RF module for all Horus modes)
//  LLCC68: RTTY, Horus, LoRa, APRS (not recommended for LoRa, only bw 125, 250 and 500kHz are upported)
//    RF69: RTTY, Horus, APRS
//
//  For Horus all modules have a tone spacing of 270 except for the sx127x and
//  RF69 modules which have a tone spacing of 244. 
//============================================================================
#define USE_SX127X
// #define USE_LLCC68
// #define USE_SX1268
// #define USE_SX1262  
// #define USE_RF69 

//============================================================================
// Define the use of a TCXO
// Enter the voltage for the TCXO
// Possible values are 1.6 or 0
// Most of the time the sx126x needs 1.6 (with TCXO) and the sx127x needs 0.0 (without TCXO)
// If you pick the wrong value, you will usually get an error -707
//============================================================================
// Possible values are 1.6 or 0
#define USE_TCXO 0.0

//============================================================================
// Define the pin numbers for the connection from the esp32 to the RF module
// Not all pin numbers are used for the different RF modules
// For the sx127x series: PIN_NSS, PIN_DIO0, PIN_RESET, PIN_DIO1 (and PIN_DIO2 is you use AFSK APRS)
// For the SX126x and LLCC68 series: PIN_NSS, PIN_DIO1, PIN_RESET, PIN_BUSY (and PIN_DIO2 if you use AFSKL APRS)
// For the RF69: PIN_NSS, PIN_DIO0, PIN_RESET
//
// Use the pins below for the esp32s3 with camera 
//#define PIN_NSS 1
//#define PIN_DIO0 41
//#define PIN_BUSY -1     
//#define PIN_RESET 42
//#define PIN_DIO1 20
//
//#define PIN_DIO2 -1  
//============================================================================
#define PIN_NSS 34
#define PIN_DIO0 38
#define PIN_BUSY 4     
#define PIN_RESET 33
#define PIN_DIO1 3

// PIN_DI02 is only used for AFSK-APRS
// SX127x/RF69/SX126x/LLCC68 all can do AFSK-APRS when DIO2 is connected to the esp32
#define PIN_DIO2 4  

//============================================================================
// Enable these lines if you want to use a voltage divider to read voltage information
// A template of the code for the voltage divider is in ADC.ino. Or you can write
// your own code. 
//
// Voltage Divider Schematic
//
//      Vin (Battery or Solar)
//      |
//      R1
//      |
//      +---- Voltage_in_pin (Pin x from ESP32)
//      |   
//      R2
//      |
//      GND
//
// Comment the five lines below out if you do not use a voltage divider
// Use the pins below for the esp32s3 with camera 
// #define VOLTAGE_IN_PIN 3
//============================================================================
//#define USE_VOLTAGE_INFO          // Uncomment this if you use a voltage divider
//#define VOLTAGE_IN_PIN 2          // Pin number to which the voltage divider is connected
//#define VOLTAGE_DIVIDER_R1 100000 // in Ohm 100K is a good value for voltage between 2 and 6 volts
//#define VOLTAGE_DIVIDER_R2 100000 // in Ohm 100K is a good value for voltage between 2 and 6 volts
//#define VOLTAGE_DEVIATION  0.0    // Will be added as an error offset to the calculated result of the voltage divider.In a perfect world this should be 0.00.
//
//#define USE_VOLTAGE_IN_APRS     // If you uncomment this, the voltage information will be added to the APRS comment field

//============================================================================
// Enable this if you have a BME280 sensor installed.
// A template of the code for the BME280 is in bme280.ino. Or you can write
// your own code. 
// 
// Use the pins below for the esp32s3 with camera 
//#define SDA_PIN 46  // your SDA pin for the I2C protocol (needed for BME280 sensor)
//#define SCL_PIN 2  // your SCL pin for the I2C protocol (needed for BME280 sensor) 
//
// Comment the lines below out if you do not use a bme280 sensor
//============================================================================
//#define USE_BME280 // Uncomment this line if you use a BME280 sensor
//#define SDA_PIN 8  // your SDA pin for the I2C protocol (needed for BME280 sensor)
//#define SCL_PIN 9  // your SCL pin for the I2C protocol (needed for BME280 sensor) 
//#define USE_BME280_TEMP_IN_APRS     // If you uncomment this, the temperature reading from the BME280 will be added to the APRS comment field
//#define USE_BME280_PRESSURE_IN_APRS // If you uncomment this, the pressure reading from the BME280 will be added to the APRS comment field
//#define USE_BME280_HUMIDITY_IN_APRS // If you uncomment this, the humidity reading from the BME280 will be added to the APRS comment field


//============================================================================
// Enable this if you want to calibrate your radio module.
// It will send a 10 second carrier on the CAL_FREQUENCY, 5 seconds of silence, 10 second carrier, and so on
// Tweak the CAL_OFFSET_FREQUJENCY frequency until you get the best result
// Use the offset in the Horus and LoRa settings 
// If you use this software as a balloon tracker, try experimenting with ice spray to 
// simulate high altitude temperatures
// Frequencies are in MHz.
//============================================================================
// Enable the three defines below to enter calibration mode
// #define CALIBRATE_RADIO
// #define CAL_FREQUENCY 433.090
// #define CAL_OFFSET_FREQUENCY -0.000

//============================================================================
// RTTY SETTINGS
//  
// Personalize when you have RTTY_ENABLED set to true and you want RTTY transmissions
// I consider this mode more or less deprecated and I will probably remove this mode in future releases
//============================================================================
#define RTTY_ENABLED false        // Set to true if you want RTTY transmissions
#define RTTY_PAYLOAD_ID "MYCALL"  // This will show on Sondehub. Payload ID for RTTY protocol. CHANGE THIS!
#define RTTY_FREQUENCY 437.600    // in MHz
#define RTTY_SHIFT 610            // 610 is usually a good value. 
#define RTTY_BAUD 100             // Baud rate. You should set this to 50 or 100 usually
#define RTTY_STOPBITS 2           // Usually leave this at 2
#define RTTY_PREFIX "$$$$$$"      // As RTTY with the sx12xx series chips is challenging, prefix with at least 4x$
#define RTTY_REPEATS 1            // number of RTTY transmits during a cycle, usually set to 1
#define RTTY_LOOPTIME 40          // Transmit RTTY every xx seconds
#define RTTY_IDLE_TIME 4000       // Idle carrier in ms before sending actual RTTY string. \
                                  // Set to a low value (i.e. 1000 or lower) if you have a very frequency stable signal 
                                  // Set to a high value (i.e. 5000 or even higher) if you have a hard time to tune and decode the signal

//============================================================================
// SSDVsettings
// Currently TBTracker only supports the Freenove ESP32-S3 WROOM series board with camera 
// module. In the Arduino interface set the board to ESP32S3 Dev Module.
// IF YOU USE SSDV, YOU NEED TO ENABLE LORA MODE 1 or 2 AS WELL!
// Pin assignments are critical. Below is a working combination for the esp32-S3 N16R8 WROOM:
// 
// For the SPI interface
// #define SCK 47
// #define MISO 14
// #define MOSI 21
// #define CS 1
//
// For the I2C interface 
// #define SDA_PIN 46  
// #define SCL_PIN 2  
// 
// For the GPS connection
// static const int Rx = -1, Tx = 19;
//
// For the voltage divider
// #define VOLTAGE_IN_PIN 3
//============================================================================
// The main SSDV master switch. Enable the line below if you want to use SSDV
// Otherwise leave it commented out.
// #define USE_SSDV   

// Freenove ESP32-S3 WROOM (or one of the manycompatibles) is the camera interface. Currently the only camera interface we tested.
// But you can try others as defined in camera_pins.h. If you manage to get others working, please let me know with the correct pin numbers
// Some lenses have a tiny coil motor to control focus (i.e. OV2640AF). However these lenses are very rare and this software
// does not support AF lenses yet. I recommend to "pre-focus" the lens before launch. Turn the lens against the clock 
// for focus close by and with the clock for focus in the distance. Usually the lens is lightly glued to the camera.
// SETTINGS BELOW ONLY WORK IF THE LINE #DEFINE USE_SSDV IS UNCOMMENTED
#define CAMERA_MODEL_ESP32S3_EYE
#define FLIP_HORIZONTAL true      // Camera is usually mounted in selfie mode. Set to true if the picture needs mirroring hotizontally
#define FLIP_VERTICAL false       // Set to true if the picture needs mirroring vertically (usually not the case)

// High res settings (save to SD)
#define SSDV_HIGHRES true         // Set to true if you want to take high res pictures and save those to SD card 
#define SSDVHIGHRES_LOOPTIME 30   // take a high res picture and save to SD every xx seconds 
#define HIGHRES_RESOLUTION  4     // 1 = 1600x1200 (all sensors, OV2640, OV3660 and OV5640)
                                  // 2 = 1920x1080 (3MP and 5MP sensors, OV3660 and OV5640) 
                                  // 3 = 2048x1536 (3MP and 5MP sensors, OV3660 and OV5640) 
                                  // 4 = 2560x1440 (5MP sensors, OV5640)  2K
#define HIGHRES_QUALITY 10        // 0..63 with 0=best, 63=worst. 10 is very good quality.                                  

// Low res settings (send over LoRa, Highres pictures will be delayed as no highres pics can be taken before the lowres is sent over LoRa)
#define SSDV_LOWRES  true        // Set to true if you want to send low res images over LoRa Mode 1
#define CALLSIGN_SSDV "MY_CAM"   // max 6 chars!
#define LOWRES_RESOLUTION 2      // 1=320x240, 2=640x480, 3=800x600, 4=1024x768
#define LOWRES_QUALITY 4         // 0..7 with 7=best. Above 4 the improvements were not detectable

//============================================================================
// LORA SETTINGS
//  
// Personalize when you have LORA_ENABLED set to true and you want LORA transmissions
// About HAB modes:
// 0 = (normal for telemetry,     60 baud)  Explicit mode, Error coding 4:8, Bandwidth 20.8kHz, SF 11,Low data rate optimize on  - SUPPORTED
// 1 = (normal for SSDV,        1400 baud)  Implicit mode, Error coding 4:5, Bandwidth 20.8kHz, SF 6, Low data rate optimize off - SUPPORTED
// 2 = (normal for repeater,    2000 baud)  Explicit mode, Error coding 4:8, Bandwidth 62.5kHz, SF 8, Low data rate optimize off - SUPPORTED
// 3 = (normal for fast SSDV,   8000 baud)  Explicit mode, Error coding 4:6, Bandwidth 250kHz,  SF 7, Low data rate optimize off - SUPPORTED
// 4 = (Turbo SSDV,            16828 baud)  Explicit mode, Error coding 4:5, Bandwidth 250kHz,  SF 6, Low data rate optimize off - SUPPORTED
// 5 = (normal for calling mode, 200 baud)  Explicit mode, Error coding 4:8, Bandwidth 41.7kHz, SF 11,Low data rate optimize off - SUPPORTED
// 6 = (uplink 868,             2800 baud)  Explicit mode, Error coding 4:5, Bandwidth 41.7kHz, SF 6, Low data rate optimize off - SUPPORTED
// 7 = (Telnet comms 434,       2800 baud)  Explicit mode, Error coding 4:5, Bandwidth 20.8kHz, SF 7, Low data rate optimize off - SUPPORTED
// 8 = (SSDV repeater,          4500 baud)  Explicit mode, Error coding 4:5, Bandwidth 62.5kHz, SF 6, Low data rate optimize off - SUPPORTED
//============================================================================
#define LORA_ENABLED false        // Set to true if you want LoRa transmissions
#define RECEIVING_ENABLED false  // Set to true if you want the tracker to listen on the LoRa frequency for incoming packets
#define LORA_PAYLOAD_ID "MYCALL-L"   // This will show on Sondehub. Payload ID for LoRa protocol. CHANGE THIS!
#define LORA_FREQUENCY 432.662   // in MHz
#define LORA_MODE 2              // Mode 2 is usually used for simple telemetry data or fast SSDV
                                 // Mode 1 is usually used for low bandwidth SSDV
                                 // Mode 2 is faster than mode 1 for ssdv but uses more bandwidth
                                 // If you have a sx126x you best use mode 2 as mode 1 sometimes does not decode with some chinese chips.
                                 // sx127x works fine with both modes
                                 // I did not test the other modes
#define LORA_REPEATS 1           // number of LoRa transmits during a cycle
#define LORA_LOOPTIME 45         // Transmit LoRa every xx seconds
#define LORA_FREQ_OFFSET 0.0     // Frequency deviation in MHz. Will be added to the LoRa frequency. Should be a float and can be negative.

//============================================================================
// LORA-APRS SETTINGS
//  
// Personalize when you have LORA_APRS_ENABLED set to true and you want LORA-APRS transmissions 
//============================================================================
#define LORA_APRS_ENABLED false          // Set to true if you want LORA-APRS transmissions at all, also select (multiple) APRS frequencies below
#define LORA_APRS_WORLD_ENABLED true     // Set to true if you want LORA-APRS transmissions on the world frequency 433.775 (LORA_APRS_ENABLED must be set to true)
#define LORA_APRS_PL_ENABLED true        // Set to True if you want LORA-APRS transmissions on the Poland frequency 434.855 (LORA_APRS_ENABLED must be set to true)
#define LORA_APRS_UK_ENABLED true        // Set to True if you want LORA-APRS transmissions on the UK frequency 439.9125 (LORA_APRS_ENABLED must be set to true)
#define LORA_APRS_PAYLOAD_ID "NOCALL"    // CHANGE THIS. This will show on Sondehub. For LORA-APRS this should be a HAM call without SSID.
#define LORA_APRS_SSID "-11"             // 11 is the symbol for balloon. Use quotes like this: "-11"
#define LORA_APRS_MODE 99                // Do not change
#define LORA_APRS_MODE_PL 98             // Do not change
#define LORA_APRS_MODE_UK 97             // Do not change
#define LORA_APRS_FREQUENCY 433.775      // LORA-APRS is worldwide on 433.775 MHz at about 300bd, do not change
#define LORA_APRS_FREQUENCY_PL 434.855   // LORA-APRS used in Poland on 434.855 at about 1200bd
#define LORA_APRS_FREQUENCY_UK 439.9125  // LORA-APRS used in the UK on 439.9125 at about 300bd
#define LORA_APRS_LOOPTIME 180           // Set this rather high (>120s), so you won't be flagged for misusing the APRS network
#define LORA_APRS_FREQ_OFFSET 0.0        // Frequency deviation in MHz. Will be added to the LoRa APRS frequency. Should be a float and can be negative.
#define LORA_APRS_CUSTOM_MESSAGE "BALLOON" // Custom message that will be added to the LoRa APRS telemetry and will be visible on APRS and Sondehub. Use quotes.

//============================================================================
// HORUSBINARY SETTINGS
//  
// Personalize when you have HORUS_V*_ENABLED set to true and you want HORUS transmissions
//============================================================================
//============================================================================
// Set your Payload IDs for HorusV1 or HorusV2
// Please refer to: https://github.com/projecthorus/horusdemodlib/blob/master/payload_id_list.txt
//
// If you do not have a payload ID, you can use 0 (=4FSKTEST) for V1 and 256 (=4FSKTEST-V2) for V2:
//#define PAYLOAD_ID_V1  0
//#define PAYLOAD_ID_V2  256
//
// HORUS V3 is currently the preferred mode.
//============================================================================
#define HORUS_V1_ENABLED false       // Set to true if you want HorusBinary V1 transmissions (you can do V1, V2 and V3 transmissions on the same tracker)
#define HORUS_V2_ENABLED false       // Set to true if you want HorusBinary V2 transmissions
#define HORUS_V3_ENABLED false       // Set to true if you want HorusBinary V3 transmissions (recommended Horus mode)
#define HORUS_V3_CALLSIGN "MYCALL"   // Horus V3 callsign and is free to choose but keep it AS SHORT AS POSSIBLE (adding V3 in the call is not necessary and not recommended)
#define HORUS_V3_CUSTOM_FIELDS       // if defined will include custom fields into the Horus transmission
                                     // two fields have been already added as custom fields in this code:
                                     // 1. gps speed (currently set to 'do not show' in TBTracker-ESP32.ini)
                                     // 2. RF chip
                                     // You can change this in the code or leave it as is
                                     // Note that including custom fields will SIGNIFICANTLY increase transmission length!
                                     // Just comment the line out if you do not want custom fields
#define PAYLOAD_ID_V1 0              // For Horus V1. See above. Set to 0 if you do not have a payload ID
#define PAYLOAD_ID_V2 256            // For Horus V2. See above. Set to 256 if you do not have a payload ID
#define HORUS_FREQUENCY_1 437.600    // Horus can transmit on two frequencies (434.714, 437.600 is kind of standard in Europe )
#define HORUS_FREQUENCY_2 434.714    // Just set to 0.0 if you only want 1 frequency
#define HORUS_POWER 13               // In dBm. Valid values +2 to +17 dBm. 10dBm = 10mW, 13dBm=20mW (recommended)
#define HORUS_BAUD 100               // recommended 50 (8MHz processor) or 100 baud (16MHz, better processor or esp32)
#define HORUS_SPACING 270            // NOTE: This results in a shift of 244 Hz on the sx127x and RF69 due to the PLL Resolution of those chips is 61Hz
#define HORUS_LOOPTIME 40            // Transmit Horus every xx seconds
#define HORUS_FREQ_OFFSET 0.0        // Frequency deviation in MHz. This will be added to HORUS_FREQUENCY

//============================================================================
// "Standard" AFSK APRS SETTINGS
// This is very experimental. The analog tones are simultated through PCM block waves.
// Personalize when you have AFSK_APRS set to true and you want APRS transmissions
//
// At this moment, AFSK APRS only works for boards using the original ESP32 MCU's (which are in the T-BEAM's and LILYGO boards)
// AFSK APRS does currently not work reliable for the Sx and Cx ESP32 series. But we are working on that :-)
//============================================================================
#define APRS_AFSK_ENABLED false      // Set this to true if you want APRS transmissions
#define APRS_AFSK_CALLSIGN "NOCALL"  // CHANGE THIS and use quotation marks. This will show on Sondehub. For APRS this should be a HAM call without SSID.
#define APRS_AFSK_LOOPTIME 180       // Transmit APRS every xx seconds. Set this to something >= 120 seconds
#define APRS_AFSK_SSID 11            // SSID. You can use 11 for a HAM balloon
#define APRS_AFSK_PREAMBLE 100       // I got good results with 100 but you can go as low as 8
#define APRS_AFSK_POWER 13           // In dBm. Valid values +2 to +17 dBm. 10dBm = 10mW, 13dBm=20mW
#define APRS_AFSK_FREQUENCY 432.500  // 70cm APRS frequency. Seems still experimental
#define APRS_AFSK_FREQ_OFFSET 0.0    // Frequency deviation in MHz. This will be added to APRS_AFSK_FREQUENCY

//============================================================================
// GPS SETTINGS
//  
// Change if needed
// For the esp32s3 with camere use: static const int Rx = -1, Tx = 19;
//============================================================================
// GPS Serial device pin numbers
static const int Rx = 40, Tx = 39;     // This will probably be different for your board
static const uint32_t GPSBaud = 9600;  // modern devices are 9600 baud. some are 4800 baud.

//============================================================================
// TRANSMISSIONS SETTINGS
//   
// Change if needed
//============================================================================
#define SENTENCE_LENGTH 100  // Maximum length of telemetry line to send

//============================================================================
// SONDEHUB EXTRA FIELDS SETTINGS for LoRa and RTTY transmissions (not used for Horus)
//  
// For displaying extra fields at sondehub, we need to define which fields are
// in the telemetry after the lat, lon, alt fields
// This can be done by adding a specific string after the last telemetry field
// This is supported by the various receivers made by Dave Akerman,
// See: https://www.daveakerman.com/?page_id=2410
// 
// 0  PayloadID
// 1 Counter
// 2 Time
// 3 Latitude
// 4 Longitude
// 5 Altitude
// 6 Satellites
// 7 Speed
// 8 Heading
// 9 Battery Voltage
// A InternalTemperature
// B ExternalTemperature
// C PredictedLatitude
// D PredictedLongitude
// E CutdownStatus
// F LastPacketSNR
// G LastPacketRSSI
// H ReceivedCommandCount
// I-N ExtraFields
// O MaximumAltitude
// P Battery Current
// Q External Temperature 2
// R Pressure
// S Humidity
// T CDA
// U Predicted Landing Speed
// V Time Till Landing
// W Last Command Received
// 
// You can disable FIELDSTR by undefining it, if you want.
//============================================================================
// If you disable USE_FIELDSTR, the software will only send GPS info.

// If you enable USE_FIELDSTR, the software will also send temperature, voltage, humidity en air pressure
// You will need additional sensors for that and configure those in the software
// TB-Tracker at this moment only supports voltage dividers and BME280 sensors
#define USE_FIELDSTR
#define FIELDSTR "01234569"

//============================================================================
// DEFAULT RTTY SETTINGS
//  
// Normally needs no change
//============================================================================
#define RTTY_ASCII 0           // 7 data bits
#define RTTY_ASCII_EXTENDED 1  // 8 data bits
#define RTTY_ITA2 2            // Baudot

//============================================================================
// DEFAULT LORA SETTINGS
//  
// Normally needs no change / for testing purposes
//============================================================================
#define LORA_BANDWIDTH 125.0  // Do not change, change LORA_MODE instead
#define LORA_SPREADFACTOR 9   // Do not change, change LORA_MODE instead
#define LORA_CODERATE 7       // Do not change, change LORA_MODE instead
#define LORA_PREFIX "$$"      // Prefix for "Telemetry". Some older LoRa software does not accept a prefix of more than 2x "$"
#define LORA_SYNCWORD 0x12    // Default syncword
#define LORA_POWER 13         // in dBm between 2 and 17. 10 = 10mW (recommended)
#define LORA_CURRENTLIMIT 100
#define LORA_PREAMBLELENGTH 8
#define LORA_GAIN 0

//============================================================================
// DEFAULT FSK SETTINGS
//  
// You can change this and it will alter the default FSK settings
// Some of these settings are overridden in the setup of the different modes (see above)
//============================================================================
#define FSK_FREQUENCY 434.0
#define FSK_BITRATE 4.8
#define FSK_FREQDEV 5.0
#define FSK_RXBANDWIDTH_sx127 125.0
#define FSK_RXBANDWIDTH_sx126 156.2 
#define FSK_POWER 10  // default power setting in dBm between 2 and 17. 10 = 10mW. Sets also RTTY power
#define FSK_PREAMBLELENGTH 16
#define FSK_ENABLEOOK false
#define FSK_DATASHAPING 0.5
#define FSK_USERREGULATORLDO false
