# TBTracker-ESP32
A Plug and Play High Altitude Balloon tracker for ESP32. Supports LoRa, LoRa-APRS, RTTY, Horus V1 4FSK, Horus V2 4FSK.

TBTracker-ESP32 is an Arduino sketch for a tracker for high altitude weather or scientific balloons. 
It supports sending telemetry data in mulitple formats:
- RTTY
- LoRa
- LoRa-APRS
- Horus 4FSK V1
- Horus 4FSK V2

You can select multiple modes or just a single mode.

It is designed to send telemetry data in the correct format for https://amateur.sondehub.org.
As of v0.2.0 it is also capable of receiving LoRa packets and act upon that (experimental).

The code is written in the Arduino IDE for ESP32 with a GPS module and a LoRa module like the sx1278 or sx1276 or Hope RFM9x.

# Library
You will need to install two extra Arduino library from the librairy manager:
- Radiolib
- TinyGPS++

# Hardware
The minimal hardware configuration you need is:
- ESP32 or ESP32S2 board
- GPS module (recommended Ublox Neo or ATGM336H)
- Lora module (sx1278 or sx1276 or Hope RFM9x module)

# Horusbinary_radiolib
The radio related basecode for this sketch was taken from the horusbinary_radiolib project.
See: https://github.com/projecthorus/horusbinary_radiolib

# Installation
Connect your LoRa and GPS modules to your ESP board and change the values in the settings.h file.See the comments in the settings.h file. Compile in the Arduino IDE and upload to your board.

# Versions

V0.1.0:
- Initial commit
- 
V0.1.1:  
- Added a temporary APRS device-ID (APZTBT)
- Added a timestamp to to the APRS packets for better compatibility with Sondehub

V0.2.0:
- TBTracker got assigned its own APRS device-ID (APETBT). This is "hardcoded" into the source. Please do not change this ID, as it is used by APRS to identify the APRS packets as coming from TBTracker
- TBTracker can now receive LoRa packets and act upon it. This can be used to release payloads or do other things. You need to enable it in settings.h. LoRa needs to enabled and RX will use the same settings as TX.

