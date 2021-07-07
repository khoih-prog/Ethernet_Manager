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

#if ESP32
  #if defined(ETHERNET_USE_WT32_ETH01)
    #undef ETHERNET_USE_WT32_ETH01
  #endif
  #define ETHERNET_USE_WT32_ETH01           true
  #define USE_DYNAMIC_PARAMETERS            true
  
  #warning Use ESP32 architecture for WT32_ETH01
#else
  #error This code is designed to run on WT32_ETH01 and ESP32 platform! Please check your Tools->Board setting.
#endif

/* Comment this out to disable prints and save space */
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       2
#define _ETHERNET_MANAGER_LOGLEVEL_         4

/////////////////////////////////////////////

#define DOUBLERESETDETECTOR_DEBUG           true

#define USE_LITTLEFS                        true
#define USE_SPIFFS                          false

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
#define SHIELD_TYPE     "WT32_ETH01"
#endif

#define W5100_CS        10
#define SDCARD_CS       4

#define ETHERNET_HOST_NAME   "WT32_ETH01"

#endif      //defines_h
