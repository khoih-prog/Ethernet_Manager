/****************************************************************************************************************************
  defines.h
  For W5x00 and ENC28J60 Ethernet shields.

  Ethernet_Manager is a library for nRF52, Teensy, STM32, SAM DUE and SAMD boards, with Ethernet W5x00 or ENC28J60 shields,
  to enable easy configuration/reconfiguration of Credentials and autoconnect/autoreconnect of Ethernet.
  AVR Mega is not supported.

  Built by Khoi Hoang https://github.com/khoih-prog/Ethernet_Manager
  Licensed under MIT license
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h

#if ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD51P19A__) || defined(__SAMD21G18A__) )
  #if defined(ETHERNET_USE_SAMD)
    #undef ETHERNET_USE_SAMD
  #endif
  #define ETHERNET_USE_SAMD           true
  #define USE_DYNAMIC_PARAMETERS      true
#else
  #error This code is designed to run on SAMD21/SAMD51 platform! Please check your Tools->Board setting.    
#endif

/* Comment this out to disable prints and save space */
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       0
#define _ETHERNET_MANAGER_LOGLEVEL_         2

#define DRD_GENERIC_DEBUG                   true

// For SAMD
// Default pin 10 to SS/CS
#define USE_THIS_SS_PIN       10

#if ( defined(ARDUINO_SAMD_ZERO) && !defined(SEEED_XIAO_M0) )
  #define BOARD_TYPE      "SAMD Zero"
#elif defined(ARDUINO_SAMD_MKR1000)
  #define BOARD_TYPE      "SAMD MKR1000"
#elif defined(ARDUINO_SAMD_MKRWIFI1010)
  #define BOARD_TYPE      "SAMD MKRWIFI1010"
#elif defined(ARDUINO_SAMD_NANO_33_IOT)
  #define BOARD_TYPE      "SAMD NANO_33_IOT"
#elif defined(ARDUINO_SAMD_MKRFox1200)
  #define BOARD_TYPE      "SAMD MKRFox1200"
#elif ( defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) )
  #define BOARD_TYPE      "SAMD MKRWAN13X0"
#elif defined(ARDUINO_SAMD_MKRGSM1400)
  #define BOARD_TYPE      "SAMD MKRGSM1400"
#elif defined(ARDUINO_SAMD_MKRNB1500)
  #define BOARD_TYPE      "SAMD MKRNB1500"
#elif defined(ARDUINO_SAMD_MKRVIDOR4000)
  #define BOARD_TYPE      "SAMD MKRVIDOR4000"
#elif defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
  #define BOARD_TYPE      "SAMD ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS"
#elif defined(ADAFRUIT_FEATHER_M0_EXPRESS)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_FEATHER_M0_EXPRESS"
#elif defined(ADAFRUIT_METRO_M0_EXPRESS)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_METRO_M0_EXPRESS"
#elif defined(ADAFRUIT_CIRCUITPLAYGROUND_M0)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_CIRCUITPLAYGROUND_M0"
#elif defined(ADAFRUIT_GEMMA_M0)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_GEMMA_M0"
#elif defined(ADAFRUIT_TRINKET_M0)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_TRINKET_M0"
#elif defined(ADAFRUIT_ITSYBITSY_M0)
  #define BOARD_TYPE      "SAMD21 ADAFRUIT_ITSYBITSY_M0"
#elif defined(ARDUINO_SAMD_HALLOWING_M0)
  #define BOARD_TYPE      "SAMD21 ARDUINO_SAMD_HALLOWING_M0"
#elif defined(ADAFRUIT_METRO_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_METRO_M4_EXPRESS"
#elif defined(ADAFRUIT_GRAND_CENTRAL_M4)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_GRAND_CENTRAL_M4"
#elif defined(ADAFRUIT_FEATHER_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_FEATHER_M4_EXPRESS"
#elif defined(ADAFRUIT_ITSYBITSY_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_ITSYBITSY_M4_EXPRESS"
  #define USE_THIS_SS_PIN       10
