/****************************************************************************************************************************
  defines.h
  For W5x00, LAN8720 and ENC28J60 Ethernet shields.

  Ethernet_Manager is a library for nRF52, Teensy, STM32, SAM DUE and SAMD boards, with Ethernet W5x00, LAN8720 or ENC28J60 shields,
  to enable easy configuration/reconfiguration of Credentials and autoconnect/autoreconnect of Ethernet.
  AVR Mega is not supported.

  Built by Khoi Hoang https://github.com/khoih-prog/Ethernet_Manager
  Licensed under MIT license
 *****************************************************************************************************************************/

#ifndef defines_h
#define defines_h

#if ( defined(NANO_RP2040_CONNECT)    || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || \
      defined(ARDUINO_GENERIC_RP2040) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) )
  // For RPI Pico
  #if defined(ETHERNET_USE_RPIPICO)
    #undef ETHERNET_USE_RPIPICO
  #endif
  #define ETHERNET_USE_RPIPICO         true
  #define USE_DYNAMIC_PARAMETERS        true
  
  #warning Use RPI-Pico RP2040 architecture
#else
  #error This code is designed to run on RP2040 platform! Please check your Tools->Board setting.
#endif

/* Comment this out to disable prints and save space */
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       2
#define _ETHERNET_MANAGER_LOGLEVEL_         2

#define DRD_GENERIC_DEBUG                   true

// Default pin 5 (in Mbed) or 17 to SS/CS
#if defined(ARDUINO_ARCH_MBED)
  // For RPI Pico using Arduino Mbed RP2040 core
  // SCK: GPIO2,  MOSI: GPIO3, MISO: GPIO4, SS/CS: GPIO5
  
  #define USE_THIS_SS_PIN       17

  #if defined(BOARD_NAME)
    #undef BOARD_NAME
  #endif

  #if defined(ARDUINO_RASPBERRY_PI_PICO) 
    #define BOARD_TYPE      "MBED RASPBERRY_PI_PICO"
  #elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040)
    #define BOARD_TYPE      "MBED DAFRUIT_FEATHER_RP2040"
  #elif defined(ARDUINO_GENERIC_RP2040)
    #define BOARD_TYPE      "MBED GENERIC_RP2040"
  #else
    #define BOARD_TYPE      "MBED Unknown RP2040"
  #endif
  
#else

  #define USING_SPI2          false     //true
  
  // For RPI Pico using E. Philhower RP2040 core
  #if (USING_SPI2)
    // SCK: GPIO14,  MOSI: GPIO15, MISO: GPIO12, SS/CS: GPIO13 for SPI1
    #define USE_THIS_SS_PIN       13
  #else
    // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17 for SPI0
    #define USE_THIS_SS_PIN       17
  #endif

#endif
 
#define SS_PIN_DEFAULT        USE_THIS_SS_PIN

#ifndef BOARD_NAME
  #define BOARD_NAME    BOARD_TYPE
#endif

#include <SPI.h>

// Use true  for ENC28J60 and UIPEthernet library (https://github.com/UIPEthernet/UIPEthernet)
// Use false for W5x00 and Ethernetx library      (https://www.arduino.cc/en/Reference/Ethernet)

//#define USE_UIP_ETHERNET   true
#define USE_UIP_ETHERNET   false

#if ( !defined(USE_UIP_ETHERNET) || !USE_UIP_ETHERNET )

  // To override the default CS/SS pin. Don't use unless you know exactly which pin to use
  // You can define here or customize for each board at same place with BOARD_TYPE
  // Check @ defined(SEEED_XIAO_M0)
  //#define USE_THIS_SS_PIN   22  //21  //5 //4 //2 //15
  
  // Only one if the following to be true
  #define USE_ETHERNET_GENERIC  true
  #define USE_ETHERNET_ENC      false
  #define USE_CUSTOM_ETHERNET   false
  
  ////////////////////////////
  
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
    #ifdef USE_CUSTOM_ETHERNET
      #undef USE_CUSTOM_ETHERNET
    #endif
    #define USE_CUSTOM_ETHERNET   false
  #endif

  #if USE_ETHERNET_GENERIC

    #if USING_SPI2
      #define SHIELD_TYPE           "W5x00 using Ethernet_Generic Library on SPI1"
    #else
      #define SHIELD_TYPE           "W5x00 using Ethernet_Generic Library on SPI0/SPI"
    #endif 

    #define ETHERNET_LARGE_BUFFERS

    #define _ETG_LOGLEVEL_                      1
    
    #include "Ethernet_Generic.h"
    #warning Using Ethernet_Generic lib

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
    #ifdef USE_ETHERNET_GENERIC
      #undef USE_ETHERNET_GENERIC
    #endif
    #define USE_ETHERNET_GENERIC   true
    #include "Ethernet_Generic.h"
    #warning Using default Ethernet_Generic lib
    #define SHIELD_TYPE           "W5x00 using default Ethernet_Generic Library"
  #endif
  
  // Ethernet_Shield_W5200, EtherCard, EtherSia not supported
  // Select just 1 of the following #include if uncomment #define USE_CUSTOM_ETHERNET
  // Otherwise, standard Ethernet library will be used for W5x00
  
  ////////////////////////////
  
#elif USE_UIP_ETHERNET
    #include "UIPEthernet.h"
    #warning Using UIPEthernet library
    #define SHIELD_TYPE           "ENC28J60 using UIPEthernet Library"
#endif      // #if !USE_UIP_ETHERNET

/////////////////////////////////////////////

// Add customs headers from v1.2.0
#define USING_CUSTOMS_STYLE                 true
#define USING_CUSTOMS_HEAD_ELEMENT          true
#define USING_CORS_FEATURE                  true

/////////////////////////////////////////////

// Config Timeout 120s (default 60s)
#define CONFIG_TIMEOUT                      120000L

#define USE_DYNAMIC_PARAMETERS              true

//////////////////////////////////////////

#include <Ethernet_Manager.h>

#ifndef SHIELD_TYPE
  #define SHIELD_TYPE     "Unknown Ethernet shield/library"
#endif

#define W5100_CS        10
#define SDCARD_CS       4

#define ETHERNET_HOST_NAME   "RP2040-Ethernet"

#endif      //defines_h
