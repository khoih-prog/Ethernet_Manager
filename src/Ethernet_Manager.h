/****************************************************************************************************************************
  Ethernet_Manager.h
  For W5x00 and ENC28J60 Ethernet shields.

  Ethernet_Manager is a library for nRF52, Teensy, STM32, SAM DUE and SAMD boards, with Ethernet W5x00 or ENC28J60 shields,
  to enable easy configuration/reconfiguration of Credentials and autoconnect/autoreconnect of Ethernet.
  AVR Mega is not supported.

  Built by Khoi Hoang https://github.com/khoih-prog/Ethernet_Manager
  Licensed under MIT license
  Version: 1.1.0

  Version  Modified By   Date      Comments
  -------  -----------  ---------- -----------
  1.0.0     K Hoang     14/12/2020 Initial coding.
  1.1.0     K Hoang     17/12/2020 Add support to ESP32/ESP8266. Add MQTT related examples to demo dynamic parameter usage
 *****************************************************************************************************************************/

#pragma once

#ifndef Ethernet_Manager_h
#define Ethernet_Manager_h

#define ETHERNET_MANAGER_VERSION      "Ethernet_Manager v1.1.0"

#if ( USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE || USE_ETHERNET_ESP8266 || USE_ETHERNET_ENC || USE_NATIVE_ETHERNET )
  #ifdef USE_CUSTOM_ETHERNET
    #undef USE_CUSTOM_ETHERNET
  #endif
  #define USE_CUSTOM_ETHERNET   false
#endif
    
#include "Ethernet_Manager_Debug.h"

#if ( !defined(USE_UIP_ETHERNET) || !USE_UIP_ETHERNET )
    
  #if USE_NATIVE_ETHERNET
    #include "NativeEthernet.h"
    #warning Using NativeEthernet lib for Teensy 4.1. Must also use Teensy Packages Patch or error
    #define SHIELD_TYPE           "Custom Ethernet using Teensy 4.1 NativeEthernet Library"
  #elif USE_ETHERNET3
    #include "Ethernet3.h"
    #warning Using Ethernet3 lib from Ethernet_Manager.h
    #define SHIELD_TYPE           "W5x00 using Ethernet3 Library"
  #elif USE_ETHERNET2
    #include "Ethernet2.h"
    #warning Using Ethernet2 lib from Ethernet_Manager.h
    #define SHIELD_TYPE           "W5x00 using Ethernet2 Library"
  #elif USE_ETHERNET_LARGE
    #include "EthernetLarge.h"
    #warning Using EthernetLarge lib from Ethernet_Manager.h
    #define SHIELD_TYPE           "W5x00 using EthernetLarge Library"
  #elif USE_ETHERNET_ESP8266
    #include "Ethernet_ESP8266.h"
    #warning Using Ethernet_ESP8266 lib from Ethernet_Manager.h
    #define SHIELD_TYPE           "W5x00 using Ethernet_ESP8266 Library" 
  #elif USE_ETHERNET_ENC
    #include "EthernetENC.h"
    #warning Using EthernetENC lib from Ethernet_Manager.h
    #define SHIELD_TYPE           "ENC28J60 using EthernetENC Library"
  #elif USE_CUSTOM_ETHERNET
    //#include "Ethernet_XYZ.h"
    #include "EthernetENC.h"
    #warning Using Custom Ethernet library from Ethernet_Manager.h. You must include a library and initialize.
    #define SHIELD_TYPE           "Custom Ethernet using Ethernet_XYZ Library"
  #else
    #ifdef USE_ETHERNET
      #undef USE_ETHERNET
    #endif
    #define USE_ETHERNET   true
    #include "Ethernet.h"
    #warning Using Ethernet lib from Ethernet_Manager.h
    #define SHIELD_TYPE           "W5x00 using Ethernet Library"
  #endif

#else
    #include "UIPEthernet.h"
    #warning Using UIPEthernet lib from Ethernet_Manager.h
    #define SHIELD_TYPE           "ENC28J60 using UIPEthernet Library"

#endif

#if USE_NATIVE_ETHERNET
  #include <NativeEthernetClient.h>
#else
  #include <EthernetClient.h>
#endif

#include <EthernetWebServer.h>

#if ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD51P19A__) || defined(__SAMD21G18A__) )
  #if defined(ETHERNET_USE_SAMD)
    #undef ETHERNET_USE_SAMD
  #endif
  #define ETHERNET_USE_SAMD      true
#endif

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(ETHERNET_USE_SAM_DUE)
    #undef ETHERNET_USE_SAM_DUE
  #endif
  #define ETHERNET_USE_SAM_DUE      true
#endif

#if ( defined(CORE_TEENSY) && !( defined(__MKL26Z64__) || defined(__AVR_AT90USB1286__) || defined(__AVR_ATmega32U4__) ) )
  #if defined(ETHERNET_USE_TEENSY)
    #undef ETHERNET_USE_TEENSY
  #endif
  #define ETHERNET_USE_TEENSY         true
#endif

#if ( defined(ESP8266) )
  // For ESP8266
  #if defined(ETHERNET_USE_ESP8266)
    #undef ETHERNET_USE_ESP8266
  #endif
  #define ETHERNET_USE_ESP8266         true
#endif

#if ( defined(ESP32) )
  // For ESP32
  #if defined(ETHERNET_USE_ESP32)
    #undef ETHERNET_USE_ESP32
  #endif
  #define ETHERNET_USE_ESP32         true
#endif

#if ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
        defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
        defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )
  #if defined(ETHERNET_USE_NRF52)
    #undef ETHERNET_USE_NRF528XX
  #endif
  #define ETHERNET_USE_NRF528XX         true
#endif

#if (ETHERNET_USE_SAMD)
  #include <Adapters/Ethernet_SAMD_Manager.h>
#elif (ETHERNET_USE_SAM_DUE)
  #include <Adapters/Ethernet_DUE_Manager.h>
#elif (ETHERNET_USE_TEENSY)
  #include <Adapters/Ethernet_Teensy_Manager.h>
#elif (ETHERNET_USE_ESP32)
  #include <Adapters/Ethernet_ESP32_Manager.h>
#elif (ETHERNET_USE_ESP8266)
  #include <Adapters/Ethernet_ESP8266_Manager.h>
#elif (ETHERNET_USE_NRF528XX)
  #include <Adapters/Ethernet_NRF52_Manager.h>
#else
  #error This code for SAMD21, SAMD51, SAM-DUE, Teensy (4.1/4.0, 3.x), ESP8266, ESP32, nRF52 boards, not AVR Mega nor STM32! Please check your Tools->Board setting.
#endif


#endif    // Ethernet_Manager_h
