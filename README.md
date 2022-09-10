## Ethernet_Manager

[![arduino-library-badge](https://www.ardu-badge.com/badge/Ethernet_Manager.svg?)](https://www.ardu-badge.com/Ethernet_Manager)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Ethernet_Manager.svg)](https://github.com/khoih-prog/Ethernet_Manager/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Ethernet_Manager/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Ethernet_Manager.svg)](http://github.com/khoih-prog/Ethernet_Manager/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>

---
---

## Table of Contents

* [Important Notes about Nano_RP2040_Connect](#important-notes-about-nano_rp2040_connect)
* [Why do we need this Ethernet_Manager library](#why-do-we-need-this-ethernet_manager-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
  * [Currently supported Ethernet shields/modules](#currently-supported-ethernet-shieldsmodules)
* [Changelog](changelog.md) 
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
    * [7.1. For STM32 boards to use LAN8720](#71-for-stm32-boards-to-use-lan8720)
    * [7.2. For STM32 boards to use Serial1](#72-for-stm32-boards-to-use-serial1)
  * [8. For RP2040-based boards using Earle Philhower arduino-pico core](#8-for-rp2040-based-boards-using-earle-philhower-arduino-pico-core)
    * [8.1. To use BOARD_NAME](#81-to-use-board_name)
    * [8.2. To avoid compile error relating to microsecondsToClockCycles](#82-to-avoid-compile-error-relating-to-microsecondstoclockcycles)
  * [9. For Portenta_H7 boards using Arduino IDE in Linux](#9-for-portenta_h7-boards-using-arduino-ide-in-linux)
  * [10. For RTL8720DN boards using AmebaD core](#10-for-rtl8720dn-boards-using-amebad-core)
  * [11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core](#11-For-SAMD21-and-SAMD51-boards-using-ArduinoCore-fab-sam-core)
  * [12. For Seeeduino RP2040 boards](#12-For-Seeeduino-RP2040-boards)
* [Libraries' Patches](#libraries-patches)
  * [1. For application requiring 2K+ HTML page](#1-for-application-requiring-2k-html-page)
  * [2. For Ethernet library](#2-for-ethernet-library)
  * [3. For EthernetLarge library](#3-for-ethernetlarge-library)
  * [4. For Etherne2 library](#4-for-ethernet2-library)
  * [5. For Ethernet3 library](#5-for-ethernet3-library)
  * [6. For UIPEthernet library](#6-for-uipethernet-library)
  * [7. For fixing ESP32 compile error](#7-for-fixing-esp32-compile-error) 
* [Note for Platform IO using ESP32 LittleFS](#note-for-platform-io-using-esp32-littlefs) 
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [Important Notes](#important-notes)
  * [1. Using hpp files](#1-using-hpp-files)
  * [2. Note for Adafruit nRF52](#2-note-for-adafruit-nrf52)
  * [3. Note for Adafruit SAMD21 and SAMD51](#3-note-for-adafruit-samd21-and-samd51)
  * [4. Note for Arduino SAM DUE](#4-note-for-arduino-sam-due)
  * [5. Note for RP2040-based boards](#5-note-for-rp2040-based-boards)
  * [6. Note for MBED RP2040-based boards](#6-note-for-mbed-rp2040-based-boards)
  * [7. Note for MBED RP2040-based boards LittleFS usage](#7-note-for-mbed-rp2040-based-boards-littlefs-usage). **Important**
* [Configuration Notes](#configuration-notes)
  * [1. How to select which built-in Ethernet or shield to use](#1-how-to-select-which-built-in-ethernet-or-shield-to-use)
  * [2. How to select another CS/SS pin to use](#2-how-to-select-another-csss-pin-to-use)
  * [3. How to use W5x00/ENC28J60 with ESP32](#3-how-to-use-w5x00enc28j60-with-esp32)
  * [4. How to use W5x00/ENC28J60 with ESP8266](#4-how-to-use-w5x00enc28j60-with-esp8266)
  * [5. How to increase W5x00 TX/RX buffer](#5-how-to-increase-w5x00-txrx-buffer)
  * [6. How to use SPI2 for ESP32 using W5x00 and Ethernet_Generic Library](#6-How-to-use-SPI2-for-ESP32-using-W5x00-and-Ethernet_Generic-Library)
  * [7. How to use SPI1 for RP2040 using W5x00 and Ethernet_Generic Library](#7-How-to-use-SPI1-for-RP2040-using-W5x00-and-Ethernet_Generic-Library)
  * [Not supported Libraries](#not-supported-libraries)
* [How to use default Credentials and have them pre-loaded onto Config Portal](#how-to-use-default-credentials-and-have-them-pre-loaded-onto-config-portal)
* [How to use](#how-to-use)
  * [1. Basic usage](#1-basic-usage)
  * [2. Add custom parameters](#2-add-custom-parameters)
  * [3. Not using custom parameters](#3-not-using-custom-parameters)
  * [4. To open Config Portal](#4-to-open-config-portal)
  * [5. To use custom HTML Style](#5-to-use-custom-html-style)
  * [6. To use custom Head Elements](#6-to-use-custom-head-elements)
  * [7. To use CORS Header](#7-to-use-cors-header)
* [Important Notes for using Dynamic Parameters' ids](#important-notes-for-using-dynamic-parameters-ids)
* [Examples](#examples)
  * [ 1. AM2315_Ethernet](examples/AM2315_Ethernet)
  * [ 2. Ethernet_Generic](examples/Ethernet_Generic)
  * [ 3. Ethernet_nRF52](examples/Ethernet_nRF52)
  * [ 4. Ethernet_RP2040](examples/Ethernet_RP2040). **New**
  * [ 5. Ethernet_SAMD](examples/Ethernet_SAMD)
  * [ 6. Ethernet_SAM_DUE](examples/Ethernet_SAM_DUE)
  * [ 7. Ethernet_Teensy](examples/Ethernet_Teensy)
  * [ 8. Ethernet_WT32_ETH01](examples/Ethernet_WT32_ETH01). **New**
  * [ 9. **MQTT_ThingStream_Ethernet_Generic**](examples/MQTT_ThingStream_Ethernet_Generic)
  * [10. **MQTT_ThingStream_Ethernet_nRF52**](examples/MQTT_ThingStream_Ethernet_nRF52)
  * [11. **MQTT_ThingStream_Ethernet_RP2040**](examples/MQTT_ThingStream_Ethernet_RP2040). **New**
  * [12. **MQTT_ThingStream_Ethernet_SAMD**](examples/MQTT_ThingStream_Ethernet_SAMD)
  * [13. **MQTT_ThingStream_Ethernet_SAM_DUE**](examples/MQTT_ThingStream_Ethernet_SAM_DUE)
  * [14. **MQTT_ThingStream_Ethernet_Teensy**](examples/MQTT_ThingStream_Ethernet_Teensy)
  * [15. **MQTT_ThingStream_Ethernet_WT32_ETH01**](examples/MQTT_ThingStream_Ethernet_WT32_ETH01). **New**
  * [16. QNEthernet_Teensy](examples/QNEthernet_Teensy). **New**
  * [17. **MQTT_ThingStream_QNEthernet_Teensy**](examples/MQTT_ThingStream_QNEthernet_Teensy). **New**
* [So, how it works?](#so-how-it-works)
* [Example Ethernet_Generic](#example-ethernet_generic)
  * [1. File Ethernet_Generic.ino](#1-file-ethernet_genericino)
  * [2. File defines.h](#2-file-definesh) 
  * [3. File Credentials.h](#3-file-credentialsh) 
  * [4. File dynamicParams.h](#4-file-dynamicparamsh) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. Ethernet_nRF52 on NRF52840_FEATHER_EXPRESS with W5500 using Ethernet_Generic Library](#1-ethernet_nrf52-on-nrf52840_feather_express-with-w5500-using-Ethernet_Generic-library)
    * [1.1 Normal run](#11-normal-run)
    * [1.2. DoubleResetDetected](#12-doubleresetdetected) 
    * [1.3. Config Portal started](#13-config-portal-started) 
    * [1.4. Credentials entered and Saved](#14-credentials-entered-and-saved) 
  * [2. Ethernet_SAMD on SeeedStudio SAMD21 SEEED_XIAO_M0 with W5500 using Ethernet_Generic Library](#2-ethernet_samd-on-seeedstudio-samd21-seeed_xiao_m0-with-w5500-using-Ethernet_Generic-library)
  * [3. Ethernet_SAM_DUE on Arduino SAM DUE with W5100 using Ethernet_Generic Library](#3-ethernet_sam_due-on-arduino-sam-due-with-w5100-using-Ethernet_Generic-library)
  * [4. MQTT_ThingStream_Ethernet_Generic on ESP8266_NODEMCU with W5x00 using Ethernet_Generic Library](#4-mqtt_thingstream_ethernet_generic-on-esp8266_nodemcu-with-w5x00-using-Ethernet_Generic-library)
    * [4.1. Normal run without correct ThingStream MQTT Credentials](#41-normal-run-without-correct-thingstream-mqtt-credentials)
    * [4.2. Got correct ThingStream MQTT Credentials from Config Portal](#42-got-correct-thingstream-mqtt-credentials-from-config-portal) 
  * [5. MQTT_ThingStream_Ethernet_Generic on NRF52840_FEATHER with ENC28J60 using EthernetENC Library](#5-mqtt_thingstream_ethernet_generic-on-nrf52840_feather-with-enc28j60-using-ethernetenc-library)
    * [5.1. Normal run without correct ThingStream MQTT Credentials](#51-normal-run-without-correct-thingstream-mqtt-credentials)
    * [5.2. Got correct ThingStream MQTT Credentials from Config Portal](#52-got-correct-thingstream-mqtt-credentials-from-config-portal)
  * [6. MQTT_ThingStream_Ethernet_RP2040 on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library](#6-mqtt_thingstream_ethernet_rp2040-on-raspberry_pi_pico-with-w5x00-using-Ethernet_Generic-library)
    * [6.1. Normal run without correct ThingStream MQTT Credentials or DRD](#61-normal-run-without-correct-thingstream-mqtt-credentials-or-drd)
    * [6.2. Got correct ThingStream MQTT Credentials from Config Portal](#62-got-correct-thingstream-mqtt-credentials-from-config-portal)
  * [7. Ethernet_RP2040 on MBED RASPBERRY_PI_PICO with W5500 using Ethernet_Generic Library](#7-ethernet_rp2040-on-mbed-raspberry_pi_pico-with-w5500-using-Ethernet_Generic-library)
    * [7.1. DRD => Config Portal](#71-drd--config-portal)
    * [7.2. Data Saved => Exit Config Portal](#72-data-saved--exit-config-portal)
  * [8. MQTT_ThingStream_Ethernet_WT32_ETH01 on WT32-ETH01](#8-mqtt_thingstream_ethernet_wt32_eth01-on-wt32-eth01)
    * [8.1. Normal run with correct ThingStream MQTT Credentials](#81-normal-run-with-correct-thingstream-mqtt-credentials) 
  * [9. QNEthernet_Teensy on TEENSY 4.1 using QNEthernet](#9-qnethernet_teensy-on-teensy-41-using-qnethernet)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)


---
---

### Important Notes about Nano_RP2040_Connect

The LittleFS of the new **Nano_RP2040_Connect** board ( see [New board](pics/New_Board.png) ), using ISSI Flash chip, is currently not working with [`Arduino mbed_rp2040 core 2.4.1+`](https://github.com/arduino/ArduinoCore-mbed/releases/tag/2.4.1). Please downgrade to [`Arduino mbed_rp2040 core 2.3.1`](https://github.com/arduino/ArduinoCore-mbed/releases/tag/2.3.1)

Check [**RP2040 Connect board has faulty components in newest purchase** #318](https://github.com/arduino/ArduinoCore-mbed/issues/318#) for more information of when and how the issue will be fixed.

The old board ( see [Old board](pics/Old_Board.png) ), using Adesto Flash chip, is currently working with [`Arduino mbed_rp2040 core 2.4.1+`](https://github.com/arduino/ArduinoCore-mbed/releases/tag/2.4.1).

---
---

### Why do we need this [Ethernet_Manager library](https://github.com/khoih-prog/Ethernet_Manager)

#### Features

- This is the new library, adding to the current WiFiManager sets of libraries. It's designed to help you eliminate `hardcoding` your Credentials in **Teensy, SAM DUE, SAMD21, SAMD51, nRF52,RP2040-based, etc. boards using Ethernet shields (W5100, W5200, W5500, ENC28J60, Teensy 4.1 NativeEthernet/QNEthernet, etc)**. It's currently **not supporting SSL**. Will support soon.

- It's not supporting UNO/Nano/Mega and other AVR boards for not enough memory.
- You can update Credentials any time you need to change via Configure Portal. Data are saved in configurable locations in EEPROM, DueFlashStorage or FlashStorage
- Teensy LC, 2.0++ and 2.0 not supported.
- **DoubleDetectDetector** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
- Configurable **Config Portal Title** to be either BoardName or default undistinguishable names.
- Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device

The **RP2040-based boards, such as Nano RP2040 Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, ADAFRUIT_ITSYBITSY_RP2040, ADAFRUIT_QTPY_RP2040, ADAFRUIT_STEMMAFRIEND_RP2040, ADAFRUIT_TRINKEYQT_RP2040, ADAFRUIT_MACROPAD_RP2040, CYTRON_MAKER_PI_RP2040, SPARKFUN_PROMICRO_RP2040, CHALLENGER_2040_WIFI_RP2040, CHALLENGER_2040_LTE_RP2040, MELOPERO_SHAKE_RP2040, UPESY_RP2040_DEVKIT, etc.**, are currently supported using [Earle Philhower's arduino-pico core](https://github.com/earlephilhower/arduino-pico) or [**Arduino mbed OS for RP2040/Nano boards**](https://github.com/arduino/ArduinoCore-mbed).

New recent features:

- **DoubleDetectDetector** feature to force Config Portal when double reset is detected within predetermined time, default 10s.
- Configurable **Config Portal Title** to be either BoardName or default undistinguishable names.
- Examples are redesigned to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device
- Auto detect ESP32 core and use either built-in LittleFS or [LITTLEFS](https://github.com/lorol/LITTLEFS) library for ESP32 and WT32-ETH01.

---

#### Currently Supported Boards

This [**Ethernet_Manager** library](https://github.com/khoih-prog/Ethernet_Manager) currently supports these following boards:

 1. **nRF52 boards**, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
 
 2. **SAM DUE**
 
 3. **SAMD21**
  - Arduino SAMD21: ZERO, MKRs, NANO_33_IOT, etc.
  - Adafruit SAMD21 (M0): ItsyBitsy M0, Feather M0, Feather M0 Express, Metro M0 Express, Circuit Playground Express, Trinket M0, PIRkey, Hallowing M0, Crickit M0, etc.
  - Seeeduino:  LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.
  - SAMD21E1xA, SAMD21G1xA and SAMD21J1xA
  
 4. **SAMD51**
  - Adafruit SAMD51 (M4): Metro M4, Grand Central M4, ItsyBitsy M4, Feather M4 Express, Trellis M4, Metro M4 AirLift Lite, MONSTER M4SK Express, Hallowing M4, etc.
  - Seeeduino: Wio Terminal, Grove UI Wireless
  
 5. **Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC)**
 
 6. **ESP32 including ESP32-S2 (ESP32-S2 Saola, AI-Thinker ESP-12K, etc.)**
 
 7. **ESP8266**
 
 8. RP2040-based boards, such as **Nano RP2040 Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, ADAFRUIT_ITSYBITSY_RP2040, ADAFRUIT_QTPY_RP2040, ADAFRUIT_STEMMAFRIEND_RP2040, ADAFRUIT_TRINKEYQT_RP2040, ADAFRUIT_MACROPAD_RP2040, CYTRON_MAKER_PI_RP2040, SPARKFUN_PROMICRO_RP2040, CHALLENGER_2040_WIFI_RP2040, CHALLENGER_2040_LTE_RP2040, MELOPERO_SHAKE_RP2040, UPESY_RP2040_DEVKIT, etc.**, using [Earle Philhower's arduino-pico core](https://github.com/earlephilhower/arduino-pico).

 9. RP2040-based boards, such as **Nano RP2040 Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed)

10. **WT32_ETH01 boards** using ESP32-based boards and LAN8720 Ethernet

---
 
#### Supported Ethernet shields/modules:

1. W5x00 using [`Ethernet_Generic`](https://github.com/khoih-prog/Ethernet_Generic) library
2. ENC28J60 using [`EthernetENC`](https://github.com/jandrassy/EthernetENC) or [`UIPEthernet`](https://github.com/UIPEthernet/UIPEthernet) library
3. Teensy 4.1 built-in Ethernet using [`NativeEthernet`](https://github.com/vjmuzik/NativeEthernet) library
4. LAN8720 Ethernet used in WT32_ETH01 boards
5. Teensy 4.1 built-in Ethernet using [`QNEthernet`](https://github.com/ssilverman/QNEthernet) library


---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Arduino AVR core 1.8.5+`](https://github.com/arduino/ArduinoCore-avr) for Arduino (Use Arduino Board Manager) AVR boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-avr.svg)](https://github.com/arduino/ArduinoCore-avr/releases/latest)
 3. [`Teensy core v1.57+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0) boards.
 4. [`Arduino SAM DUE core v1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards.
 5. [`Arduino SAMD core 1.8.13+`](https://github.com/arduino/ArduinoCore-samd) for SAMD ARM Cortex-M0+ boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-samd.svg)](https://github.com/arduino/ArduinoCore-samd/releases/latest)
 6. [`Adafruit SAMD core 1.7.10+`](https://github.com/adafruit/ArduinoCore-samd) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). [![GitHub release](https://img.shields.io/github/release/adafruit/ArduinoCore-samd.svg)](https://github.com/adafruit/ArduinoCore-samd/releases/latest)
 7. [`Seeeduino SAMD core 1.8.3+`](https://github.com/Seeed-Studio/ArduinoCore-samd) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). [![Latest release](https://img.shields.io/github/release/Seeed-Studio/ArduinoCore-samd.svg)](https://github.com/Seeed-Studio/ArduinoCore-samd/releases/latest/)
 8. [`Adafruit nRF52 v1.3.0+`](https://github.com/adafruit/Adafruit_nRF52_Arduino) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest)
 9. [`ESP32 Core 2.0.4+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/)
10. [`ESP8266 Core 3.0.2+`](https://github.com/esp8266/Arduino) for ESP8266-based boards. [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/). To use ESP8266 core 2.7.1+ for LittleFS.
11. [`ArduinoCore-mbed mbed_rp2040, mbed_nano, mbed_portenta core 3.1.1+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino (Use Arduino Board Manager) **Portenta_H7, RP2040-based boards, such as Nano_RP2040_Connect, RASPBERRY_PI_PICO**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
12. [`Earle Philhower's arduino-pico core v2.5.2+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest)
13. [`Functional-Vlpp library v1.0.2+`](https://github.com/khoih-prog/functional-vlpp) to use server's lambda function. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/Functional-Vlpp.svg?)](https://www.ardu-badge.com/Functional-Vlpp)
14. Depending on which Ethernet card you're using:
   - [`Ethernet_Generic library v2.5.2+`](https://github.com/khoih-prog/Ethernet_Generic) for W5100, W5200 and W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip.  [![GitHub release](https://img.shields.io/github/release/khoih-prog/Ethernet_Generic.svg)](https://github.com/khoih-prog/Ethernet_Generic/releases/latest)
   - [`EthernetENC library v2.0.3+`](https://github.com/jandrassy/EthernetENC) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/jandrassy/EthernetENC.svg)](https://github.com/jandrassy/EthernetENC/releases/latest). **New and Better**
   - [`UIPEthernet library v2.0.12+`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/UIPEthernet/UIPEthernet.svg)](https://github.com/UIPEthernet/UIPEthernet/releases/latest)
   - [`NativeEthernet Library version stable111+`](https://github.com/vjmuzik/NativeEthernet) for Teensy 4.1 built-in Ethernet.
   - [`QNEthernet Library version v0.15.0+`](https://github.com/ssilverman/QNEthernet) for Teensy 4.1 built-in Ethernet. **New**
15. Depending on which board you're using:
   - [`DueFlashStorage library v1.0.0+`](https://github.com/sebnil/DueFlashStorage) for SAM DUE. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/DueFlashStorage.svg?)](https://www.ardu-badge.com/DueFlashStorage)
   - [`FlashStorage_SAMD library v1.3.2+`](https://github.com/khoih-prog/FlashStorage_SAMD) for SAMD21 and SAMD51 boards (ZERO, MKR, NANO_33_IOT, M0, M0 Pro, AdaFruit Itsy-Bitsy M4, etc.). [![GitHub release](https://img.shields.io/github/release/khoih-prog/FlashStorage_SAMD.svg)](https://github.com/khoih-prog/FlashStorage_SAMD/releases/latest)
   - [`Adafruit's LittleFS/InternalFS`](www.adafruit.com) for nRF52
16. [`EthernetWebServer library v2.2.2+`](https://github.com/khoih-prog/EthernetWebServer). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/EthernetWebServer.svg?)](https://www.ardu-badge.com/EthernetWebServer).
17. [`WebServer_WT32_ETH01 library v1.5.0+`](https://github.com/khoih-prog/WebServer_WT32_ETH01) for WT32_ETH01 boards. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WebServer_WT32_ETH01.svg?)](https://www.ardu-badge.com/WebServer_WT32_ETH01).
18. [`ESP_DoubleResetDetector library v1.3.2+`](https://github.com/khoih-prog/ESP_DoubleResetDetector) for ESP32 and ESP8266.  To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_DoubleResetDetector.svg?)](https://www.ardu-badge.com/ESP_DoubleResetDetector).
19. [`DoubleResetDetector_Generic library v1.8.1+`](https://github.com/khoih-prog/DoubleResetDetector_Generic) for other boards (not ESP32 or ESP8266). To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/DoubleResetDetector_Generic.svg?)](https://www.ardu-badge.com/DoubleResetDetector_Generic).
20. [`LittleFS_esp32 v1.0.6+`](https://github.com/lorol/LITTLEFS) for ESP32-based boards using LittleFS with ESP32 core **v1.0.5-**. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/LittleFS_esp32.svg?)](https://www.ardu-badge.com/LittleFS_esp32). **Notice**: This [`LittleFS_esp32 library`](https://github.com/lorol/LITTLEFS) has been integrated to Arduino [ESP32 core v1.0.6+](https://github.com/espressif/arduino-esp32/tree/master/libraries/LITTLEFS) and **you don't need to install it if using ESP32 core v1.0.6+**

---

### Installation

The suggested way to install is to:

#### Use Arduino Library Manager

The best way is to use `Arduino Library Manager`. Search for `Ethernet_Manager`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/Ethernet_Manager.svg?)](https://www.ardu-badge.com/Ethernet_Manager) for more detailed instructions.

### Manual Install

1. Navigate to [Ethernet_Manager](https://github.com/khoih-prog/Ethernet_Manager) page.
2. Download the latest release `Ethernet_Manager-main.zip`.
3. Extract the zip file to `Ethernet_Manager-main` directory 
4. Copy the whole `Ethernet_Manager-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**Ethernet_Manager** library](https://registry.platformio.org/libraries/khoih-prog/Ethernet_Manager) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/Ethernet_Manager/installation). Search for Ethernet_Manager in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 Packages_Patches](Packages_Patches/adafruit/hardware/nrf52/1.3.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0). 

Supposing the Adafruit nRF52 version is 1.3.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.19/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.19. These files must be copied into the directory:

- `./arduino-1.8.19/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD Packages_Patches](Packages_Patches/arduino/hardware/samd/1.8.13) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.13).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.13. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.13/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the whole [Adafruit SAMD Packages_Patches](Packages_Patches/adafruit/hardware/samd/1.7.10) directory into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.7.10). 

Supposing the Adafruit SAMD core version is 1.7.10. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.7.10/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.10/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.10/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the whole [Seeeduino SAMD Packages_Patches](Packages_Patches/Seeeduino/hardware/samd/1.8.3) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3). 

Supposing the Seeeduino SAMD core version is 1.8.3. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.3/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 7. For STM32 boards

#### 7.1 For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.3.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 7.2 For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.3.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.3.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.3.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.3.0/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h`

#### 8. For RP2040-based boards using [Earle Philhower arduino-pico core](https://github.com/earlephilhower/arduino-pico)

#### 8.1 To use BOARD_NAME

 **To be able to automatically detect and display BOARD_NAME on RP2040-based boards (RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc) boards**, you have to copy the file [RP2040 platform.txt](Packages_Patches/rp2040/hardware/rp2040/1.4.0) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0). 

Supposing the rp2040 core version is 1.4.0. This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/platform.txt`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add -DBOARD_NAME="{build.board}" #136](https://github.com/earlephilhower/arduino-pico/pull/136).

#### 8.2 To avoid compile error relating to microsecondsToClockCycles

Some libraries, such as [Adafruit DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library), require the definition of microsecondsToClockCycles(). **To be able to compile and run on RP2040-based boards**, you have to copy the files in [**RP2040 Arduino.h**](Packages_Patches/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0).

Supposing the rp2040 core version is 1.4.0. This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/cores/rp2040/Arduino.h`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add defs for compatibility #142](https://github.com/earlephilhower/arduino-pico/pull/142).


#### 9. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/3.1.1/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/3.1.1/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/3.1.1
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 3.1.1. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.1.1/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`


#### 10. For RTL8720DN boards using AmebaD core
 
 To avoid compile error relating to PROGMEM, you have to copy the file [Realtek AmebaD core pgmspace.h](Packages_Patches/realtek/hardware/AmebaD/3.1.3/cores/arduino/avr/pgmspace.h) into Realtek AmebaD directory (~/.arduino15/packages/realtek/hardware/AmebaD/3.1.3/cores/arduino/avr/pgmspace.h). 

Supposing the Realtek AmebaD core version is 3.1.3. This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/3.1.3/cores/arduino/avr/pgmspace.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/x.yy.zz/cores/arduino/avr/pgmspace.h`


#### 11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core
 
 To avoid compile error relating to SAMD21/SAMD51, you have to copy the file [ArduinoCore-fab-sam core pgmspace.h](Packages_Patches/Fab_SAM_Arduino/hardware/samd/1.7.0/boards.txt) into `ArduinoCore-fab-sam` samd directory (~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.7.0/boards.txt). 

Supposing the `ArduinoCore-fab-sam` samd core version is 1.7.0. This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.7.0/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/x.yy.zz/boards.txt`


#### 12. For Seeeduino RP2040 boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino RP2040 (XIAO RP2040, Wio RP2040 Mini) boards***, you have to copy the whole [Seeeduino RP2040 Packages_Patches](Packages_Patches/Seeeduino/hardware/rp2040/2.7.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2). 

Supposing the Seeeduino SAMD core version is 2.7.2. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/variants/Seeed_XIAO_RP2040/pins_arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/variants/Seeed_XIAO_RP2040/pins_arduino.h`


---
---

### Libraries' Patches

#### 1. For application requiring 2K+ HTML page

If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

#### 2. For Ethernet library

To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

#### 3. For EthernetLarge library

To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)


#### 4. For Ethernet2 library

To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for the [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

#### 5. For Ethernet3 library

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

#### 6. For UIPEthernet library

***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
- [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
- [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
- [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

#### 7. For fixing ESP32 compile error

To fix [`ESP32 compile error`](https://github.com/espressif/arduino-esp32), just copy the following file into the [`ESP32`](https://github.com/espressif/arduino-esp32) cores/esp32 directory (e.g. ./arduino-1.8.12/hardware/espressif/cores/esp32) to overwrite the old file:
- [Server.h](LibraryPatches/esp32/cores/esp32/Server.h)

---
---

### Note for Platform IO using ESP32 LittleFS

In Platform IO, to fix the error when using [`LittleFS_esp32 v1.0`](https://github.com/lorol/LITTLEFS) for ESP32-based boards with ESP32 core v1.0.4- (ESP-IDF v3.2-), uncomment the following line

from

```
//#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

to

```
#define CONFIG_LITTLEFS_FOR_IDF_3_2   /* For old IDF - like in release 1.0.4 */
```

It's advisable to use the latest [`LittleFS_esp32 v1.0.6+`](https://github.com/lorol/LITTLEFS) to avoid the issue.

Thanks to [Roshan](https://github.com/solroshan) to report the issue in [Error esp_littlefs.c 'utime_p'](https://github.com/khoih-prog/ESPAsync_WiFiManager/issues/28) 

---
---

### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- ADC1 controls ADC function for pins **GPIO32-GPIO39**
- ADC2 controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/main/components/driver/adc_common.c#L61)

> In ADC2, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the ADC2, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the ADC2, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use ADC2 for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use ADC2 with WiFi/BlueTooth (BT/BLE).
- Use ADC1, and pins GPIO32-GPIO39
- If somehow it's a must to use those pins serviced by ADC2 (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).

---
---

### Important Notes

#### 1. Using hpp files

Code is restructured to provide flexibility to make it easy to support many more **Ethernet** modules/shields in the future. Please delete the *.cpp files, replaced by *.hpp files, in the src directory, if *.cpp files still exist after installing new version.

#### 2. Note for Adafruit nRF52

For **Adafruit nRF52**, use the SPI's pins as follows:

  - SS/CS     = 10
  - SPI_MOSI  = MO(SI)
  - SPI_MISO  = MI(SO)
  - SPI_SCK   = SCK

#### 3. Note for Adafruit SAMD21 and SAMD51

For **Adafruit SAMD21/SAMD51**, use the SPI's CS/SS pin as follows:

  - Itsy-Bitsy M0/M4, Feather M0 (Express), Hallowing M0 Express, Zero, Metro M0 => use CS = 16 = pin A2
  - Feather M4 (SAMD51)   => use SS/CS = 9
  - Grand Central M4      => use SS/CS = 53
  - Hallowing M4          => use SS/CS = 10
  - Metro M4 AirLift      => use SS/CS = 36

To know the default CS/SS pins of not listed boards, check the related `variant.h` files in 

`~/.arduino15/packages/adafruit/hardware/samd/x.y.zz/variants/board_name/variant.h`

#### 4. Note for Arduino SAM DUE

For **Arduino SAM DUE**, use the SPI's pins as follows:

  - SS/CS     = 10
  - SPI_MOSI  = 75 ( pin 4 @ [ICSP connector](pics/ICSP_connector.jpg) )
  - SPI_MISO  = 74 ( pin 1 @ [ICSP connector](pics/ICSP_connector.jpg) )
  - SPI_SCK   = 76 ( pin 3 @ [ICSP connector](pics/ICSP_connector.jpg) )
  
<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Manager/blob/main/pics/ICSP_connector.jpg">
</p>
  
#### 5. Note for RP2040-based boards

For **RP2040-based** boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [Earle Philhower's arduino-pico core](https://github.com/earlephilhower/arduino-pico), use the SPI's pins as follows:

  - SS/CS     = 17
  - SPI_MOSI  = 19
  - SPI_MISO  = 16
  - SPI_SCK   = 18

#### 6. Note for MBED RP2040-based boards

For **RP2040-based** boards, such as **Nano RP2040 Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino mbed OS for RP2040/Nano boards**](https://github.com/arduino/ArduinoCore-mbed), use the SPI's pins as follows:

  - SS/CS     = 5
  - SPI_MOSI  = 3
  - SPI_MISO  = 4
  - SPI_SCK   = 2
  
  
#### 7. Note for MBED RP2040-based boards LittleFS usage

Currently, the MBED RP2040-based boards share the LittleFS usage and settings with the [**DoubleResetDetector_Generic** Library](https://github.com/khoih-prog/DoubleResetDetector_Generic). Check the `LittleFS` definitions at [DoubleResetDetector_Generic.h#L196-L204](https://github.com/khoih-prog/DoubleResetDetector_Generic/blob/master/src/DoubleResetDetector_Generic.h#L196-L204)

```
#if !defined(RP2040_FS_SIZE_KB)
  // Using default 16KB for LittleFS
  #define RP2040_FS_SIZE_KB       (64)
#endif

#if !defined(RP2040_FS_START)
  #define RP2040_FS_START           (RP2040_FLASH_SIZE - (RP2040_FS_SIZE_KB * 1024))
#endif

FlashIAPBlockDevice bd(XIP_BASE + RP2040_FS_START, (RP2040_FS_SIZE_KB * 1024));
```

You can change the `LittleFS` size from default 64KB to any size (from 1KB to 1MB = 1024KB) by adding a definition in your code to override the default, such as

```
#define RP2040_FS_SIZE_KB       (512)
```
  
Be sure to have the above definition before the first inclusion of `Ethernet_Manager.h`

```
#define RP2040_FS_SIZE_KB       (512)

...

#include <Ethernet_Manager.h>
```
  
The end of `LittleFS` is set at the end of RP2040 Flash, currently 2MB

```
#define RP2040_FS_START           (RP2040_FLASH_SIZE - (RP2040_FS_SIZE_KB * 1024))
```
  
---
---

### Configuration Notes

#### 1. How to select which built-in Ethernet or shield to use

The easiest way is to use 

```cpp
#define USE_ETHERNET_WRAPPER    true
```

then select **one and only one** Ethernet library to use as follows:

- Standard W5x00 Ethernet_Generic library is used by default, in the sketch, just be sure to comment out or leave these #defines to be false :

```cpp

// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      false
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       false
```

To use W5x00 Ethernet, for example using Ethernet_Generic library

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      true
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       false
```

- To use ENC28J60 Ethernet, using EthernetENC library (**NEW and Better**)

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      false
#define USE_ETHERNET_ENC          true
#define USE_CUSTOM_ETHERNET       false
```

- To use ENC28J60 Ethernet, using UIPEthernet library:

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          true
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      false
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       false
```


- To use another Ethernet library
For example, EthernetLarge library

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      false
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       true

//Must be placed before #include <EthernetWebServer.h>
#include <EthernetLarge.h>
...

#include <EthernetWebServer.h>
```

- Only for Teensy 4.1, to use NativeEthernet library

```
#if defined(__IMXRT1062__)
    // For Teensy 4.1/4.0
    #if defined(ARDUINO_TEENSY41)
      #define BOARD_TYPE      "TEENSY 4.1"
      // Use true for NativeEthernet Library, false if using other Ethernet libraries
      #define USE_NATIVE_ETHERNET     true
      #define USE_QN_ETHERNET         false
    #elif defined(ARDUINO_TEENSY40)
      #define BOARD_TYPE      "TEENSY 4.0"
    #else
      #define BOARD_TYPE      "TEENSY 4.x"
    #endif      
  #elif defined(__MK66FX1M0__)
  ....
```

- Only for Teensy 4.1, to use another Ethernet library, for example Ethernet_Generic library

```
#if defined(__IMXRT1062__)
  // For Teensy 4.1/4.0
  #if defined(ARDUINO_TEENSY41)
    #define BOARD_TYPE      "TEENSY 4.1"
    // Use true for NativeEthernet Library, false if using other Ethernet libraries
    #define USE_NATIVE_ETHERNET     false
    #define USE_QN_ETHERNET         false
  #elif defined(ARDUINO_TEENSY40)
    #define BOARD_TYPE      "TEENSY 4.0"
  #else
    #define BOARD_TYPE      "TEENSY 4.x"
  #endif      
#elif defined(__MK66FX1M0__)
  ....
  
#define USE_UIP_ETHERNET        false

// Only one if the following to be true
#define USE_ETHERNET_GENERIC    true
#define USE_ETHERNET_ENC        false
#define USE_CUSTOM_ETHERNET     false  
```

- Only for Teensy 4.1, to use QNEthernet library

```
#if ( defined(CORE_TEENSY) && defined(__IMXRT1062__) && defined(ARDUINO_TEENSY41) ) 
  // For Teensy 4.1
  #define BOARD_TYPE      "TEENSY 4.1"
  // Use true for NativeEthernet Library, false if using other Ethernet libraries
  #define USE_NATIVE_ETHERNET     false
  #define USE_QN_ETHERNET         true
#else
  #error Only Teensy 4.1 supported
#endif

#define USE_ETHERNET_WRAPPER    false

// Use true  for ENC28J60 and UIPEthernet library (https://github.com/UIPEthernet/UIPEthernet)
// Use false for W5x00 and Ethernetx library      (https://www.arduino.cc/en/Reference/Ethernet)

#define USE_UIP_ETHERNET        false
#define USE_ETHERNET_GENERIC    false
#define USE_ETHERNET_ENC        false
#define USE_CUSTOM_ETHERNET     false

#if USE_NATIVE_ETHERNET
  #include "NativeEthernet.h"
  #warning Using NativeEthernet lib for Teensy 4.1. Must also use Teensy Packages Patch or error
  #define SHIELD_TYPE           "using NativeEthernet"
#elif USE_QN_ETHERNET
  #include "QNEthernet.h"
  using namespace qindesign::network;
  #warning Using QNEthernet lib for Teensy 4.1. Must also use Teensy Packages Patch or error
  #define SHIELD_TYPE           "using QNEthernet"  
#endif 
```

---

#### 2. How to select another CS/SS pin to use

The default CS/SS pin is GPIO4(D2) for ESP8266, GPIO22 for ESP32, 10 for all other boards.

If the default pin is not correct, the easiest way is to change is to select the CS/SS pin (e.g. 22) to use as follows:

```
// To override the default CS/SS pin. Don't use unless you know exactly which pin to use
#define USE_THIS_SS_PIN   22
```

#### 3. How to use W5x00/ENC28J60 with ESP32


These pins are tested OK with ESP32 and W5x00/ENC28J60: 

* MOSI:  GPIO23
* MISO:  GPIO19
* SCK:   GPIO18 
* CS/SS: GPIO22

```
  #define PIN_D18           18        // Pin D18 mapped to pin GPIO18/VSPI_SCK of ESP32
  #define PIN_D19           19        // Pin D19 mapped to pin GPIO19/VSPI_MISO of ESP32
  #define PIN_D23           23        // Pin D23 mapped to pin GPIO23/VSPI_MOSI of ESP32
   
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // Connection for ESP32
  // MOSI: GPIO23, MISO: GPIO19, SCK: GPIO18, CS/SS: GPIO22
  
  #ifndef USE_THIS_SS_PIN
    #define USING_M5STACK_W5500     false
    #if USING_M5STACK_W5500
      #warning Using M5Stack_Core_ESP32 with W5500 mudule
      #define USE_THIS_SS_PIN   26    // For M5Stack_Core_ESP32 with W5500 mudule
    #else
      #define USE_THIS_SS_PIN   22    // For ESP32
    #endif
  #endif

```

#### 4. How to use W5x00/ENC28J60 with ESP8266

To avoid using the default but not-working Ethernet library of ESP8266, rename the Ethernet.h/cpp to Ethernet_ESP8266.h/cpp to avoid library conflict if you're using the Arduino Ethernet library. The `Ethernet_Generic` library can be used without conflict.

These pins are tested OK with ESP8266 and W5x00/ENC28J60

* MOSI:   D7/GPIO13
* MISO:   D6/GPIO12
* SCK:    D5/GPIO14
* CS/SS:  D2/GPIO4

```
  #define PIN_D5            14        // Pin D5 mapped to pin GPIO14/HSCLK of ESP8266
  #define PIN_D6            12        // Pin D6 mapped to pin GPIO12/HMISO of ESP8266
  #define PIN_D7            13        // Pin D7 mapped to pin GPIO13/RXD2/HMOSI of ESP8266
  
  // Connection for ESP8266
  // MOSI: D7/GPIO13, MISO: D6/GPIO12, SCK: D5/GPIO14, CS/SS: D2/GPIO4
  
  // For ESP8266, change for other boards if necessary
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   D2    // For ESP8266
  #endif
  
  // For ESP8266
  // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
  // Ethernet           0                 X            X            X            X        0
  // Ethernet2          X                 X            X            X            X        0
  // Ethernet3          X                 X            X            X            X        0
  // EthernetLarge      X                 X            X            X            X        0
  // Ethernet_ESP8266   0                 0            0            0            0        0
  // D2 is safe to used for Ethernet, Ethernet2, Ethernet3, EthernetLarge libs
  // Must use library patch for Ethernet, EthernetLarge libraries
  //Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (USE_THIS_SS_PIN);

```

#### 5. How to increase W5x00 TX/RX buffer

- For **Ethernet_Generic** library only,  simply use as follows to have large buffer similar to EthernetLarge library
```
#define ETHERNET_LARGE_BUFFERS
```

- For **Ethernet3** library only,  use as follows

```cpp
  // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
  #ifndef ETHERNET3_MAX_SOCK_NUM
    #define ETHERNET3_MAX_SOCK_NUM      4
  #endif
  
  Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
```


### 6. How to use SPI2 for ESP32 using W5x00 and Ethernet_Generic Library

- For **Ethernet_Generic** library only, to use `SPI2` for ESP32

```
#define USING_SPI2                          true
```

Pin to use for `SPI2`

```
MOSI:  13
MISO:  12
SCK:   14
SS:    5
```

### 7. How to use SPI1 for RP2040 using W5x00 and Ethernet_Generic Library

- For **Ethernet_Generic** library only, to use `SPI1` for RP2040 using [arduino-pico core](https://github.com/earlephilhower/arduino-pico)

```
#define USING_SPI2                          true
```

Pin to use for `SPI1`

```
MOSI:  15
MISO:  12
SCK:   14
SS:    13
```


#### Not supported Libraries

- The **Ethernet_Shield_W5200, EtherCard, EtherSia  libraries are not supported**. Don't use unless you know how to modify those libraries.
- Requests to support for any future custom Ethernet library will be ignored. **Use at your own risk**.

---


### How to use default Credentials and have them pre-loaded onto Config Portal

See this example and modify as necessary

1. To load [Default Credentials](examples/Ethernet_Generic/Credentials.h)
```
bool LOAD_DEFAULT_CONFIG_DATA = true;
```

2. To use system default to load "blank" when there is no valid Credentials
```
bool LOAD_DEFAULT_CONFIG_DATA = false;
```

3. Example of [Default Credentials](examples/Ethernet_Generic/Credentials.h)

```cpp
/// Start Default Config Data //////////////////

/*
typedef struct Configuration
{
  char header         [16];
  char static_IP      [16];
  char board_name     [24];
  int  checkSum;
} Ethernet_Configuration;
*/

#define TO_LOAD_DEFAULT_CONFIG_DATA      true

#if TO_LOAD_DEFAULT_CONFIG_DATA

bool LOAD_DEFAULT_CONFIG_DATA = false;

Ethernet_Configuration defaultConfig =
{
  //char header[16], dummy, not used
#if USE_SSL
  "Eth_SSL",
#else
  "Eth_NonSSL",
#endif

  // char static_IP      [16];
  //"192.168.2.230",
  // Use dynamic DHCP IP
  "",
  //char board_name     [24];
  "Air-Control",
  // terminate the list
  //int  checkSum, dummy, not used
  0
  /////////// End Default Config Data /////////////
};

#else

bool LOAD_DEFAULT_CONFIG_DATA = false;

Ethernet_Configuration defaultConfig;

#endif    // TO_LOAD_DEFAULT_CONFIG_DATA

/////////// End Default Config Data /////////////
```

---
---

### How to use

#### 1. Basic usage

- Include in your sketch

```cpp
// Must be before #include <Ethernet_Manager.h>
#include <Ethernet_Manager.h>

Ethernet_Manager ethernet_manager;
```

#### 2. Add custom parameters

- To add custom parameters, just add

```
#ifndef dynamicParams_h
#define dynamicParams_h

#include "defines.h"

// USE_DYNAMIC_PARAMETERS defined in defined.h

/////////////// Start dynamic Credentials ///////////////

/**************************************
  #define MAX_ID_LEN                5
  #define MAX_DISPLAY_NAME_LEN      16

  typedef struct
  {
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
  } MenuItem;
**************************************/

#if USE_DYNAMIC_PARAMETERS

  #define MAX_MQTT_SERVER_LEN      34
  char MQTT_Server  [MAX_MQTT_SERVER_LEN + 1]   = "default-mqtt-server";
  
  #define MAX_MQTT_PORT_LEN        6
  char MQTT_Port   [MAX_MQTT_PORT_LEN + 1]  = "1883";
  
  #define MAX_MQTT_USERNAME_LEN      34
  char MQTT_UserName  [MAX_MQTT_USERNAME_LEN + 1]   = "default-mqtt-username";
  
  #define MAX_MQTT_PW_LEN        34
  char MQTT_PW   [MAX_MQTT_PW_LEN + 1]  = "default-mqtt-password";
  
  #define MAX_MQTT_SUBS_TOPIC_LEN      34
  char MQTT_SubsTopic  [MAX_MQTT_SUBS_TOPIC_LEN + 1]   = "default-mqtt-SubTopic";
  
  #define MAX_MQTT_PUB_TOPIC_LEN       34
  char MQTT_PubTopic   [MAX_MQTT_PUB_TOPIC_LEN + 1]  = "default-mqtt-PubTopic";
  
  MenuItem myMenuItems [] =
  {
    { "mqtt", "MQTT Server",      MQTT_Server,      MAX_MQTT_SERVER_LEN },
    { "mqpt", "Port",             MQTT_Port,        MAX_MQTT_PORT_LEN   },
    { "user", "MQTT UserName",    MQTT_UserName,    MAX_MQTT_USERNAME_LEN },
    { "mqpw", "MQTT PWD",         MQTT_PW,          MAX_MQTT_PW_LEN },
    { "subs", "Subs Topics",      MQTT_SubsTopic,   MAX_MQTT_SUBS_TOPIC_LEN },
    { "pubs", "Pubs Topics",      MQTT_PubTopic,    MAX_MQTT_PUB_TOPIC_LEN },
  };
  
  uint16_t NUM_MENU_ITEMS = sizeof(myMenuItems) / sizeof(MenuItem);  //MenuItemSize;

#else

  MenuItem myMenuItems [] = {};
  
  uint16_t NUM_MENU_ITEMS = 0;
#endif

/////// // End dynamic Credentials ///////////

#endif      //dynamicParams_h

```

#### 3. Not using custom parameters

- If you don't need to add dynamic parameters, use the following in sketch

```
#define USE_DYNAMIC_PARAMETERS      false
```

#### 4. To open Config Portal

- When you want to open a config portal, just add

```cpp
ethernet_manager.begin();
```

#### 5. To use custom HTML Style

```
const char NewCustomsStyle[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}\
button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";

...

ethernet_manager.setCustomsStyle(NewCustomsStyle);
```

#### 6. To use custom Head Elements


```
ethernet_manager.setCustomsHeadElement("<style>html{filter: invert(10%);}</style>");
```

#### 7. To use CORS Header

```
ethernet_manager.setCORSHeader("Your Access-Control-Allow-Origin");
```


While in AP mode, connect to it using its `SSID` (ESP_XXXXXX) / `Password` ("MyESP_XXXXXX"), then open a browser to the Portal AP IP, default `192.168.4.1`, configure wifi then click **Save**. The Credentials / WiFi connection information will be saved in non-volatile memory. It will then autoconnect.


Once Credentials / WiFi network information is saved in the host non-volatile memory, it will try to autoconnect to WiFi every time it is started, without requiring any function calls in the sketch.

---
---

### Important Notes for using Dynamic Parameters' ids

1. These ids (such as "mqtt" in example) must be **unique**.

Please be noted that the following **reserved names are already used in library**:

```
"ip"    for Static IP Address
"nm"    for Board Name
```

---
---

### Examples

 1. [AM2315_Ethernet](examples/AM2315_Ethernet)
 2. [Ethernet_Generic](examples/Ethernet_Generic) 
 3. [Ethernet_nRF52](examples/Ethernet_nRF52)
 4. [Ethernet_RP2040](examples/Ethernet_RP2040). **New**
 5. [Ethernet_SAMD](examples/Ethernet_SAMD)
 6. [Ethernet_SAM_DUE](examples/Ethernet_SAM_DUE)
 7. [Ethernet_Teensy](examples/Ethernet_Teensy)
 8. [Ethernet_WT32_ETH01](examples/Ethernet_WT32_ETH01). **New**
 9. [**MQTT_ThingStream_Ethernet_Generic**](examples/MQTT_ThingStream_Ethernet_Generic).
10. [**MQTT_ThingStream_Ethernet_nRF52**](examples/MQTT_ThingStream_Ethernet_nRF52).
11. [**MQTT_ThingStream_Ethernet_RP2040**](examples/MQTT_ThingStream_Ethernet_RP2040). **New**
12. [**MQTT_ThingStream_Ethernet_SAMD**](examples/MQTT_ThingStream_Ethernet_SAMD).
13. [**MQTT_ThingStream_Ethernet_SAM_DUE**](examples/MQTT_ThingStream_Ethernet_SAM_DUE).
14. [**MQTT_ThingStream_Ethernet_Teensy**](examples/MQTT_ThingStream_Ethernet_Teensy).
15. [**MQTT_ThingStream_Ethernet_WT32_ETH01**](examples/MQTT_ThingStream_Ethernet_WT32_ETH01). **New**
16. [QNEthernet_Teensy](examples/QNEthernet_Teensy). **New**
17. [**MQTT_ThingStream_QNEthernet_Teensy**](examples/MQTT_ThingStream_QNEthernet_Teensy). **New**

---
---

## So, how it works?

If no valid config data are stored in EEPROM, it will switch to `Configuration Mode`. Connect to access point at the IP address displayed on Terminal or Router's DHCP server as in the following picture:

<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Manager/blob/main/pics/ConfigPortal.png">
</p>

After you connected to, for example, `192.168.2.86`, the Browser will display the following picture:

<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Manager/blob/main/pics/ConfigPortal.png">
</p>

Enter your credentials (Blynk Servers/Tokens and Port). If you prefer static IP, input it (for example `192.168.2.220`) in the corresponding field. Otherwise, just leave it `blank` or `nothing` to use auto IP assigned by DHCP server.

<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Manager/blob/main/pics/ConfigPortal_Data.png">
</p>

Then click `Save`. After the  board auto-restarted, you will see if it's connected to your Blynk server successfully as in  the following picture:

<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Manager/blob/main/pics/Saved.png">
</p>

This `ethernet_manager.run()` is not a blocking call, so you can use it for critical functions requiring in loop(). 

In operation, if Ethernet or connection is lost, `ethernet_manager.run()` will try reconnecting automatically. Therefore, `ethernet_manager.run()` must be called in the `loop()` function.

```cpp
void loop()
{
  ethernet_manager.run();
  ...
}
```

---
---

### Example [Ethernet_Generic](examples/Ethernet_Generic)

#### 1. File [Ethernet_Generic.ino](examples/Ethernet_Generic/Ethernet_Generic.ino)

https://github.com/khoih-prog/Ethernet_Manager/blob/d04bc0fedc077f0d4f6e7758ca0b4f879cc26d45/examples/Ethernet_Generic/Ethernet_Generic.ino#L13-L369

---

#### 2. File [defines.h](examples/Ethernet_Generic/defines.h)


https://github.com/khoih-prog/Ethernet_Manager/blob/d04bc0fedc077f0d4f6e7758ca0b4f879cc26d45/examples/Ethernet_Generic/defines.h#L13-L523


---

#### 3. File [Credentials.h](examples/Ethernet_Generic/Credentials.h)

https://github.com/khoih-prog/Ethernet_Manager/blob/d04bc0fedc077f0d4f6e7758ca0b4f879cc26d45/examples/Ethernet_Generic/Credentials.h#L13-L67


---

#### 4. File [dynamicParams.h](examples/Ethernet_Generic/dynamicParams.h)

https://github.com/khoih-prog/Ethernet_Manager/blob/d04bc0fedc077f0d4f6e7758ca0b4f879cc26d45/examples/Ethernet_Generic/dynamicParams.h#L13-L76



---
---

### Debug Terminal Output Samples

#### 1. Ethernet_nRF52 on NRF52840_FEATHER_EXPRESS with W5500 using Ethernet_Generic Library

This is the terminal output of an Adafruit NRF52840_FEATHER board with W5500 Ethernet shield using Ethernet_Generic Library, running [Ethernet_nRF52](examples/Ethernet_nRF52) example when **no doubleResetDetected**.

#### 1.1 Normal run

```
Start Ethernet_nRF52 on NRF52840_FEATHER
Ethernet Shield type W5x00 using Ethernet_Generic Library
Ethernet_Manager v1.8.1
DoubleResetDetector_Generic v1.8.1
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 25
[EWS] MISO: 24
[EWS] SCK: 26
[EWS] SS: 5
[EWS] =========================
[EWS] Board : NRF52840_FEATHER , setCsPin: 10
[EWS] =========================
[EWS] Currently Used SPI pinout:
[EWS] MOSI: 25
[EWS] MISO: 24
[EWS] SCK: 26
[EWS] SS: 5
[EWS] =========================
[ETM] ======= Start Default Config Data =======
[ETM] Header= Eth_NonSSL , BoardName= Air-Control
[ETM] StaticIP= 
[ETM] i= 0 ,id= mqtt
[ETM] data= default-mqtt-server
[ETM] i= 1 ,id= mqpt
[ETM] data= 1883
[ETM] i= 2 ,id= user
[ETM] data= default-mqtt-username
[ETM] i= 3 ,id= mqpw
[ETM] data= default-mqtt-password
[ETM] i= 4 ,id= subs
[ETM] data= default-mqtt-SubTopic
[ETM] i= 5 ,id= pubs
[ETM] data= default-mqtt-PubTopic
[ETM] LoadCfgFile 
[ETM] OK
[ETM] LoadCredFile 
[ETM] ChkCrR: Buffer allocated, Sz= 35
[ETM] ChkCrR:pdata= new-mqtt-server ,len= 34
[ETM] ChkCrR:pdata= 1883 ,len= 6
[ETM] ChkCrR:pdata= new-mqtt-username ,len= 34
[ETM] ChkCrR:pdata= old-mqtt-password ,len= 34
[ETM] ChkCrR:pdata= old-mqtt-SubTopic ,len= 34
[ETM] ChkCrR:pdata= old-mqtt-PubTopic ,len= 34
[ETM] OK
[ETM] CrCCSum=0x 217e ,CrRCSum=0x 217e
[ETM] Buffer freed
[ETM] CCSum=0x 6e7 ,RCSum=0x 6e7
[ETM] LoadCredFile 
[ETM] CrR:pdata= new-mqtt-server ,len= 34
[ETM] CrR:pdata= 1883 ,len= 6
[ETM] CrR:pdata= new-mqtt-username ,len= 34
[ETM] CrR:pdata= old-mqtt-password ,len= 34
[ETM] CrR:pdata= old-mqtt-SubTopic ,len= 34
[ETM] CrR:pdata= old-mqtt-PubTopic ,len= 34
[ETM] OK
[ETM] CrCCSum=0x 217e ,CrRCSum=0x 217e
[ETM] Valid Stored Dynamic Data
[ETM] ======= Start Stored Config Data =======
[ETM] Header= nRF52 , BoardName= nRF52_W5500
[ETM] StaticIP= 192.168.2.222
[ETM] i= 0 ,id= mqtt
[ETM] data= new-mqtt-server
[ETM] i= 1 ,id= mqpt
[ETM] data= 1883
[ETM] i= 2 ,id= user
[ETM] data= new-mqtt-username
[ETM] i= 3 ,id= mqpw
[ETM] data= old-mqtt-password
[ETM] i= 4 ,id= subs
[ETM] data= old-mqtt-SubTopic
[ETM] i= 5 ,id= pubs
[ETM] data= old-mqtt-PubTopic
[ETM] Start connectEthernet using Static IP = 192.168.2.222
[ETM] MAC:FE-9F-FA-D8-DC-BA
[ETM] IP: 192.168.2.222
[ETM] begin:Ethernet Connected.
Connected! IP address: 192.168.2.222
H
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = old-mqtt-password
Subs Topics = old-mqtt-SubTopic
Pubs Topics = old-mqtt-PubTopic
```


#### 1.2. DoubleResetDetected

```cpp
Start Ethernet_nRF52 on NRF52840_FEATHER
Ethernet Shield type : W5x00 using Ethernet_Generic Library
Ethernet_Manager v1.8.1
DoubleResetDetector_Generic v1.8.1
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 25
[EWS] MISO: 24
[EWS] SCK: 26
[EWS] SS: 5
[EWS] =========================
[EWS] Board : NRF52840_FEATHER , setCsPin: 10
[EWS] =========================
[EWS] Currently Used SPI pinout:
[EWS] MOSI: 25
[EWS] MISO: 24
[EWS] SCK: 26
[EWS] SS: 5
[EWS] =========================
LittleFS Flag read = 0xd0d01234
Flag read = 0xd0d01234
doubleResetDetected
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
[ETM] =====================
[ETM] DRD. Run ConfigPortal
[ETM] =====================
[ETM] ======= Start Default Config Data =======
[ETM] Header= Eth_NonSSL , BoardName= Air-Control
[ETM] StaticIP= 
[ETM] i= 0 ,id= mqtt
[ETM] data= default-mqtt-server
[ETM] i= 1 ,id= mqpt
[ETM] data= 1883
[ETM] i= 2 ,id= user
[ETM] data= default-mqtt-username
[ETM] i= 3 ,id= mqpw
[ETM] data= default-mqtt-password
[ETM] i= 4 ,id= subs
[ETM] data= default-mqtt-SubTopic
[ETM] i= 5 ,id= pubs
[ETM] data= default-mqtt-PubTopic
[ETM] LoadCfgFile 
[ETM] OK
[ETM] LoadCredFile 
[ETM] ChkCrR: Buffer allocated, Sz= 35
[ETM] ChkCrR:pdata= new-mqtt-server ,len= 34
[ETM] ChkCrR:pdata= 1883 ,len= 6
[ETM] ChkCrR:pdata= new-mqtt-username ,len= 34
[ETM] ChkCrR:pdata= old-mqtt-password ,len= 34
[ETM] ChkCrR:pdata= old-mqtt-SubTopic ,len= 34
[ETM] ChkCrR:pdata= old-mqtt-PubTopic ,len= 34
[ETM] OK
[ETM] CrCCSum=0x 217e ,CrRCSum=0x 217e
[ETM] Buffer freed
[ETM] CCSum=0x 6e7 ,RCSum=0x 6e7
[ETM] LoadCredFile 
[ETM] CrR:pdata= new-mqtt-server ,len= 34
[ETM] CrR:pdata= 1883 ,len= 6
[ETM] CrR:pdata= new-mqtt-username ,len= 34
[ETM] CrR:pdata= old-mqtt-password ,len= 34
[ETM] CrR:pdata= old-mqtt-SubTopic ,len= 34
[ETM] CrR:pdata= old-mqtt-PubTopic ,len= 34
[ETM] OK
[ETM] CrCCSum=0x 217e ,CrRCSum=0x 217e
[ETM] Valid Stored Dynamic Data
[ETM] ======= Start Stored Config Data =======
[ETM] Header= nRF52 , BoardName= nRF52_W5500
[ETM] StaticIP= 192.168.2.222
[ETM] i= 0 ,id= mqtt
[ETM] data= new-mqtt-server
[ETM] i= 1 ,id= mqpt
[ETM] data= 1883
[ETM] i= 2 ,id= user
[ETM] data= new-mqtt-username
[ETM] i= 3 ,id= mqpw
[ETM] data= old-mqtt-password
[ETM] i= 4 ,id= subs
[ETM] data= old-mqtt-SubTopic
[ETM] i= 5 ,id= pubs
[ETM] data= old-mqtt-PubTopic
[ETM] Start connectEthernet using Static IP = 192.168.2.222
[ETM] MAC:FE-99-F8-DF-DA-BA
[ETM] IP: 192.168.2.222
[ETM] begin:Stay in CfgPortal: DRD
[ETM] CfgIP= 192.168.2.222
Connected! IP address: 192.168.2.222
H
Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = old-mqtt-password
Subs Topics = old-mqtt-SubTopic
Pubs Topics = old-mqtt-PubTopic
HHHH

Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = old-mqtt-password
Subs Topics = old-mqtt-SubTopic
Pubs Topics = old-mqtt-PubTopic
HHHH
```

#### 1.3. Config Portal started


```
[ETM] h1:myMenuItems[ 0 ]= new-mqtt-server
[ETM] h1:myMenuItems[ 1 ]= 1883
[ETM] h1:myMenuItems[ 2 ]= new-mqtt-username
[ETM] h1:myMenuItems[ 3 ]= old-mqtt-password
[ETM] h1:myMenuItems[ 4 ]= old-mqtt-SubTopic
[ETM] h1:myMenuItems[ 5 ]= old-mqtt-PubTopic
HHHHH HHHHHHH
```

#### 1.4. Credentials entered and Saved

```
[ETM] h:items updated = 0
[ETM] h:key = ip , value = 192.168.2.223
[ETM] h:ip
[ETM] h:items updated = 1
[ETM] h:key = nm , value = nRF52_W5500
[ETM] h:nm
[ETM] h:items updated = 2
[ETM] h:key = mqtt , value = new-mqtt-server
[ETM] h2:myMenuItems[ 0 ]= new-mqtt-server
[ETM] h:items updated = 3
[ETM] h:key = mqpt , value = 1883
[ETM] h2:myMenuItems[ 1 ]= 1883
[ETM] h:items updated = 4
[ETM] h:key = user , value = new-mqtt-username
[ETM] h2:myMenuItems[ 2 ]= new-mqtt-username
[ETM] h:items updated = 5
[ETM] h:key = mqpw , value = old-mqtt-password
[ETM] h2:myMenuItems[ 3 ]= old-mqtt-password
[ETM] h:items updated = 6
[ETM] h:key = subs , value = old-mqtt-SubTopic
[ETM] h2:myMenuItems[ 4 ]= old-mqtt-SubTopic
[ETM] h:items updated = 7
[ETM] h:key = pubs , value = old-mqtt-PubTopic
[ETM] h2:myMenuItems[ 5 ]= old-mqtt-PubTopic
[ETM] h:Updating EEPROM. Please wait for reset
[ETM] SaveCfgFile 
[ETM] WCSum=0x 6e8
[ETM] OK
[ETM] SaveBkUpCfgFile 
[ETM] OK
[ETM] SaveCredFile 
[ETM] CW1:pdata= new-mqtt-server ,len= 34
[ETM] CW1:pdata= 1883 ,len= 6
[ETM] CW1:pdata= new-mqtt-username ,len= 34
[ETM] CW1:pdata= old-mqtt-password ,len= 34
[ETM] CW1:pdata= old-mqtt-SubTopic ,len= 34
[ETM] CW1:pdata= old-mqtt-PubTopic ,len= 34
[ETM] OK
[ETM] CrWCSum= 217e
[ETM] SaveBkUpCredFile 
[ETM] CW2:pdata= new-mqtt-server ,len= 34
[ETM] CW2:pdata= 1883 ,len= 6
[ETM] CW2:pdata= new-mqtt-username ,len= 34
[ETM] CW2:pdata= old-mqtt-password ,len= 34
[ETM] CW2:pdata= old-mqtt-SubTopic ,len= 34
[ETM] CW2:pdata= old-mqtt-PubTopic ,len= 34
[ETM] OK
[ETM] h:Rst

```

---

#### 2. Ethernet_SAMD on SeeedStudio SAMD21 SEEED_XIAO_M0 with W5500 using Ethernet_Generic Library

This is the terminal output of an SeeedStudio SAMD21 SEEED_XIAO_M0 board with W5500 Ethernet shield using Ethernet_Generic Library, running [Ethernet_SAMD](examples/Ethernet_SAMD) example when **no doubleResetDetected**.

```
Start Ethernet_SAMD on SEEED_XIAO_M0
Ethernet Shield type : W5x00 using Ethernet Library
Ethernet_Manager v1.8.1
DoubleResetDetector_Generic v1.8.1
Flag read = 0xffffffff
No doubleResetDetected
SetFlag write = 0xd0d01234
[ETM] ======= Start Default Config Data =======
[ETM] Header= Eth_NonSSL , BoardName= Air-Control
[ETM] StaticIP= 
[ETM] i= 0 ,id= mqtt
[ETM] data= default-mqtt-server
[ETM] i= 1 ,id= mqpt
[ETM] data= 1883
[ETM] i= 2 ,id= user
[ETM] data= default-mqtt-username
[ETM] i= 3 ,id= mqpw
[ETM] data= default-mqtt-password
[ETM] i= 4 ,id= subs
[ETM] data= default-mqtt-SubTopic
[ETM] i= 5 ,id= pubs
[ETM] data= default-mqtt-PubTopic
[ETM] ChkCrR:CrCCSum=0x af50 ,CrRCSum=0x ffffffff
[ETM] CCSum=0x 0 ,RCSum=0x 0
[ETM] Invalid Stored Dynamic Data. Load default from Sketch
[ETM] SaveEEPROM,Sz= 1024
[ETM] DataSz= 0 ,WCSum=0x 71e
[ETM] pdata= default-mqtt-server ,len= 34
[ETM] pdata= 1883 ,len= 6
[ETM] pdata= default-mqtt-username ,len= 34
[ETM] pdata= default-mqtt-password ,len= 34
[ETM] pdata= default-mqtt-SubTopic ,len= 34
[ETM] pdata= default-mqtt-PubTopic ,len= 34
[ETM] CrCCSum=0x 29a6
[ETM] Header= SAMD , BoardName= Air-Control
[ETM] StaticIP= 
[ETM] i= 0 ,id= mqtt
[ETM] data= default-mqtt-server
[ETM] i= 1 ,id= mqpt
[ETM] data= 1883
[ETM] i= 2 ,id= user
[ETM] data= default-mqtt-username
[ETM] i= 3 ,id= mqpw
[ETM] data= default-mqtt-password
[ETM] i= 4 ,id= subs
[ETM] data= default-mqtt-SubTopic
[ETM] i= 5 ,id= pubs
[ETM] data= default-mqtt-PubTopic
[ETM] Start connectEthernet using DHCP
[ETM] MAC:FE-9A-F4-DB-DC-BA

W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 1
W5100::init: W5500, SSIZE =4096
Done
[ETM] IP: 192.168.2.199
[ETM] begin:Stay in CfgPortal: No CfgDat
[ETM] CfgIP= 192.168.2.199
Connected! IP address: 192.168.2.199

Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
HStop doubleResetDetecting
ClearFlag write = 0xd0d04321
```

---

#### 3. Ethernet_SAM_DUE on Arduino SAM DUE with W5100 using Ethernet_Generic Library

This is the terminal output of an Arduino SAM DUE board with W5100 Ethernet shield using Ethernet_Generic Library, running [Ethernet_SAM_DUE](examples/Ethernet_SAM_DUE) example when **no doubleResetDetected**.

```
Start Ethernet_SAM_DUE on SAM DUE
Ethernet Shield type : W5x00 using Ethernet_Generic Library
Ethernet_Manager v1.8.1
DoubleResetDetector_Generic v1.8.1
Flag read = 0xd0d01234
doubleResetDetected
ClearFlag write = 0xd0d04321
[ETM] =====================
[ETM] DRD. Run ConfigPortal
[ETM] =====================
[ETM] ======= Start Default Config Data =======
[ETM] Header=  , BoardName= 
[ETM] StaticIP= 
[ETM] Invalid Stored Dynamic Data. Load default from Sketch
[ETM] Header= SAMDUE , BoardName= 
[ETM] StaticIP= 
[ETM] Start connectEthernet using DHCP
[ETM] MAC:FE-9A-FD-DB-DE-BA
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5100, SSIZE =4096
[ETM] IP: 192.168.2.228
[ETM] begin:Stay in CfgPortal: DRD
[ETM] CfgIP= 192.168.2.228
Connected! IP address: 192.168.2.228
Ethernet type is W5100

Your stored Credentials :
MQTT Server = default-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
HHH[ETM] h:Updating EEPROM. Please wait for reset
⸮
Start Ethernet_SAM_DUE on SAM DUE
Ethernet Shield type : W5x00 using Ethernet_Generic Library
Ethernet_Manager v1.1.0
Flag read = 0xd0d04321
No doubleResetDetected
SetFlag write = 0xd0d01234
[ETM] ======= Start Default Config Data =======
[ETM] Header=  , BoardName= 
[ETM] StaticIP= 
[ETM] Header= SAMDUE , BoardName= DUE_ETM
[ETM] StaticIP= 192.168.2.222
[ETM] Start connectEthernet using Static IP = 192.168.2.222
[ETM] MAC:FE-9A-FD-DD-D9-BA

W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5100, SSIZE =4096
[ETM] IP: 192.168.2.222
[ETM] begin:Ethernet Connected.
Connected! IP address: 192.168.2.222
Ethernet type is W5100

Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = default-mqtt-username
MQTT PWD = default-mqtt-password
Subs Topics = default-mqtt-SubTopic
Pubs Topics = default-mqtt-PubTopic
Stop doubleResetDetecting
ClearFlag write = 0xd0d04321
HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH HHHHHHHHHH

```

---

#### 4. MQTT_ThingStream_Ethernet_Generic on ESP8266_NODEMCU with W5x00 using Ethernet_Generic Library

This is the terminal output of ESP8266_NODEMCU board with W5x00 using Ethernet_Generic Library, running complex [MQTT_ThingStream_Ethernet_Generic](examples/MQTT_ThingStream_Ethernet_Generic) example to demonstrate how to use dynamic parameters, entered via Config Portal, to connect to [**ThingStream MQTT Server**](mqtt.thingstream.io).

#### 4.1. Normal run without correct ThingStream MQTT Credentials

If no valid config data are stored in EEPROM, it will switch to `Configuration Mode`. Connect to access point at the IP address displayed on Terminal or Router's DHCP server as in the following picture:

<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Manager/blob/main/pics/MQTT_ConfigPortal_blank.png">
</p>


```
Start MQTT_ThingStream_Ethernet_Generic using LittleFS on ESP8266_NODEMCU
Ethernet Shield type : W5x00 using Ethernet_Generic Library
Ethernet_Manager v1.8.1
ESP_DoubleResetDetector v1.3.2
=========================
Currently Used SPI pinout:
MOSI:13
MISO:12
SCK:14
SS:15
=========================
LittleFS Flag read = 0xd0d04321
No doubleResetDetected
Saving config file...
Saving config file OK
[ETM] ======= Start Default Config Data =======
[ETM] Header= Eth_NonSSL , BoardName= Generic-Ethernet
[ETM] StaticIP= 
[ETM] CCSum=0x 9a7 ,RCSum=0x 9a7
[ETM] Invalid Stored Dynamic Data. Load default from Sketch
[ETM] Header= ESP8266 , BoardName= Generic-Ethernet
[ETM] StaticIP= 
[ETM] Start connectEthernet using DHCP
[ETM] MAC:FE-AB-CD-EF-ED-BA
[ETM] IP: 192.168.2.62
[ETM] begin:Stay in CfgPortal: No CfgDat
[ETM] CfgIP= 192.168.2.62
Connected! IP address: 192.168.2.62
***************************************
esp32-sniffer/12345678/ble
***************************************
Stop doubleResetDetecting
Saving config file...
Saving config file OK
[ETM] h:Updating LittleFS: /etm_config.dat
[ETM] h:Rst
```


#### 4.2. Got correct ThingStream MQTT Credentials from Config Portal

Enter your credentials (Blynk Servers/Tokens and Port). If you prefer static IP, input it (for example `192.168.2.220`) in the corresponding field. Otherwise, just leave it `blank` or `nothing` to use auto IP assigned by DHCP server.

<p align="center">
    <img src="https://github.com/khoih-prog/Ethernet_Manager/blob/main/pics/MQTT_ConfigPortal_ESP8266.png">
</p>

```
Start MQTT_ThingStream_Ethernet_Generic using LittleFS on ESP8266_NODEMCU
Ethernet Shield type : W5x00 using Ethernet_Generic Library
Ethernet_Manager v1.8.1
ESP_DoubleResetDetector v1.3.2
=========================
Currently Used SPI pinout:
MOSI:13
MISO:12
SCK:14
SS:15
=========================
LittleFS Flag read = 0xd0d04321
No doubleResetDetected
Saving config file...
Saving config file OK
[ETM] ======= Start Default Config Data =======
[ETM] Header= Eth_NonSSL , BoardName= Generic-Ethernet
[ETM] StaticIP= 
[ETM] CCSum=0x 975 ,RCSum=0x 975
[ETM] ======= Start Stored Config Data =======
[ETM] Header= ESP8266 , BoardName= ESP8266-Ethernet
[ETM] StaticIP= 192.168.2.222
[ETM] Start connectEthernet using Static IP = 192.168.2.222
[ETM] MAC:FE-AB-CD-EF-ED-BA
[ETM] IP: 192.168.2.222
[ETM] begin:Ethernet Connected.
Connected! IP address: 192.168.2.222
***************************************
esp32-sniffer/12345678/ble
***************************************
Attempting MQTT connection to mqtt.thingstream.io
...connected
Published connection message successfully!
Subcribed to: esp32-sniffer/12345678/ble

Your stored Credentials :
MQTT Server = mqtt.thingstream.io
Port = 1883
MQTT UserName = user_name
MQTT PWD = user_pwd
Client ID = client_ID
HStop doubleResetDetecting
Saving config file...
Saving config file OK

MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTT_ThingStream on ESP8266_NODEMCU with W5x00 using Ethernet_Generic Library
H
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTT_ThingStream on ESP8266_NODEMCU with W5x00 using Ethernet_Generic Library
H
```

---

#### 5. MQTT_ThingStream_Ethernet_Generic on NRF52840_FEATHER with ENC28J60 using EthernetENC Library

This is the terminal output of NRF52840_FEATHER board with ENC28J60 using EthernetENC Library, running complex [MQTT_ThingStream_Ethernet_Generic](examples/MQTT_ThingStream_Ethernet_Generic) example to demonstrate how to use dynamic parameters, entered via Config Portal, to connect to [**ThingStream MQTT Server**](mqtt.thingstream.io).

#### 5.1. Normal run without correct ThingStream MQTT Credentials

```
Start MQTT_ThingStream_Ethernet_Generic on NRF52840_FEATHER
Ethernet Shield type : ENC28J60 using EthernetENC Library
Ethernet_Manager v1.8.1
DoubleResetDetector_Generic v1.8.1
LittleFS Flag read = 0xd0d01234
Flag read = 0xd0d01234
doubleResetDetected
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
[ETM] =====================
[ETM] DRD. Run ConfigPortal
[ETM] =====================
[ETM] ======= Start Default Config Data =======
[ETM] Header= Eth_NonSSL , BoardName= nRF52-Ethernet
[ETM] StaticIP= 
[ETM] CCSum=0x 7a6 ,RCSum=0x 7a6
[ETM] ======= Start Stored Config Data =======
[ETM] Header= nRF52 , BoardName= nRF52-Ethernet
[ETM] StaticIP= 
[ETM] Start connectEthernet using DHCP
[ETM] MAC:FE-33-78-EF-ED-BA
[ETM] IP: 192.168.2.89
[ETM] begin:Stay in CfgPortal: DRD
[ETM] CfgIP= 192.168.2.89
Connected! IP address: 192.168.2.89
***************************************
esp32-sniffer/12345678/ble
***************************************
[ETM] h:Updating EEPROM. Please wait for reset
[ETM] h:Rst

```

#### 5.2. Got correct ThingStream MQTT Credentials from Config Portal

```
Start MQTT_ThingStream_Ethernet_Generic on NRF52840_FEATHER
Ethernet Shield type : ENC28J60 using EthernetENC Library
Ethernet_Manager v1.8.1
DoubleResetDetector_Generic v1.8.1
LittleFS Flag read = 0xd0d04321
Flag read = 0xd0d04321
No doubleResetDetected
Saving DOUBLERESETDETECTOR_FLAG to DRD file : 0xd0d01234
Saving DRD file OK
SetFlag write = 0xd0d01234
[ETM] ======= Start Default Config Data =======
[ETM] Header= Eth_NonSSL , BoardName= nRF52-Ethernet
[ETM] StaticIP= 
[ETM] CCSum=0x 8d3 ,RCSum=0x 8d3
[ETM] ======= Start Stored Config Data =======
[ETM] Header= nRF52 , BoardName= nRF52-Ethernet
[ETM] StaticIP= 192.168.2.222
[ETM] Start connectEthernet using Static IP = 192.168.2.222
[ETM] MAC:FE-33-78-EF-ED-BA
[ETM] IP: 192.168.2.222
[ETM] begin:Ethernet Connected.
Connected! IP address: 192.168.2.222
***************************************
esp32-sniffer/12345678/ble
***************************************
Attempting MQTT connection to mqtt.thingstream.io
...connected
Published connection message successfully!
Subcribed to: esp32-sniffer/12345678/ble

Your stored Credentials :
MQTT Server = mqtt.thingstream.io
Port = 1883
MQTT UserName = I7UPHZWCKHZASRDIOME9
MQTT PWD = k8UJuIOtke4yXeF1lY9mXbbCxTovHAAgE3CViJ/4
Client ID = device:352fc9a7-3211-4e46-8a9a-a390f2e4ca86
HStop doubleResetDetecting
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321

MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTT_ThingStream on NRF52840_FEATHER with ENC28J60 using EthernetENC Library
H
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTT_ThingStream on NRF52840_FEATHER with ENC28J60 using EthernetENC Library
H
```

---

#### 6. MQTT_ThingStream_Ethernet_RP2040 on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

This is the terminal output of RASPBERRY_PI_PICO board with W5x00 using Ethernet_Generic Library, running complex [MQTT_ThingStream_Ethernet_RP2040](examples/MQTT_ThingStream_Ethernet_RP2040) example to demonstrate how to use dynamic parameters, entered via Config Portal, to connect to [**ThingStream MQTT Server**](mqtt.thingstream.io).

#### 6.1. Normal run without correct ThingStream MQTT Credentials or DRD

```
Start MQTT_ThingStream_Ethernet_RP2040 on RASPBERRY_PI_PICO
Ethernet Shield type : W5x00 using Ethernet_Generic Library
Ethernet_Manager v1.8.1
DoubleResetDetector_Generic v1.8.1
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 19
[EWS] MISO: 16
[EWS] SCK: 18
[EWS] SS: 17
[EWS] =========================
[EWS] RPIPICO setCsPin: 17
[EWS] =========================
[EWS] Currently Used SPI pinout:
[EWS] MOSI: 19
[EWS] MISO: 16
[EWS] SCK: 18
[EWS] SS: 17
[EWS] =========================
LittleFS Flag read = 0xd0d01234
Flag read = 0xd0d01234
doubleResetDetected
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
[ETM] =====================
[ETM] DRD. Run ConfigPortal
[ETM] =====================
[ETM] CCSum=0x 8cb ,RCSum=0x 8cb
[ETM] CrCCsum=0x 2785 ,CrRCsum=0x 2785
[ETM] CrCCsum=0x 2785 ,CrRCsum=0x 2785
[ETM] Valid Stored Dynamic Data
[ETM] ======= Start Stored Config Data =======
[ETM] Header= RP2040 , BoardName= RP2040-Ethernet
[ETM] StaticIP= 192.168.2.233
[ETM] Start connectEthernet using Static IP = 192.168.2.233
[ETM] MAC:FE-99-F5-DF-DB-BA
[ETM] IP: 192.168.2.233
[ETM] bg: isForcedConfigPortal = false
[ETM] bg:Stay forever in CP: DRD/MRD
[ETM] clearForcedCP
[ETM] SaveCPFile 
[ETM] OK
[ETM] SaveBkUpCPFile 
[ETM] OK
[ETM] CfgIP= 192.168.2.233
Connected! IP address: 192.168.2.233
Ethernet type is W5500
***************************************
esp32-sniffer/12345678/ble
***************************************
```

#### 6.2. Got correct ThingStream MQTT Credentials from Config Portal

```
Start MQTT_ThingStream_Ethernet_RP2040 on RASPBERRY_PI_PICO
Ethernet Shield type : W5x00 using Ethernet_Generic Library
Ethernet_Manager v1.8.1
DoubleResetDetector_Generic v1.8.1
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 19
[EWS] MISO: 16
[EWS] SCK: 18
[EWS] SS: 17
[EWS] =========================
[EWS] RPIPICO setCsPin: 17
[EWS] =========================
[EWS] Currently Used SPI pinout:
[EWS] MOSI: 19
[EWS] MISO: 16
[EWS] SCK: 18
[EWS] SS: 17
[EWS] =========================
LittleFS Flag read = 0xd0d04321
Flag read = 0xd0d04321
No doubleResetDetected
Saving DOUBLERESETDETECTOR_FLAG to DRD file : 0xd0d01234
Saving DRD file OK
SetFlag write = 0xd0d01234
[ETM] CCSum=0x 8cb ,RCSum=0x 8cb
[ETM] CrCCsum=0x 2785 ,CrRCsum=0x 2785
[ETM] CrCCsum=0x 2785 ,CrRCsum=0x 2785
[ETM] Valid Stored Dynamic Data
[ETM] ======= Start Stored Config Data =======
[ETM] Header= RP2040 , BoardName= RP2040-Ethernet
[ETM] StaticIP= 192.168.2.233
[ETM] Start connectEthernet using Static IP = 192.168.2.233
[ETM] MAC:FE-9A-FB-DD-DB-8E
[ETM] IP: 192.168.2.233
[ETM] begin:Ethernet Connected.
Connected! IP address: 192.168.2.233
Ethernet type is W5500
***************************************
esp32-sniffer/12345678/ble
***************************************
Stop doubleResetDetecting
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
Attempting MQTT connection to mqtt.thingstream.io
...connected
Published connection message successfully!
Subcribed to: esp32-sniffer/12345678/ble
H
Your stored Credentials :
MQTT Server = mqtt.thingstream.io
Port = 1883
MQTT UserName = User_name
MQTT PWD = password
Client ID = device_id

MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTT_ThingStream on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTT_ThingStream on RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library
H
```

---

#### 7. Ethernet_RP2040 on MBED RASPBERRY_PI_PICO with W5500 using Ethernet_Generic Library

This is the terminal output of an MBED RASPBERRY_PI_PICO board with W5500 Ethernet shield using Ethernet_Generic Library, running [Ethernet_RP2040](examples/Ethernet_RP2040) example with **doubleResetDetected**.

#### 7.1 DRD => Config Portal

```
Start Ethernet_RP2040 on MBED RASPBERRY_PI_PICO
Ethernet Shield type : W5x00 using Ethernet_Generic Library
Ethernet_Manager v1.8.1
DoubleResetDetector_Generic v1.8.1
[[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 19
[EWS] MISO: 16
[EWS] SCK: 18
[EWS] SS: 17
[EWS] =========================
[EWS] RPIPICO setCsPin: 17
[EWS] =========================
[EWS] Currently Used SPI pinout:
[EWS] MOSI: 19
[EWS] MISO: 16
[EWS] SCK: 18
[EWS] SS: 17
[EWS] =========================
LittleFS size (KB) = 64
LittleFS Mount OK
LittleFS Flag read = 0xd0d01234
Flag read = 0xd0d01234
doubleResetDetected
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
[ETM] =====================
[ETM] DRD. Run ConfigPortal
[ETM] =====================
[ETM] CCSum=0x 477 ,RCSum=0x 477
[ETM] CrCCsum=0x 219f ,CrRCsum=0x 219f
[ETM] CrCCsum=0x 219f ,CrRCsum=0x 219f
[ETM] Valid Stored Dynamic Data
[ETM] ======= Start Stored Config Data =======
[ETM] Header= RP2040 , BoardName= MBED_RP2040
[ETM] StaticIP= 0
[ETM] Start connectEthernet using DHCP
[ETM] MAC:FE-99-FD-D7-DA-BA
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 5, new ss_pin = 10, W5100Class::ss_pin = 5
W5100::init: W5500, SSIZE =8192
[ETM] IP: 192.168.2.185
[ETM] bg: isForcedConfigPortal = false
[ETM] bg:Stay forever in CP: DRD/MRD
[ETM] clearForcedCP
[ETM] SaveCPFile 
[ETM] OK
[ETM] SaveBkUpCPFile 
[ETM] OK
[ETM] CfgIP= 192.168.2.185
Connected! IP address: 192.168.2.185
Ethernet type is W5500

Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = new-mqtt-password
Subs Topics = new-mqtt-SubTopic
Pubs Topics = new-mqtt-PubTopic
HHHH[ETM] h:Updating LittleFS: /fs/etm_config.dat
[ETM] WCSum=0x 477
[ETM] CrWCSum=0x 219f
[ETM] h:Rst

```

#### 7.2 Data Saved => Exit Config Portal


```
Start Ethernet_RP2040 on MBED RASPBERRY_PI_PICO
Ethernet Shield type : W5x00 using Ethernet_Generic Library
Ethernet_Manager v1.8.1
DoubleResetDetector_Generic v1.8.1
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 19
[EWS] MISO: 16
[EWS] SCK: 18
[EWS] SS: 17
[EWS] =========================
[EWS] RPIPICO setCsPin: 17
[EWS] =========================
[EWS] Currently Used SPI pinout:
[EWS] MOSI: 19
[EWS] MISO: 16
[EWS] SCK: 18
[EWS] SS: 17
[EWS] =========================
LittleFS size (KB) = 64
LittleFS Mount OK
LittleFS Flag read = 0xd0d04321
Flag read = 0xd0d04321
No doubleResetDetected
Saving DOUBLERESETDETECTOR_FLAG to DRD file : 0xd0d01234
Saving DRD file OK
SetFlag write = 0xd0d01234
[ETM] CCSum=0x 477 ,RCSum=0x 477
[ETM] CrCCsum=0x 219f ,CrRCsum=0x 219f
[ETM] CrCCsum=0x 219f ,CrRCsum=0x 219f
[ETM] Valid Stored Dynamic Data
[ETM] ======= Start Stored Config Data =======
[ETM] Header= RP2040 , BoardName= MBED_RP2040
[ETM] StaticIP= 0
[ETM] Start connectEthernet using DHCP
[ETM] MAC:FE-9A-FB-D7-D8-BA
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 5, new ss_pin = 10, W5100Class::ss_pin = 5
W5100::init: W5500, SSIZE =8192
[ETM] IP: 192.168.2.183
[ETM] begin:Ethernet Connected.
Connected! IP address: 192.168.2.183
Ethernet type is W5500

Your stored Credentials :
MQTT Server = new-mqtt-server
Port = 1883
MQTT UserName = new-mqtt-username
MQTT PWD = new-mqtt-password
Subs Topics = new-mqtt-SubTopic
Pubs Topics = new-mqtt-PubTopic
HStop doubleResetDetecting
Saving to DRD file : 0xd0d04321
Saving DRD file OK
LittleFS Flag read = 0xd0d04321
ClearFlag write = 0xd0d04321
HHHHHH
```

---


#### 8. MQTT_ThingStream_Ethernet_WT32_ETH01 on WT32-ETH01

This is the terminal output of WT32-ETH01 board with LAN8720 Ethernet, running complex [MQTT_ThingStream_Ethernet_WT32_ETH01](examples/MQTT_ThingStream_Ethernet_WT32_ETH01) example to demonstrate how to use dynamic parameters, entered via Config Portal, to connect to [**ThingStream MQTT Server**](mqtt.thingstream.io).

#### 8.1. Normal run with correct ThingStream MQTT Credentials

```
Start MQTT_ThingStream_Ethernet_WT32_ETH01 on WT32-ETH01
Ethernet Shield type : ETH_PHY_LAN8720
WebServer_WT32_ETH01 v1.5.0
Ethernet_Manager v1.8.1
ESP_DoubleResetDetector v1.3.2
[ETM] Set CustomsStyle to :  <style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>
[ETM] Set CustomsHeadElement to :  <style>html{filter: invert(10%);}</style>
[ETM] Set CORS Header to :  Your Access-Control-Allow-Origin
LittleFS Flag read = 0xD0D04321
No doubleResetDetected
Saving config file...
Saving config file OK
[ETM] LoadCfgFile 
[ETM] OK
[ETM] ======= Start Stored Config Data =======
[ETM] Header= WT32_ETH01 , BoardName= WT32_ETH01
[ETM] StaticIP= 192.168.2.232
[ETM] i= 0 ,id= mqtt
[ETM] data= default-mqtt-server
[ETM] i= 1 ,id= mqpt
[ETM] data= 1883
[ETM] i= 2 ,id= user
[ETM] data= default-mqtt-username
[ETM] i= 3 ,id= mqpw
[ETM] data= default-mqtt-password
[ETM] i= 4 ,id= clid
[ETM] data= default-mqtt-clientID
[ETM] CCSum=0x 7f0 ,RCSum=0x 7f0
[ETM] LoadCredFile 
[ETM] CrR:pdata= mqtt.thingstream.io ,len= 48
[ETM] CrR:pdata= 1883 ,len= 6
[ETM] CrR:pdata= mqtt_user ,len= 34
[ETM] CrR:pdata= mqtt_pass ,len= 48
[ETM] CrR:pdata= client_ID ,len= 48
[ETM] OK
[ETM] CrCCsum=0x 2785 ,CrRCsum=0x 2785
[ETM] Valid Stored Dynamic Data
[ETM] Start connectEthernet using Static IP = 192.168.2.232
[ETM] myGW IP = 192.168.2.1
[ETM] ETH Started
[ETM] ETH MAC: A8:03:2A:A1:61:73 , IPv4: 192.168.2.232
[ETM] FULL_DUPLEX, Link Speed (Mbps) 100
[ETM] IP: 192.168.2.232
[ETM] Check if isForcedCP
[ETM] LoadCPFile 
[ETM] OK
[ETM] begin:Ethernet Connected.
Connected! IP address: 192.168.2.232
***************************************
esp32-sniffer/12345678/ble
***************************************
Connecting to MQTT_SERVER = mqtt.thingstream.io, MQTT_PORT= 1883
Attempting MQTT connection to mqtt.thingstream.io
MQTT_CLIENT_ID = client_ID
MQTT_USER = mqtt_user
MQTT_PASS = mqtt_pass
...connected
Published connection message successfully!
Subcribed to: esp32-sniffer/12345678/ble

Your stored Credentials :
MQTT Server = mqtt.thingstream.io
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pass
Client ID = client_ID
HStop doubleResetDetecting
Saving config file...
Saving config file OK

MQTT Message Send : esp32-sniffer/12345678/ble => Hello from MQTT_ThingStream on WT32-ETH01 with ETH_PHY_LAN8720
H
MQTT Message receive [esp32-sniffer/12345678/ble] Hello from MQTT_ThingStream on WT32-ETH01 with ETH_PHY_LAN8720
H
```


---

#### 9. QNEthernet_Teensy on TEENSY 4.1 using QNEthernet

This is the terminal output of Teensy 4.1 board with built-in Ethernet, using QNEthernet Library, running [QNEthernet_Teensy](examples/QNEthernet_Teensy) example when **no doubleResetDetected**.

```
Starting QNEthernet_Teensy on TEENSY 4.1 using QNEthernet
Ethernet_Manager v1.8.1
DoubleResetDetector_Generic v1.8.1
[EWS] =========== USE_QN_ETHERNET ===========
QNEthernet using static IP

EEPROM size = 4284, start = 0
Flag read = 0xD0D04321
No doubleResetDetected
SetFlag write = 0xD0D01234
[ETM] Header= Teensy , BoardName= Teensy
[ETM] StaticIP= 192.168.2.232
[ETM] CCSum=0x 77e ,RCSum=0x 77e
[ETM] Header= Teensy , BoardName= Teensy
[ETM] StaticIP= 192.168.2.232
[ETM] ChkCrR:CrCCsum=0x 101b ,CrRCsum=0x 101b
[ETM] CrCCsum=0x 101b ,CrRCsum=0x 101b
[ETM] Valid Stored Dynamic Data
[ETM] ======= Start Stored Config Data =======
[ETM] Header= Teensy , BoardName= Teensy
[ETM] StaticIP= 192.168.2.232
[ETM] Start connectEthernet using Static IP = 192.168.2.232
[ETM] IP: 192.168.2.222
[ETM] begin:Ethernet Connected.
Connected! IP address: 192.168.2.222

Your stored Credentials :
MQTT Server = mqtt_server
Port = 1883
MQTT UserName = mqtt_user
MQTT PWD = mqtt_pwd
Subs Topics = Subs
Pubs Topics = Pubs
Stop doubleResetDetecting
ClearFlag write = 0xD0D04321
HHHH
```

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level from 0 to 4

```cpp
/* Comment this out to disable prints and save space */
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       0
#define _ETHERNET_MANAGER_LOGLEVEL_         2
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.

---
---


### Issues ###

Submit issues to: [Ethernet_Manager issues](https://github.com/khoih-prog/Ethernet_Manager/issues)

---
---

### TO DO

1. Same features for other boards with new Ethernet shields.
2. Add SSL/TLS feature.
3. Bug Searching and Killing
4. Support more non-compatible Ethernet Libraries such as Ethernet_Shield_W5200, EtherCard, EtherSia.

### DONE

 1. Permit EEPROM size and location configurable to avoid conflict with others.
 2. More flexible to configure reconnection timeout.
 3. For fresh config data, don't need to wait for connecting timeout before entering config portal.
 4. If the config data not entered completely (Serves, HardwarePort and Blynk tokens), entering config portal
 5. Change Synch XMLHttpRequest to Async
 6. Reduce memory usage.
 7. Support ENC28J60 as well as W5100/W5200/W5500 Ethernet shields
 8. Add checksums
 9. Support SAM DUE, SAMD, Teensy boards
10. Easy-to-use **Dynamic Parameters** without the necessity to write complicated ArduinoJSon functions
11. Permit to input special chars such as **%** and **#** into data fields.
12. Support more types of boards using Ethernet shields : **nRF52** boards, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, etc.**
Default Credentials and dynamic parameters
13. **DoubleDetectDetector** to force Config Portal when double reset is detected within predetermined time, default 10s.
14. Configurable Config Portal Title
15. Re-structure all examples to separate Credentials / Defines / Dynamic Params / Code so that you can change Credentials / Dynamic Params quickly for each device.
16. Add **LittleFS** support to ESP8266 as SPIFFS deprecated since **ESP8266 core 2.7.1.**
17. Add support to new [**`EthernetENC library`**](https://github.com/jandrassy/EthernetENC) for ENC28J60.
18. Add support to new [`NativeEthernet Library version stable111+`](https://github.com/vjmuzik/NativeEthernet) for Teensy 4.1.
19. Add support ESP32/ESP8266 boards
20. Add Table of Contents and Version String
21. Configurable **Customs HTML Headers**, including Customs Style, Customs Head Elements, CORS Header
22. Add support to **ESP32-S2 (ESP32-S2 Saola, AI-Thinker ESP-12K, etc.)**
23. Add support to RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [Earle Philhower's arduino-pico core](https://github.com/earlephilhower/arduino-pico) and LittleFS.
24. Add support to RP2040-based boards, such as **Nano RP2040 Connect**, using [**Arduino mbed OS for Nano boards**](https://github.com/arduino/ArduinoCore-mbed) and LittleFS.
25. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** v2.1.0+ core](https://github.com/arduino/ArduinoCore-mbed) and LittleFS.
26. Add support to **WT32_ETH01 boards** using ESP32-based boards and LAN8720 Ethernet
27. Add support to Teensy 4.1 built-in Ethernet using [`QNEthernet`](https://github.com/ssilverman/QNEthernet) library
28. Auto detect ESP32 core and use either built-in LittleFS or [LITTLEFS](https://github.com/lorol/LITTLEFS) library for ESP32 and WT32-ETH01.
29. Fix QNEthernet-related linkStatus.
30. Add support to many more RP2040 boards
31. Add support to generic SAMD21 : `__SAMD21E1xA__`, `__SAMD21G1xA__` and `__SAMD21J1xA__`
32. Update to be compatible with new `FlashStorage_SAMD` library version
33. Use new [**Ethernet_Generic** library](https://github.com/khoih-prog/Ethernet_Generic) as default for W5x00.
34. Support **SPI2 for ESP32**
35. Add support to SPI1 for RP2040 using [arduino-pico core](https://github.com/earlephilhower/arduino-pico)
36. Drop `EthernetWrapper`
37. Fix `macAddress` bug. Check [Unable so set MAC Address #2](https://github.com/khoih-prog/Ethernet_Manager/issues/2)
38. Permit setting `macAddress` for supporting Ethernet shields W5x00 and ENC28J60
39. Add functions relating to `macAddress`
40. Fix chipID and add getChipID(), getChipOUI() for `ESP32` and `WT32_ETH01`


---
---

### Contributions and Thanks

1. Thanks to [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing
2. Thanks to [sahlex](https://github.com/sahlex) to report issue [Unable so set MAC Address #2](https://github.com/khoih-prog/Ethernet_Manager/issues/2) leading to version v1.8.0

<table>
  <tr>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>⭐️ Miguel Wisintainer</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/sahlex"><img src="https://github.com/sahlex.png" width="100px;" alt="sahlex"/><br /><sub><b>sahlex</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/Ethernet_Manager/blob/main/LICENSE)

---

### Copyright

Copyright 2020- Khoi Hoang


