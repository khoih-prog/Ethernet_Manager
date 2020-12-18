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

#if ( defined(CORE_TEENSY) )
  // Don't support Teensy 2.x, LC
  #if defined(ETHERNET_USE_TEENSY)
    #undef ETHERNET_USE_TEENSY
  #endif
  #define ETHERNET_USE_TEENSY         true
  #define USE_DYNAMIC_PARAMETERS      true
#else
  #error This code is designed to run on Teensy platform! Please check your Tools->Board setting.  
#endif

/* Comment this out to disable prints and save space */
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       2
#define _ETHERNET_MANAGER_LOGLEVEL_         2

#define DRD_GENERIC_DEBUG                   true

// Default pin 10 to SS/CS
#define USE_THIS_SS_PIN       10

#if defined(__IMXRT1062__)
  // For Teensy 4.1/4.0
  #if defined(ARDUINO_TEENSY41)
    #define BOARD_TYPE      "TEENSY 4.1"
    // Use true for NativeEthernet Library, false if using other Ethernet libraries
    #define USE_NATIVE_ETHERNET     true
  #elif defined(ARDUINO_TEENSY40)
    #define BOARD_TYPE      "TEENSY 4.0"
  #else
    #define BOARD_TYPE      "TEENSY 4.x"
  #endif      
#elif defined(__MK66FX1M0__)
  #define BOARD_TYPE "Teensy 3.6"
#elif defined(__MK64FX512__)
  #define BOARD_TYPE "Teensy 3.5"
#elif defined(__MKL26Z64__)
  #define BOARD_TYPE "Teensy LC"
#elif defined(__MK20DX256__)
  #define BOARD_TYPE "Teensy 3.2" // and Teensy 3.1 (obsolete)
#elif defined(__MK20DX128__)
  #define BOARD_TYPE "Teensy 3.0"
#elif defined(__AVR_AT90USB1286__)
  #error Teensy 2.0++ not supported yet
#elif defined(__AVR_ATmega32U4__)
  #error Teensy 2.0 not supported yet
#else
  // For Other Boards
  #define BOARD_TYPE      "Unknown Teensy Board"
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
  
#elif USE_UIP_ETHERNET

  #warning Using UIPEthernet library
  #define SHIELD_TYPE           "ENC28J60 using UIPEthernet Library"
#endif      // #if !USE_UIP_ETHERNET

//////////////////////////////////////////

// EEPROM_START + CONFIG_DATA_SIZE must be <= EEPROM_SIZE
#define EEPROM_START   0

//////////////////////////////////////////

//#define USE_SSL   true
#define USE_SSL   false

#if USE_SSL
  // Need ArduinoECCX08 and ArduinoBearSSL libraries
  // Currently, error not enough memory for UNO, Mega2560. Don't use
  #include <EthernetSSL_Manager.h>
#else
  #include <Ethernet_Manager.h>
#endif

#ifndef SHIELD_TYPE
  #define SHIELD_TYPE     "Unknown Ethernet shield/library" 
#endif

#define W5100_CS        10
#define SDCARD_CS       4

#define ETHERNET_HOST_NAME   "Teensy-Ethernet"

#endif      //defines_h