#elif defined(ADAFRUIT_TRELLIS_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_TRELLIS_M4_EXPRESS"
#elif defined(ADAFRUIT_PYPORTAL)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYPORTAL"
#elif defined(ADAFRUIT_PYPORTAL_M4_TITANO)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYPORTAL_M4_TITANO"
#elif defined(ADAFRUIT_PYBADGE_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYBADGE_M4_EXPRESS"
#elif defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_METRO_M4_AIRLIFT_LITE"
#elif defined(ADAFRUIT_PYGAMER_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYGAMER_M4_EXPRESS"
#elif defined(ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYGAMER_ADVANCE_M4_EXPRESS"
#elif defined(ADAFRUIT_PYBADGE_AIRLIFT_M4)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_PYBADGE_AIRLIFT_M4"
#elif defined(ADAFRUIT_MONSTER_M4SK_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_MONSTER_M4SK_EXPRESS"
#elif defined(ADAFRUIT_HALLOWING_M4_EXPRESS)
  #define BOARD_TYPE      "SAMD51 ADAFRUIT_HALLOWING_M4_EXPRESS"
#elif defined(SEEED_WIO_TERMINAL)
  #define BOARD_TYPE      "SAMD SEEED_WIO_TERMINAL"
#elif defined(SEEED_FEMTO_M0)
  #define BOARD_TYPE      "SAMD SEEED_FEMTO_M0"
#elif defined(SEEED_XIAO_M0)
  #define BOARD_TYPE      "SAMD SEEED_XIAO_M0"
  #ifdef USE_THIS_SS_PIN
    #undef USE_THIS_SS_PIN
  #endif
  #define USE_THIS_SS_PIN       A1
  #warning define SEEED_XIAO_M0 USE_THIS_SS_PIN == A1
#elif defined(Wio_Lite_MG126)
  #define BOARD_TYPE      "SAMD SEEED Wio_Lite_MG126"
#elif defined(WIO_GPS_BOARD)
  #define BOARD_TYPE      "SAMD SEEED WIO_GPS_BOARD"
#elif defined(SEEEDUINO_ZERO)
  #define BOARD_TYPE      "SAMD SEEEDUINO_ZERO"
#elif defined(SEEEDUINO_LORAWAN)
  #define BOARD_TYPE      "SAMD SEEEDUINO_LORAWAN"
#elif defined(SEEED_GROVE_UI_WIRELESS)
  #define BOARD_TYPE      "SAMD SEEED_GROVE_UI_WIRELESS"
#elif defined(__SAMD21E18A__)
  #define BOARD_TYPE      "SAMD21E18A"
#elif defined(__SAMD21G18A__)
  #define BOARD_TYPE      "SAMD21G18A"
#elif defined(__SAMD51G19A__)
  #define BOARD_TYPE      "SAMD51G19A"
#elif defined(__SAMD51J19A__)
  #define BOARD_TYPE      "SAMD51J19A"
#elif defined(__SAMD51J20A__)
  #define BOARD_TYPE      "SAMD51J20A"
#elif defined(__SAM3X8E__)
  #define BOARD_TYPE      "SAM3X8E"
#elif defined(__CPU_ARC__)
  #define BOARD_TYPE      "CPU_ARC"
#elif defined(__SAMD51__)
  #define BOARD_TYPE      "SAMD51"
#else
  #define BOARD_TYPE      "SAMD Unknown"
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#include <SPI.h>

//#define USE_ETHERNET_WRAPPER    true
#define USE_ETHERNET_WRAPPER    false

// Use true  for ENC28J60 and UIPEthernet library (https://github.com/UIPEthernet/UIPEthernet)
// Use false for W5x00 and Ethernetx library      (https://www.arduino.cc/en/Reference/Ethernet)

//#define USE_UIP_ETHERNET   true
#define USE_UIP_ETHERNET   false

