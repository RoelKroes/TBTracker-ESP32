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

The code is written in the Arduino IDE for ESP32 with a GPS module and a LoRa module like the sx1278 or sx1276 or Hope RFM9x.

# Library
You will need two install two extra Arduino library from the librairy manager:
- Radiolib
- TinyGPS++

# Hardware
The minimal hardware configuration you need is:
- ESP32 or ESP32S2 board
- GPS module (recommended Ublox Neo or ATGM336H)
- Lora module (sx1278 or sx1276 or Hope RFM9x module)

# Installation
Connect your LoRa and GPS modules to your ESP board and change the values in the settings.h file.See the comments in the settings.h file.

# Versions

V0.1.0:

- Initial commit
