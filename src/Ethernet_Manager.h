/****************************************************************************************************************************
  Ethernet_Manager.h
  For W5x00, LAN8720 and ENC28J60 Ethernet shields.

  Ethernet_Manager is a library for nRF52, Teensy, STM32, SAM DUE and SAMD boards, with Ethernet W5x00, LAN8720 or ENC28J60 shields,
  to enable easy configuration/reconfiguration of Credentials and autoconnect/autoreconnect of Ethernet.
  AVR Mega is not supported.

  Built by Khoi Hoang https://github.com/khoih-prog/Ethernet_Manager
  Licensed under MIT license

  Version: 1.8.1

  Version  Modified By   Date      Comments
  -------  -----------  ---------- -----------
  1.0.0     K Hoang     14/12/2020 Initial coding.
  1.1.0     K Hoang     17/12/2020 Add support to ESP32/ESP8266. Add MQTT related examples to demo dynamic parameter usage
  1.1.1     K Hoang     28/12/2020 Suppress all possible compiler warnings
  1.2.0     K Hoang     22/02/2021 Optimize code and use better FlashStorage_SAMD and FlashStorage_STM32. 
                                   Add customs HTML header feature. Fix bug.
  1.3.0     K Hoang     16/05/2021 Add support to RP2040-based boards such as RASPBERRY_PI_PICO
  1.4.0     K Hoang     28/05/2021 Add support to Nano_RP2040_Connect, RASPBERRY_PI_PICO using RP2040 Arduino mbed core
  1.5.0     K Hoang     06/07/2021 Add support to WT32_ETH01 (ESP32 + LAN8720) boards
  1.6.0     K Hoang     05/09/2021 Add support to QNEthernet Library for Teensy 4.1
  1.6.1     K Hoang     10/10/2021 Update `platform.ini` and `library.json`
  1.7.0     K Hoang     27/11/2021 Auto detect ESP32 core to use correct LittleFS. Fix QNEthernet-related linkStatus.
  1.7.1     K Hoang     26/01/2022 Update to be compatible with new FlashStorage libraries.
  1.7.2     K Hoang     10/04/2022 Use Ethernet_Generic library as default. Support SPI1/SPI2 for RP2040/ESP32
  1.8.0     K Hoang     07/09/2022 Fix macAddress bug. Add functions relating to macAddress
  1.8.1     K Hoang     09/09/2022 Fix chipID and add getChipOUI() for ESP32
 *****************************************************************************************************************************/

#pragma once

#ifndef Ethernet_Manager_h
#define Ethernet_Manager_h

///////////////////////////////////////////////////////////////

#ifndef ETHERNET_MANAGER_VERSION
  #define ETHERNET_MANAGER_VERSION            "Ethernet_Manager v1.8.1"

  #define ETHERNET_MANAGER_VERSION_MAJOR      1
  #define ETHERNET_MANAGER_VERSION_MINOR      8
  #define ETHERNET_MANAGER_VERSION_PATCH      1

  #define ETHERNET_MANAGER_VERSION_INT        1008001

#endif

///////////////////////////////////////////////////////////////

#if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC || USE_NATIVE_ETHERNET )
  #ifdef USE_CUSTOM_ETHERNET
    #undef USE_CUSTOM_ETHERNET
  #endif
  #define USE_CUSTOM_ETHERNET   false
#endif
    
#include "Ethernet_Manager_Debug.h"

///////////////////////////////////////////////////////////////

#if USE_NATIVE_ETHERNET
  #include <NativeEthernetClient.h>
  #include <EthernetWebServer.h>
#elif USE_QN_ETHERNET
  #include <QNEthernetClient.h>
  #include <EthernetWebServer.h>  
#elif ETHERNET_USE_WT32_ETH01
  #include <WebServer_WT32_ETH01.h>
#else
  #include <EthernetClient.h>
  #include <EthernetWebServer.h>
#endif

///////////////////////////////////////////////////////////////

#if ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD51P19A__) || defined(__SAMD21G18A__) )
  #if defined(ETHERNET_USE_SAMD)
    #undef ETHERNET_USE_SAMD
  #endif
  #define ETHERNET_USE_SAMD      true

#elif ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(ETHERNET_USE_SAM_DUE)
    #undef ETHERNET_USE_SAM_DUE
  #endif
  #define ETHERNET_USE_SAM_DUE      true

#elif ( defined(CORE_TEENSY) && !( defined(__MKL26Z64__) || defined(__AVR_AT90USB1286__) || defined(__AVR_ATmega32U4__) ) )
  #if defined(ETHERNET_USE_TEENSY)
    #undef ETHERNET_USE_TEENSY
  #endif
  #define ETHERNET_USE_TEENSY         true

#elif ( defined(ESP8266) )
  // For ESP8266
  #if defined(ETHERNET_USE_ESP8266)
    #undef ETHERNET_USE_ESP8266
  #endif
  #define ETHERNET_USE_ESP8266         true

#elif ( defined(ESP32) )
  // For ESP32
  #if defined(ETHERNET_USE_ESP32)
    #undef ETHERNET_USE_ESP32
  #endif
  #define ETHERNET_USE_ESP32         true
  
#elif ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
        defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
        defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )
  #if defined(ETHERNET_USE_NRF528XX)
    #undef ETHERNET_USE_NRF528XX
  #endif
  #define ETHERNET_USE_NRF528XX         true

#elif ( defined(NANO_RP2040_CONNECT)    || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || \
        defined(ARDUINO_GENERIC_RP2040) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) ) 
  #if defined(ETHERNET_USE_RPIPICO)
    #undef ETHERNET_USE_RPIPICO
  #endif
  #define ETHERNET_USE_RPIPICO      true
  
#endif

///////////////////////////////////////////////////////////////

#if (ETHERNET_USE_SAMD)
  #include <Adapters/Ethernet_SAMD_Manager.h>
#elif (ETHERNET_USE_SAM_DUE)
  #include <Adapters/Ethernet_DUE_Manager.h>
#elif (ETHERNET_USE_TEENSY)
  #if USE_NATIVE_ETHERNET
    #include <Adapters/Ethernet_Teensy_Manager.h>
  #elif USE_QN_ETHERNET
    #include <Adapters/QNEthernet_Teensy_Manager.h>
  #endif  
#elif ETHERNET_USE_WT32_ETH01
  #include <Adapters/Ethernet_WT32_ETH01_Manager.h>  
#elif (ETHERNET_USE_ESP32)
  #include <Adapters/Ethernet_ESP32_Manager.h>
#elif (ETHERNET_USE_ESP8266)
  #include <Adapters/Ethernet_ESP8266_Manager.h>
#elif (ETHERNET_USE_NRF528XX)
  #include <Adapters/Ethernet_NRF52_Manager.h>
#elif (ETHERNET_USE_RPIPICO)  && !defined(ARDUINO_ARCH_MBED)
  #include <Adapters/Ethernet_RP2040_Manager.h>  
#elif (ETHERNET_USE_RPIPICO)  && defined(ARDUINO_ARCH_MBED)
  #include <Adapters/Ethernet_MBED_RP2040_Manager.h>
#else
  #error This code for SAMD21, SAMD51, SAM-DUE, Teensy (4.1/4.0, 3.x), ESP8266, ESP32, nRF52, RP2040 boards, not AVR Mega nor STM32! Please check your Tools->Board setting.
#endif

///////////////////////////////////////////////////////////////

#endif    // Ethernet_Manager_h