// Note: To rename ESP628266 Ethernet lib files to Ethernet_ESP8266.h and Ethernet_ESP8266.cpp
// In order to USE_ETHERNET_ESP8266
#if ( !defined(USE_UIP_ETHERNET) || !USE_UIP_ETHERNET )

  // To override the default CS/SS pin. Don't use unless you know exactly which pin to use
  // You can define here or customize for each board at same place with BOARD_TYPE
  // Check @ defined(SEEED_XIAO_M0)
  //#define USE_THIS_SS_PIN   22  //21  //5 //4 //2 //15
  
  // Only one if the following to be true
  #define USE_ETHERNET          false
  #define USE_ETHERNET2         false
  #define USE_ETHERNET3         false
  #define USE_ETHERNET_LARGE    true
  #define USE_ETHERNET_ESP8266  false 
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
  
  #if !USE_ETHERNET_WRAPPER
  
    #if ( USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE || USE_ETHERNET_ESP8266 || USE_ETHERNET_ENC || USE_NATIVE_ETHERNET )
      #ifdef USE_CUSTOM_ETHERNET
        #undef USE_CUSTOM_ETHERNET
      #endif
      #define USE_CUSTOM_ETHERNET   false
    #endif

    #if USE_NATIVE_ETHERNET
      #include "NativeEthernet.h"
      #warning Using NativeEthernet lib for Teensy 4.1. Must also use Teensy Packages Patch or error
      #define SHIELD_TYPE           "Custom Ethernet using Teensy 4.1 NativeEthernet Library"
    #elif USE_ETHERNET3
      #include "Ethernet3.h"
      #warning Using Ethernet3 lib
      #define SHIELD_TYPE           "W5x00 using Ethernet3 Library"
    #elif USE_ETHERNET2
      #include "Ethernet2.h"
      #warning Using Ethernet2 lib
      #define SHIELD_TYPE           "W5x00 using Ethernet2 Library"
    #elif USE_ETHERNET_LARGE
      #include "EthernetLarge.h"
      #warning Using EthernetLarge lib
      #define SHIELD_TYPE           "W5x00 using EthernetLarge Library"
    #elif USE_ETHERNET_ESP8266
      #include "Ethernet_ESP8266.h"
      #warning Using Ethernet_ESP8266 lib 
      #define SHIELD_TYPE           "W5x00 using Ethernet_ESP8266 Library" 
    #elif USE_ETHERNET_ENC
      #include "EthernetENC.h"
      #warning Using EthernetENC lib
      #define SHIELD_TYPE           "ENC28J60 using EthernetENC Library"
    #elif USE_CUSTOM_ETHERNET
      //#include "Ethernet_XYZ.h"
      #include "EthernetENC.h"
      #warning Using Custom Ethernet library. You must include a library and initialize.
      #define SHIELD_TYPE           "Custom Ethernet using Ethernet_XYZ Library"
    #else
      #ifdef USE_ETHERNET
        #undef USE_ETHERNET
      #endif
      #define USE_ETHERNET   true
      #include "Ethernet.h"
      #warning Using Ethernet lib
      #define SHIELD_TYPE           "W5x00 using Ethernet Library"
    #endif
    
    // Ethernet_Shield_W5200, EtherCard, EtherSia not supported
    // Select just 1 of the following #include if uncomment #define USE_CUSTOM_ETHERNET
    // Otherwise, standard Ethernet library will be used for W5x00
  
  #endif    //  USE_ETHERNET_WRAPPER
#elif USE_UIP_ETHERNET
    #include "UIPEthernet.h"
    #warning Using UIPEthernet library
    #define SHIELD_TYPE           "ENC28J60 using UIPEthernet Library"
#endif      // #if !USE_UIP_ETHERNET

//////////////////////////////////////////

#define EEPROM_SIZE    (2 * 1024)
// EEPROM_START + CONFIG_DATA_SIZE must be <= EEPROM_SIZE
#define EEPROM_START   0

//////////////////////////////////////////

#include <Ethernet_Manager.h>

#ifndef SHIELD_TYPE
  #define SHIELD_TYPE     "Unknown Ethernet shield/library" 
#endif

#define W5100_CS        10
#define SDCARD_CS       4

#define ETHERNET_HOST_NAME   "SAMD-Ethernet"

#endif      //defines_h
