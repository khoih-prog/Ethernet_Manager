## Ethernet_Manager

[![arduino-library-badge](https://www.ardu-badge.com/badge/Ethernet_Manager.svg?)](https://www.ardu-badge.com/Ethernet_Manager)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Ethernet_Manager.svg)](https://github.com/khoih-prog/Ethernet_Manager/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Ethernet_Manager/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Ethernet_Manager.svg)](http://github.com/khoih-prog/Ethernet_Manager/issues)

---
---

## Table of Contents


* [Changelog](#changelog)
  * [Releases v1.7.1](#releases-v171)
  * [Major Releases v1.7.0](#major-releases-v170)
  * [Releases v1.6.1](#releases-v161)
  * [Major Releases v1.6.0](#major-releases-v160)
  * [Major Releases v1.5.0](#major-releases-v150)
  * [Major Releases v1.4.0](#major-releases-v140)
  * [Major Releases v1.3.0](#major-releases-v130)
  * [Major Releases v1.2.0](#major-releases-v120)
  * [Releases v1.1.1](#releases-v111)
  * [Releases v1.1.0](#releases-v110)
  * [Releases v1.0.0](#releases-v100)

---
---


## Changelog

### Releases v1.7.1

1. Update to be compatible with new `FlashStorage_SAMD` library version
2. Update `Packages' Patches`

### Major Releases v1.7.0

1. Auto detect ESP32 core and use either built-in LittleFS or [LITTLEFS](https://github.com/lorol/LITTLEFS) library for ESP32 and WT32-ETH01.
2. Fix QNEthernet-related linkStatus.
3. Add support to many more new RP2040 boards
4. Add support to generic SAMD21 : `__SAMD21E1xA__`, `__SAMD21G1xA__` and `__SAMD21J1xA__`

### Releases v1.6.1

1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix
2. Update `Packages' Patches`

### Major Releases v1.6.0

1. Add support to [QNEthernet Library](https://github.com/ssilverman/QNEthernet) for Teensy 4.1 built-in Ethernet
2. Update examples with new features

### Major Releases v1.5.0

1. Add support to ESP32-based WT32-ETH01 (ESP32 + LAN8720) boards, using EEPROM, SPIFFS or LittleFS

### Major Releases v1.4.0

1. Add support to RP2040-based boards, such as **Nano RP2040 Connect**, using [**Arduino mbed OS for Nano boards**](https://github.com/arduino/ArduinoCore-mbed) and LittleFS.
1. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** v2.1.0+ core](https://github.com/arduino/ArduinoCore-mbed) and LittleFS.

### Major Releases v1.3.0

1. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico core** v1.3.1+](https://github.com/earlephilhower/arduino-pico) with LittleFS.
2. Update examples with new features

### Major Releases v1.2.0

1. Configurable **Customs HTML Headers**, including Customs Style, Customs Head Elements, CORS Header.
2. Add functions to control Config Portal from software or Virtual Switches. Check [How to trigger a Config Portal from code #25](https://github.com/khoih-prog/Blynk_WM/issues/25)
3. Use more efficient [FlashStorage_SAMD v1.1.0](https://github.com/khoih-prog/FlashStorage_SAMD)
4. Add support to **ESP32-S2 (ESP32-S2 Saola and AI-Thinker ESP-12K)**
5. Add [**Instructions to install ESP32-S2 core**](https://github.com/khoih-prog/Ethernet_Manager#howto-install-esp32-s2-core-for-esp32-s2-saola-ai-thinker-esp-12k-boards-into-arduino-ide)
6. Fix Config Portal Bug. 
7. Update examples

### Releases v1.1.1

1. Clean-up all compiler warnings possible.
2. Add Table of Contents


### Releases v1.1.0

1. Add support to ESP32 and ESP8266 using EEPROM, SPIFFS or LittleFS
2. Add many complex MQTT Examples to demonstrate how to use the dynamic parameters, entered via Config Portal, to connect to **ThingStream MQTT Server** at `mqtt.thingstream.io`.


### Releases v1.0.0

1. Initial coding to support SAMD21/SAMD51, nRF52, SAM DUE, Teensy.
2. Provide support to W5x00, ENC28J60 and Teensy 4.1 NativeEthernet.
3. Supporting Ethernet, EthernetLarge, Ethernet2, Ethernet3, EthernetENC, UIPEthernet and Teensy NativeEthernet Libraries


