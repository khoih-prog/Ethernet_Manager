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

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(ETHERNET_USE_SAM_DUE)
    #undef ETHERNET_USE_SAM_DUE
  #endif
  #define ETHERNET_USE_SAM_DUE        true
  #define USE_DYNAMIC_PARAMETERS      true
#else
  #error This code is designed to run on SAM-DUE platform! Please check your Tools->Board setting.    
#endif

/* Comment this out to disable prints and save space */
#define ETHERNET_MANAGER_DEBUG_PORT         Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       0
#define _ETHERNET_MANAGER_LOGLEVEL_         2

#define DRD_GENERIC_DEBUG                   true

// For SAMD
// Default pin 10 to SS/CS
#define USE_THIS_SS_PIN       10

#define BOARD_TYPE      "SAM DUE"

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

// EEPROM_START + CONFIG_DATA_SIZE must be <= EEPROM_SIZE
#define EEPROM_START   0

//////////////////////////////////////////

#include <Ethernet_Manager.h>

#ifndef SHIELD_TYPE
  #define SHIELD_TYPE     "Unknown Ethernet shield/library" 
#endif

#define W5100_CS        10
#define SDCARD_CS       4

#define ETHERNET_HOST_NAME   "SAMDUE-Ethernet"

#endif      //defines_h
