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

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       3

#define ETHERNET_USE_WT32_ETH01             true

#include <WebServer_WT32_ETH01.h>

//////////////////////////////////////////

// Not use #define USE_SPIFFS  => using EEPROM for configuration data in Ethernet_Manager
// #define USE_SPIFFS    false => using EEPROM for configuration data in Ethernet_Manager
// #define USE_SPIFFS    true  => using SPIFFS for configuration data in Ethernet_Manager
// Be sure to define USE_SPIFFS before #include <Ethernet_Manager.h>

// Start location in EEPROM to store config data. Default 0
// Config data Size currently is 128 bytes w/o chksum, 132 with chksum)
//#define EEPROM_START     1024

// TODO, to add ESP32 LittleFS support
// For ESP32
#define USE_LITTLEFS                false
#define USE_SPIFFS                  false

#if USE_LITTLEFS
  //LittleFS has higher priority
  #define CurrentFileFS     "LittleFS"
  #ifdef USE_SPIFFS
    #undef USE_SPIFFS
  #endif
  #define USE_SPIFFS                  false
#elif USE_SPIFFS
  #define CurrentFileFS     "SPIFFS"
#endif

#if !( USE_LITTLEFS || USE_SPIFFS)

  #if !( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
    // EEPROM_SIZE must be <= 2048 and >= CONFIG_DATA_SIZE (currently 172 bytes)
    #if !defined(EEPROM_SIZE)
      #define EEPROM_SIZE    (2 * 1024)
    #endif
  #endif
  
  // EEPROM_START + CONFIG_DATA_SIZE must be <= EEPROM_SIZE
  #define EEPROM_START   0
#endif

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

#define ETHERNET_HOST_NAME   "WT32_ETH01"

#endif      //defines_h
