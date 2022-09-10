/****************************************************************************************************************************
  Ethernet_ESP8266_Manager.h
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

#ifndef Ethernet_ESP8266_Manager_h
#define Ethernet_ESP8266_Manager_h

#if defined(ESP8266)
  #if defined(ETHERNET_USE_ESP8266)
    #undef ETHERNET_USE_ESP8266
  #endif
  #warning ETHERNET_USE_ESP8266 from Ethernet_ESP8266_Manager.h
  #define ETHERNET_USE_ESP8266      true
#else
  #error This code is designed to run on ETHERNET_USE_ESP8266 platform! Please check your Tools->Board setting.
#endif

// Increase HTTP_UPLOAD_BUFLEN to 4K, instead of default 2K in <EthernetWebServer.h>
#define HTTP_UPLOAD_BUFLEN    4096

#include "FS.h"

#if USE_LITTLEFS
  #include <LittleFS.h>
  FS* filesystem =      &LittleFS;
  #define FileFS        LittleFS
#elif USE_SPIFFS
  FS* filesystem =      &SPIFFS;
  #define FileFS        SPIFFS
#else
  #include <EEPROM.h>
#endif

//////////////////////////////////////////

#ifndef USING_CUSTOMS_STYLE
  #define USING_CUSTOMS_STYLE     false
#endif

#ifndef USING_CUSTOMS_HEAD_ELEMENT
  #define USING_CUSTOMS_HEAD_ELEMENT     false
#endif

#ifndef USING_CORS_FEATURE
  #define USING_CORS_FEATURE     false
#endif

///////// NEW for DRD /////////////
// These defines must be put before #include <ESP_DoubleResetDetector.h>
// to select where to store DoubleResetDetector's variable.
// For ESP32, You must select one to be true (EEPROM, LittleFS or SPIFFS)
// For ESP8266, You must select one to be true (RTC, EEPROM, LittleFS or SPIFFS)
// Otherwise, library will use default EEPROM storage

#if USE_LITTLEFS
  #define ESP_DRD_USE_LITTLEFS    true
  #define ESP_DRD_USE_SPIFFS      false
  #define ESP_DRD_USE_EEPROM      false
#elif USE_SPIFFS
  #define ESP_DRD_USE_LITTLEFS    false
  #define ESP_DRD_USE_SPIFFS      true
  #define ESP_DRD_USE_EEPROM      false
#else
  #define ESP_DRD_USE_LITTLEFS    false
  #define ESP_DRD_USE_SPIFFS      false
  #define ESP_DRD_USE_EEPROM      true
#endif

#define ESP8266_DRD_USE_RTC       false

#ifndef DOUBLERESETDETECTOR_DEBUG
  #define DOUBLERESETDETECTOR_DEBUG     false
#endif

#include <ESP_DoubleResetDetector.h>      //https://github.com/khoih-prog/ESP_DoubleResetDetector

// Number of seconds after reset during which a
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 10

// RTC Memory Address for the DoubleResetDetector to use
#define DRD_ADDRESS 0

//DoubleResetDetector drd(DRD_TIMEOUT, DRD_ADDRESS);
DoubleResetDetector* drd;

///////// NEW for DRD /////////////

#define ESP_getChipId()   (ESP.getChipId())


//NEW
#define MAX_ID_LEN                5
#define MAX_DISPLAY_NAME_LEN      16

typedef struct
{
  char id             [MAX_ID_LEN + 1];
  char displayName    [MAX_DISPLAY_NAME_LEN + 1];
  char *pdata;
  uint8_t maxlen;
} MenuItem;
//

#if USE_DYNAMIC_PARAMETERS
  #warning Using Dynamic Parameters
  ///NEW
  extern uint16_t NUM_MENU_ITEMS;
  extern MenuItem myMenuItems [];
  bool *menuItemUpdated = nullptr;
#else
  #warning Not using Dynamic Parameters
#endif

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    ( 2 )

#define HEADER_MAX_LEN            16
#define STATIC_IP_MAX_LEN         16
#define BOARD_NAME_MAX_LEN        24

typedef struct Configuration
{
  char header         [HEADER_MAX_LEN];
  char static_IP      [STATIC_IP_MAX_LEN];
  char board_name     [BOARD_NAME_MAX_LEN];
  int  checkSum;
} Ethernet_Configuration;

// Currently CONFIG_DATA_SIZE  =  ( 60 )
uint16_t CONFIG_DATA_SIZE = sizeof(Ethernet_Configuration);

extern bool LOAD_DEFAULT_CONFIG_DATA;
extern Ethernet_Configuration defaultConfig;

// -- HTML page fragments

const char ETM_HTML_HEAD_START[] /*PROGMEM*/ = "<!DOCTYPE html><html><head><title>Ethernet_ESP8266_Manager</title>";

const char ETM_HTML_HEAD_STYLE[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";

const char ETM_HTML_HEAD_END[]   /*PROGMEM*/ = "</head><div style='text-align:left;display:inline-block;min-width:260px;'>\
<fieldset><div><label>StaticIP</label><input value='[[ip]]'id='ip'><div></div></div></fieldset>\
<fieldset><div><label>Board Name</label><input value='[[nm]]'id='nm'><div></div></div></fieldset>";

const char ETM_FLDSET_START[]  /*PROGMEM*/ = "<fieldset>";
const char ETM_FLDSET_END[]    /*PROGMEM*/ = "</fieldset>";
const char ETM_HTML_PARAM[]    /*PROGMEM*/ = "<div><label>{b}</label><input value='[[{v}]]'id='{i}'><div></div></div>";
const char ETM_HTML_BUTTON[]   /*PROGMEM*/ = "<button onclick=\"sv()\">Save</button></div>";
const char ETM_HTML_SCRIPT[]   /*PROGMEM*/ = "<script id=\"jsbin-javascript\">\
function udVal(key,val){var request=new XMLHttpRequest();var url='/?key='+key+'&value='+encodeURIComponent(val);request.open('GET',url,false);request.send(null);}\
function sv(){udVal('ip',document.getElementById('ip').value);\
udVal('nm',document.getElementById('nm').value);";

const char ETM_HTML_SCRIPT_ITEM[]  /*PROGMEM*/ = "udVal('{d}',document.getElementById('{d}').value);";
const char ETM_HTML_SCRIPT_END[]   /*PROGMEM*/ = "alert('Updated');}</script>";
const char ETM_HTML_END[]          /*PROGMEM*/ = "</html>";

//////////////////////////////////////////

//KH Add repeatedly used const
//KH, from v1.1.0
const char WM_HTTP_HEAD_CL[]         PROGMEM = "Content-Length";
const char WM_HTTP_HEAD_TEXT_HTML[]  PROGMEM = "text/html";
const char WM_HTTP_HEAD_TEXT_PLAIN[] PROGMEM = "text/plain";

const char WM_HTTP_CACHE_CONTROL[]   PROGMEM = "Cache-Control";
const char WM_HTTP_NO_STORE[]        PROGMEM = "no-cache, no-store, must-revalidate";
const char WM_HTTP_PRAGMA[]          PROGMEM = "Pragma";
const char WM_HTTP_NO_CACHE[]        PROGMEM = "no-cache";
const char WM_HTTP_EXPIRES[]         PROGMEM = "Expires";

const char WM_HTTP_CORS[]            PROGMEM = "Access-Control-Allow-Origin";
const char WM_HTTP_CORS_ALLOW_ALL[]  PROGMEM = "*";

//////////////////////////////////////////

class Ethernet_Manager
{

  public:
  
#ifndef LED_BUILTIN
#define LED_BUILTIN       13
#endif

#define LED_OFF     LOW
#define LED_ON      HIGH

    void begin(bool initialConfig = false)
    {   
      //Turn OFF
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LED_OFF);
      
      //// New DRD ////
      drd = new DoubleResetDetector(DRD_TIMEOUT, DRD_ADDRESS);  
      bool noConfigPortal = true;
   
      if (drd->detectDoubleReset())
      {
        ETM_LOGWARN(F("====================="));
        ETM_LOGWARN(F("DRD. Run ConfigPortal"));
        ETM_LOGWARN(F("====================="));
        noConfigPortal = false;
      }
      
      //// New DRD ////
      
      if (LOAD_DEFAULT_CONFIG_DATA)
      {
        ETM_LOGERROR(F("======= Start Default Config Data ======="));
        displayConfigData(defaultConfig);
      }

      hadConfigData = getConfigData();

      connectEthernet();
      
      isForcedConfigPortal = isForcedCP();

      //// New DRD ////
      //  noConfigPortal when getConfigData() OK and no MRD/DRD'ed
      if (hadConfigData && noConfigPortal && (!isForcedConfigPortal) )   
      //// New DRD //// 
      {
        hadConfigData = true;

        if (ethernetConnected)
        {
          ETM_LOGWARN(F("begin:Ethernet Connected."));
          
          if (initialConfig)
          {
            ETM_LOGWARN(F("begin: Start ConfigPortal"));
            // Start configuration mode
            startConfigurationMode();
          }

        }
        else
        {
          // Can't do anything here
          ETM_LOGWARN(F("begin:Ethernet not Connected"));
          // failed to connect to Ethernet, will start configuration mode
          //startConfigurationMode();
        }
      }
      else
      {      
        ETM_LOGERROR(isForcedConfigPortal? F("bg: isForcedConfigPortal = true") : F("bg: isForcedConfigPortal = false"));
                     
        // If not persistent => clear the flag so that after reset. no more CP, even CP not entered and saved
        if (persForcedConfigPortal)
        {
          ETM_LOGERROR1(F("bg:Stay forever in CP:"), isForcedConfigPortal ? F("Forced-Persistent") : (noConfigPortal ? F("No ConfigDat") : F("DRD/MRD")));
        }
        else
        {
          ETM_LOGERROR1(F("bg:Stay forever in CP:"), isForcedConfigPortal ? F("Forced-non-Persistent") : (noConfigPortal ? F("No ConfigDat") : F("DRD/MRD")));
          clearForcedCP();
        }
          
        //To permit autoreset after timeout if DRD/MRD or non-persistent forced-CP 
        hadConfigData = isForcedConfigPortal ? true : (noConfigPortal ? false : true);
        
        // failed to connect to WiFi, will start configuration mode
        startConfigurationMode();
      }
    }
    
    //////////////////////////////////////////

    // Return true if still in CP mode
    bool run()
    {
      //static int retryTimes = 0;
      
      //// New DRD ////
      // Call the double reset detector loop method every so often,
      // so that it can recognise when the timeout expires.
      // You can also call drd.stop() when you wish to no longer
      // consider the next reset as a double reset.
      drd->loop();
      //// New DRD ////

      // Be sure to reconnect Ethernet first
      if (!ethernetConnected)
      {
        connectEthernet();
      }

      // Connection OK. Run CP if requested.
      if (ethernetConnected)
      {
        // If configTimeout but user hasn't connected to configWeb => try to reconnect Blynk.
        // But if user has connected to configWeb, stay there until done, then reset hardware
        if ( configuration_mode && ( configTimeout == 0 ||  millis() < configTimeout ) )
        {
          retryTimes = 0;

          if (server)
          {
            server->handleClient();
          }
        }
        else
        {
#if RESET_IF_CONFIG_TIMEOUT
          // If we're here but still in configuration_mode, permit running TIMES_BEFORE_RESET times before reset hardware
          // to permit user another chance to config.
          if ( configuration_mode && (configTimeout != 0) )
          {
            if (++retryTimes <= CONFIG_TIMEOUT_RETRYTIMES_BEFORE_RESET)
            {
              ETM_LOGWARN1(F("run:TimeOut.Tried #"), retryTimes);
            }
            else
            {
              resetFunc();
            }
          }
#endif
        }
      }
      else if (configuration_mode)
      {
        configuration_mode = false;
        ETM_LOGWARN(F("run:Ethernet not OK"));
        
        // Turn the LED_BUILTIN OFF when out of configuration mode. 
        digitalWrite(LED_BUILTIN, LED_OFF);
      }
      
      return configuration_mode;
    }

    //////////////////////////////////////////

    String getBoardName()
    {
      return (String(Ethernet_Manager_config.board_name));
    }
    
    //////////////////////////////////////////

    Ethernet_Configuration* getFullConfigData(Ethernet_Configuration *configData)
    {
      if (!hadConfigData)
        getConfigData();

      // Check if nullptr pointer
      if (configData)
        memcpy(configData, &Ethernet_Manager_config, sizeof(Ethernet_Manager_config));

      return (configData);
    }
    
    //////////////////////////////////////////
    
    void clearConfigData()
    {
      memset(&Ethernet_Manager_config, 0, sizeof(Ethernet_Manager_config));

#if USE_DYNAMIC_PARAMETERS        
      for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
      }
#endif
      
      saveConfigData();
    }
    
    //////////////////////////////////////////////
    
    bool isConfigDataValid()
    {
      return hadConfigData;
    }
    
    //////////////////////////////////////////////
    
    // Forced CP => Flag = 0xBEEFBEEF. Else => No forced CP
    // Flag to be stored at (EEPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE) 
    // to avoid corruption to current data
    //#define FORCED_CONFIG_PORTAL_FLAG_DATA              ( (uint32_t) 0xDEADBEEF)
    //#define FORCED_PERS_CONFIG_PORTAL_FLAG_DATA         ( (uint32_t) 0xBEEFDEAD)
    
    const uint32_t FORCED_CONFIG_PORTAL_FLAG_DATA       = 0xDEADBEEF;
    const uint32_t FORCED_PERS_CONFIG_PORTAL_FLAG_DATA  = 0xBEEFDEAD;
    
    #define FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE     4
    
    void resetAndEnterConfigPortal()
    {
      persForcedConfigPortal = false;
      
      setForcedCP(false);
      
      // Delay then reset the ESP8266 after save data
      delay(1000);
      resetFunc();
    }
    
    //////////////////////////////////////////////
    
    // This will keep CP forever, until you successfully enter CP, and Save data to clear the flag.
    void resetAndEnterConfigPortalPersistent()
    {
      persForcedConfigPortal = true;
      
      setForcedCP(true);
      
      // Delay then reset the ESP8266 after save data
      delay(1000);
      resetFunc();
    }
    
    //////////////////////////////////////////////

    void resetFunc()
    {
      delay(1000);
      ESP.reset();
    }

    //////////////////////////////////////
    
    // Add customs headers from v1.1.0
    
    // New from v1.1.0, for configure CORS Header, default to WM_HTTP_CORS_ALLOW_ALL = "*"

#if USING_CUSTOMS_STYLE
    //sets a custom style, such as color
    // "<style>div,input{padding:5px;font-size:1em;}
    // input{width:95%;}body{text-align: center;}
    // button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}
    // fieldset{border-radius:0.3rem;margin:0px;}</style>";
    void setCustomsStyle(const char* CustomsStyle = ETM_HTML_HEAD_STYLE) 
    {
      ETM_HTML_HEAD_CUSTOMS_STYLE = CustomsStyle;
      ETM_LOGDEBUG1(F("Set CustomsStyle to :"), ETM_HTML_HEAD_CUSTOMS_STYLE);
    }
    
    //////////////////////////////////////////////
    
    const char* getCustomsStyle()
    {
      ETM_LOGDEBUG1(F("Get CustomsStyle ="), ETM_HTML_HEAD_CUSTOMS_STYLE);
      return ETM_HTML_HEAD_CUSTOMS_STYLE;
    }
#endif
    
    //////////////////////////////////////////////

#if USING_CUSTOMS_HEAD_ELEMENT    
    //sets a custom element to add to head, like a new style tag
    void setCustomsHeadElement(const char* CustomsHeadElement = nullptr) 
    {
      _CustomsHeadElement = CustomsHeadElement;
      ETM_LOGDEBUG1(F("Set CustomsHeadElement to :"), _CustomsHeadElement);
    }
    
    //////////////////////////////////////////////
    
    const char* getCustomsHeadElement()
    {
      ETM_LOGDEBUG1(F("Get CustomsHeadElement ="), _CustomsHeadElement);
      return _CustomsHeadElement;
    }
#endif
       
    //////////////////////////////////////////////
 
#if USING_CORS_FEATURE   
    void setCORSHeader(const char* CORSHeaders = nullptr)
    {     
      _CORS_Header = CORSHeaders;

      ETM_LOGDEBUG1(F("Set CORS Header to :"), _CORS_Header);
    }
    
    //////////////////////////////////////////////
    
    const char* getCORSHeader()
    {      
      ETM_LOGDEBUG1(F("Get CORS Header ="), _CORS_Header);
      return _CORS_Header;
    }
#endif
    
    //////////////////////////////////////////////

		uint8_t* getMacAddress()
		{
      return macAddress;
		}
    
    //////////////////////////////////////////////
		
		uint8_t* setMacAddress(const uint8_t* mac)
		{
		  if ( isMacAddressValid(mac) )
		    memcpy(macAddress, mac, sizeof(macAddress));
		    
		  printMacAddress();  
		    
      return macAddress;
		}
    
    //////////////////////////////////////////////

		void printMacAddress()
		{
			char theLocalBuffer[24];
					
			snprintf(theLocalBuffer, sizeof(theLocalBuffer), "MAC:%02X-%02X-%02X-%02X-%02X-%02X",
				       macAddress[0], macAddress[1],
				       macAddress[2], macAddress[3],
				       macAddress[4], macAddress[5]);
			
			ETM_LOGWARN(theLocalBuffer);
		}
    
    //////////////////////////////////////////////
		
		bool isMacAddressValid(const uint8_t* mac)
		{
		  return ( (mac != nullptr) && ( (mac[0] != 0) || (mac[1] != 0) || (mac[2] != 0) || (mac[3] != 0) ) );
		}
          
    //////////////////////////////////////


  private:
   
    // Initialize the Ethernet server library
    // with the IP address and port you want to use
    // (port 80 is default for HTTP):
    EthernetWebServer *server;

    bool ethernetConnected = false;
    
    int  retryTimes         = 0;

    bool configuration_mode = false;

    unsigned long configTimeout;
    bool hadConfigData = false;
    
    bool isForcedConfigPortal   = false;
    bool persForcedConfigPortal = false;

    Ethernet_Configuration Ethernet_Manager_config;
    
    uint16_t totalDataSize = 0;
    
    uint8_t currentBlynkServerIndex = 255;
    
    uint8_t macAddress[6] = { 0, 0, 0, 0, 0, 0 };

/////////////////////////////////////
    
    // Add customs headers from v1.1.0
    
#if USING_CUSTOMS_STYLE
    const char* ETM_HTML_HEAD_CUSTOMS_STYLE = nullptr;
#endif
    
#if USING_CUSTOMS_HEAD_ELEMENT
    const char* _CustomsHeadElement = nullptr;
#endif
    
#if USING_CORS_FEATURE    
    const char* _CORS_Header        = WM_HTTP_CORS_ALLOW_ALL;   //"*";
#endif
       
    //////////////////////////////////////
    
#define RFC952_HOSTNAME_MAXLEN      24

    char RFC952_hostname[RFC952_HOSTNAME_MAXLEN + 1];

    void setRFC952_hostname(const char* iHostname = "")
    {
      if (iHostname[0] == 0)
      {
        String _hostname = "ESP82662-XXXXXX";    // + String(macAddress, HEX);
        _hostname.toUpperCase();

        getRFC952_hostname(_hostname.c_str());

      }
      else
      {
        // Prepare and store the hostname only not nullptr
        getRFC952_hostname(iHostname);
      }

      ETM_LOGWARN1(F("Hostname="), RFC952_hostname);
    }
    
    //////////////////////////////////////

    char* getRFC952_hostname(const char* iHostname)
    {
      memset(RFC952_hostname, 0, sizeof(RFC952_hostname));

      size_t len = ( RFC952_HOSTNAME_MAXLEN < strlen(iHostname) ) ? RFC952_HOSTNAME_MAXLEN : strlen(iHostname);

      size_t j = 0;

      for (size_t i = 0; i < len - 1; i++)
      {
        if ( isalnum(iHostname[i]) || iHostname[i] == '-' )
        {
          RFC952_hostname[j] = iHostname[i];
          j++;
        }
      }
      
      // no '-' as last char
      if ( isalnum(iHostname[len - 1]) || (iHostname[len - 1] != '-') )
        RFC952_hostname[j] = iHostname[len - 1];

      return RFC952_hostname;
    }

    //////////////////////////////////////

    void displayConfigData(Ethernet_Configuration configData)
    {
      ETM_LOGWARN3(F("Header="),       configData.header,
                 F(", BoardName="),    configData.board_name);
      ETM_LOGWARN1(F("StaticIP="),      configData.static_IP);

#if USE_DYNAMIC_PARAMETERS                 
      for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        ETM_LOGINFO3("i=", i, ",id=", myMenuItems[i].id);
        ETM_LOGINFO1("data=", myMenuItems[i].pdata);
      }   
#endif         
    }
    
    //////////////////////////////////////

#define ETHERNET_BOARD_TYPE   "ESP8266"
#define WM_NO_CONFIG          "blank"
    
    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(Ethernet_Manager_config) - sizeof(Ethernet_Manager_config.checkSum)); index++)
      {
        checkSum += * ( ( (uint8_t*) &Ethernet_Manager_config ) + index);
      }

      return checkSum;
    }

#if ( USE_LITTLEFS || USE_SPIFFS )

#define  CONFIG_FILENAME                  ("/etm_config.dat")
#define  CONFIG_FILENAME_BACKUP           ("/etm_config.bak")

#define  CREDENTIALS_FILENAME             ("/etm_cred.dat")
#define  CREDENTIALS_FILENAME_BACKUP      ("/etm_cred.bak")

#define  CONFIG_PORTAL_FILENAME           ("/etm_cp.dat")
#define  CONFIG_PORTAL_FILENAME_BACKUP    ("/etm_cp.bak")

    //////////////////////////////////////////////
    
    void saveForcedCP(uint32_t value)
    {
      File file = FileFS.open(CONFIG_PORTAL_FILENAME, "w");
      
      ETM_LOGINFO(F("SaveCPFile"));

      if (file)
      {
        file.write((uint8_t*) &value, sizeof(value));
        file.close();
        ETM_LOGINFO(F("OK"));
      }
      else
      {
        ETM_LOGINFO(F("failed"));
      }

      // Trying open redundant CP file
      file = FileFS.open(CONFIG_PORTAL_FILENAME_BACKUP, "w");
      
      ETM_LOGINFO(F("SaveBkUpCPFile"));

      if (file)
      {
        file.write((uint8_t *) &value, sizeof(value));
        file.close();
        ETM_LOGINFO(F("OK"));
      }
      else
      {
        ETM_LOGINFO(F("failed"));
      }
    }
    
    //////////////////////////////////////////////
    
    void setForcedCP(bool isPersistent)
    {
      uint32_t readForcedConfigPortalFlag = isPersistent? FORCED_PERS_CONFIG_PORTAL_FLAG_DATA : FORCED_CONFIG_PORTAL_FLAG_DATA;
  
      ETM_LOGDEBUG(isPersistent ? F("setForcedCP Persistent") : F("setForcedCP non-Persistent"));

      saveForcedCP(readForcedConfigPortalFlag);
    }
    
    //////////////////////////////////////////////
    
    void clearForcedCP()
    {
      uint32_t readForcedConfigPortalFlag = 0;
   
      ETM_LOGDEBUG(F("clearForcedCP"));
      
      saveForcedCP(readForcedConfigPortalFlag);
    }
    
    //////////////////////////////////////////////

    bool isForcedCP()
    {
      uint32_t readForcedConfigPortalFlag;
   
      ETM_LOGDEBUG(F("Check if isForcedCP"));
      
      File file = FileFS.open(CONFIG_PORTAL_FILENAME, "r");
      ETM_LOGINFO(F("LoadCPFile"));

      if (!file)
      {
        ETM_LOGINFO(F("failed"));

        // Trying open redundant config file
        file = FileFS.open(CONFIG_PORTAL_FILENAME_BACKUP, "r");
        ETM_LOGINFO(F("LoadBkUpCPFile"));

        if (!file)
        {
          ETM_LOGINFO(F("failed"));
          return false;
        }
       }

      file.readBytes((char *) &readForcedConfigPortalFlag, sizeof(readForcedConfigPortalFlag));

      ETM_LOGINFO(F("OK"));
      file.close();
      
      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false     
      if (readForcedConfigPortalFlag == FORCED_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = false;
        return true;
      }
      else if (readForcedConfigPortalFlag == FORCED_PERS_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = true;
        return true;
      }
      else
      {       
        return false;
      }
    }
    
    //////////////////////////////////////////////

#if USE_DYNAMIC_PARAMETERS

    bool checkDynamicData()
    {
      int checkSum = 0;
      int readCheckSum;
      char* readBuffer;
           
      File file = FileFS.open(CREDENTIALS_FILENAME, "r");
      ETM_LOGINFO(F("LoadCredFile"));

      if (!file)
      {
        ETM_LOGINFO(F("failed"));

        // Trying open redundant config file
        file = FileFS.open(CREDENTIALS_FILENAME_BACKUP, "r");
        ETM_LOGINFO(F("LoadBkUpCredFile"));

        if (!file)
        {
          ETM_LOGINFO(F("failed"));
          return false;
        }
      }
      
      // Find the longest pdata, then dynamically allocate buffer. Remember to free when done
      // This is used to store tempo data to calculate checksum to see of data is valid
      // We dont like to destroy myMenuItems[i].pdata with invalid data
      
      uint16_t maxBufferLength = 0;
      for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        if (myMenuItems[i].maxlen > maxBufferLength)
          maxBufferLength = myMenuItems[i].maxlen;
      }
      
      if (maxBufferLength > 0)
      {
        readBuffer = new char[ maxBufferLength + 1 ];
        
        // check to see nullptr => stop and return false
        if (readBuffer == nullptr)
        {
          ETM_LOGERROR(F("ChkCrR: Error can't allocate buffer."));
          return false;
        }      
        else
        {
          ETM_LOGDEBUG1(F("ChkCrR: Buffer allocated, sz="), maxBufferLength + 1);
        }          
     
        for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
        {       
          char* _pointer = readBuffer;

          // Actual size of pdata is [maxlen + 1]
          memset(readBuffer, 0, myMenuItems[i].maxlen + 1);
          
          file.readBytes(_pointer, myMenuItems[i].maxlen);
     
          ETM_LOGDEBUG3(F("ChkCrR:pdata="), readBuffer, F(",len="), myMenuItems[i].maxlen);      
                 
          for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
          {         
            checkSum += *_pointer;  
          }       
        }

        file.readBytes((char *) &readCheckSum, sizeof(readCheckSum));
        
        ETM_LOGINFO(F("OK"));
        file.close();
        
        ETM_LOGINFO3(F("CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
        
        // Free buffer
        delete [] readBuffer;
        ETM_LOGDEBUG(F("Buffer freed"));
        
        if ( checkSum != readCheckSum)
        {
          return true;
        }
      }  
      
      return false;    
    }
    
    //////////////////////////////////////////////

    bool loadDynamicData()
    {
      int checkSum = 0;
      int readCheckSum;
      totalDataSize = sizeof(Ethernet_Manager_config) + sizeof(readCheckSum);
      
      File file = FileFS.open(CREDENTIALS_FILENAME, "r");
      ETM_LOGINFO(F("LoadCredFile"));

      if (!file)
      {
        ETM_LOGINFO(F("failed"));

        // Trying open redundant config file
        file = FileFS.open(CREDENTIALS_FILENAME_BACKUP, "r");
        ETM_LOGINFO(F("LoadBkUpCredFile"));

        if (!file)
        {
          ETM_LOGINFO(F("failed"));
          return false;
        }
      }
     
      for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;

        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
        
        file.readBytes(_pointer, myMenuItems[i].maxlen);
 
        ETM_LOGDEBUG3(F("CrR:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);       
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;  
        }       
      }

      file.readBytes((char *) &readCheckSum, sizeof(readCheckSum));
      
      ETM_LOGINFO(F("OK"));
      file.close();
      
      ETM_LOGINFO3(F("CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }

    //////////////////////////////////////////////
    
    void saveDynamicData()
    {
      int checkSum = 0;
    
      File file = FileFS.open(CREDENTIALS_FILENAME, "w");
      ETM_LOGINFO(F("SaveCredFile"));

      for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
   
        ETM_LOGDEBUG3(F("CW1:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
        
        if (file)
        {
          file.write((uint8_t*) _pointer, myMenuItems[i].maxlen);         
        }
        else
        {
          ETM_LOGINFO(F("failed"));
        }        
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;     
         }
      }
      
      if (file)
      {
        file.write((uint8_t*) &checkSum, sizeof(checkSum));     
        file.close();
        ETM_LOGINFO(F("OK"));    
      }
      else
      {
        ETM_LOGINFO(F("failed"));
      }   
           
      ETM_LOGINFO1(F("CrWCSum=0x"), String(checkSum, HEX));
      
      // Trying open redundant Auth file
      file = FileFS.open(CREDENTIALS_FILENAME_BACKUP, "w");
      ETM_LOGINFO(F("SaveBkUpCredFile"));

      for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
  
        ETM_LOGDEBUG3(F("CW2:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
        
        if (file)
        {
          file.write((uint8_t*) _pointer, myMenuItems[i].maxlen);         
        }
        else
        {
          ETM_LOGINFO(F("failed"));
        }        
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;     
         }
      }
      
      if (file)
      {
        file.write((uint8_t*) &checkSum, sizeof(checkSum));     
        file.close();
        ETM_LOGINFO(F("OK"));    
      }
      else
      {
        ETM_LOGINFO(F("failed"));
      }   
    }
#endif

    //////////////////////////////////////////////
    
    void NULLTerminateConfig()
    {
      //#define HEADER_MAX_LEN      16
      //#define STATIC_IP_MAX_LEN   16
      //#define BOARD_NAME_MAX_LEN  24
      
      // NULL Terminating to be sure
      Ethernet_Manager_config.header    [HEADER_MAX_LEN - 1]      = 0;
      Ethernet_Manager_config.static_IP [STATIC_IP_MAX_LEN - 1]   = 0;
      Ethernet_Manager_config.board_name[BOARD_NAME_MAX_LEN - 1]  = 0;
    }

    //////////////////////////////////////////////    

    bool loadConfigData()
    {
      ETM_LOGINFO(F("LoadCfgFile"));
      
      // file existed
      File file = FileFS.open(CONFIG_FILENAME, "r");
         
      if (!file)
      {
        ETM_LOGINFO(F("failed"));

        // Trying open redundant config file
        file = FileFS.open(CONFIG_FILENAME_BACKUP, "r");
        
        ETM_LOGINFO(F("LoadBkUpCfgFile"));

        if (!file)
        {
          ETM_LOGINFO(F("failed"));
          return false;
        }
      }
     
      file.readBytes((char *) &Ethernet_Manager_config, sizeof(Ethernet_Manager_config));

      ETM_LOGINFO(F("OK"));
      file.close();
      
      NULLTerminateConfig();
      
      return true;
    }
    
    //////////////////////////////////////////////  

    void saveConfigData()
    {
      ETM_LOGINFO(F("SaveCfgFile"));

      int calChecksum = calcChecksum();
      Ethernet_Manager_config.checkSum = calChecksum;
      ETM_LOGINFO1(F("WCSum=0x"), String(calChecksum, HEX));
      
      File file = FileFS.open(CONFIG_FILENAME, "w");

      if (file)
      {
        file.write((uint8_t*) &Ethernet_Manager_config, sizeof(Ethernet_Manager_config));
        
        
        file.close();
        ETM_LOGINFO(F("OK"));
      }
      else
      {
        ETM_LOGINFO(F("failed"));
      }
      
      ETM_LOGINFO(F("SaveBkUpCfgFile"));
      
      // Trying open redundant Auth file
      file = FileFS.open(CONFIG_FILENAME_BACKUP, "w");

      if (file)
      {
        file.write((uint8_t *) &Ethernet_Manager_config, sizeof(Ethernet_Manager_config));
        
        file.close();
        ETM_LOGINFO(F("OK"));
      }
      else
      {
        ETM_LOGINFO(F("failed"));
      }
    }
    
    //////////////////////////////////////////////
    
    void saveAllConfigData()
    {
      saveConfigData();     
      
#if USE_DYNAMIC_PARAMETERS      
      saveDynamicData();
#endif      
    }
    
    //////////////////////////////////////////////
    
    void loadAndSaveDefaultConfigData()
    {
      // Load Default Config Data from Sketch
      memcpy(&Ethernet_Manager_config, &defaultConfig, sizeof(Ethernet_Manager_config));
      strcpy(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE);
      
      // Including config and dynamic data, and assume valid
      saveConfigData();
        
      ETM_LOGDEBUG(F("======= Start Loaded Config Data ======="));
      displayConfigData(Ethernet_Manager_config);    
    }
    
    //////////////////////////////////////////////

    // Return false if init new EEPROM or SPIFFS. No more need trying to connect. Go directly to config mode
    bool getConfigData()
    {
      bool dynamicDataValid = true; 
      int calChecksum; 
      
      hadConfigData = false;

      // Format SPIFFS if not yet
      if (!FileFS.begin())
      {
        FileFS.format();
     
        if (!FileFS.begin())
        {
#if USE_LITTLEFS
          ETM_LOGERROR(F("LittleFS failed!. Please use SPIFFS or EEPROM."));
#else
          ETM_LOGERROR(F("SPIFFS failed!. Please use LittleFS or EEPROM."));
#endif 
          return false;
        }
      }

      if (LOAD_DEFAULT_CONFIG_DATA)
      {
        // Load Config Data from Sketch
        memcpy(&Ethernet_Manager_config, &defaultConfig, sizeof(Ethernet_Manager_config));
        strcpy(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE);
        
        // Including config and dynamic data, and assume valid
        saveAllConfigData();
         
        ETM_LOGINFO(F("======= Start Loaded Config Data ======="));
        displayConfigData(Ethernet_Manager_config);

        // Don't need Config Portal anymore
        return true; 
      }
#if USE_DYNAMIC_PARAMETERS      
      else if ( ( FileFS.exists(CONFIG_FILENAME)      || FileFS.exists(CONFIG_FILENAME_BACKUP) ) &&
                ( FileFS.exists(CREDENTIALS_FILENAME) || FileFS.exists(CREDENTIALS_FILENAME_BACKUP) ) )
#else
      else if ( FileFS.exists(CONFIG_FILENAME) || FileFS.exists(CONFIG_FILENAME_BACKUP) )
#endif   
      {
        // if config file exists, load
        if (!loadConfigData())
        {
          return false;
        }
        
        ETM_LOGINFO(F("======= Start Stored Config Data ======="));
        displayConfigData(Ethernet_Manager_config);

        calChecksum = calcChecksum();

        ETM_LOGINFO3(F("CCSum=0x"), String(calChecksum, HEX),
                   F(",RCSum=0x"), String(Ethernet_Manager_config.checkSum, HEX));

#if USE_DYNAMIC_PARAMETERS                 
        // Load dynamic data
        dynamicDataValid = loadDynamicData();
        
        if (dynamicDataValid)
        { 
          ETM_LOGINFO(F("Valid Stored Dynamic Data"));    
        }
        else
        {
          ETM_LOGINFO(F("Invalid Stored Dynamic Data. Ignored"));
        }
#endif
      }
      else    
      {
        // Not loading Default config data, but having no config file => Config Portal
        return false;
      }    

      if ( (strncmp(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE, strlen(ETHERNET_BOARD_TYPE)) != 0) ||
           (calChecksum != Ethernet_Manager_config.checkSum) || !dynamicDataValid || 
           ( (calChecksum == 0) && (Ethernet_Manager_config.checkSum == 0) ) )   
                      
      {         
        // Including Credentials CSum
        ETM_LOGINFO1(F("InitCfgFile,sz="), sizeof(Ethernet_Manager_config));

        // doesn't have any configuration        
        if (LOAD_DEFAULT_CONFIG_DATA)
        {
          memcpy(&Ethernet_Manager_config, &defaultConfig, sizeof(Ethernet_Manager_config));
        }
        else
        {
          memset(&Ethernet_Manager_config, 0, sizeof(Ethernet_Manager_config));
          
          strcpy(Ethernet_Manager_config.static_IP,   WM_NO_CONFIG);
          strcpy(Ethernet_Manager_config.board_name,  WM_NO_CONFIG);
          
#if USE_DYNAMIC_PARAMETERS       
          for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
            strncpy(myMenuItems[i].pdata, WM_NO_CONFIG, myMenuItems[i].maxlen);
          }
#endif          
        }
    
        strcpy(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE);
        
#if USE_DYNAMIC_PARAMETERS
        for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          ETM_LOGDEBUG3(F("g:myMenuItems["), i, F("]="), myMenuItems[i].pdata );
        }
#endif
        
        // Don't need
        Ethernet_Manager_config.checkSum = 0;

        saveAllConfigData();
        
        return false;        
      }
      else
      {
        displayConfigData(Ethernet_Manager_config);
      }

      return true;
    }
    
    //////////////////////////////////////////////

#else     // USE_EEPROM

#ifndef EEPROM_SIZE
  #define EEPROM_SIZE     2048
#else
  #if (EEPROM_SIZE > 2048)
    #warning EEPROM_SIZE must be <= 2048. Reset to 2048
    #undef EEPROM_SIZE
    #define EEPROM_SIZE     2048
  #endif

  // FLAG_DATA_SIZE is 4, to store DRD flag
  #if (EEPROM_SIZE < FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
    #warning EEPROM_SIZE must be > CONFIG_DATA_SIZE. Reset to 512
    #undef EEPROM_SIZE
    #define EEPROM_SIZE     2048
  #endif
#endif

#ifndef EEPROM_START
  #define EEPROM_START     0      //define 256 in DRD
  #warning EEPROM_START not defined. Set to 0
#else
  #if (EEPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE > EEPROM_SIZE)
    #error EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE > EEPROM_SIZE. Please adjust.
  #endif
#endif

// Stating positon to store Blynk8266_WM_config
#define CONFIG_EEPROM_START    (EEPROM_START + FLAG_DATA_SIZE)

    //////////////////////////////////////////////
    
    void setForcedCP(bool isPersistent)
    {
      uint32_t readForcedConfigPortalFlag = isPersistent? FORCED_PERS_CONFIG_PORTAL_FLAG_DATA : FORCED_CONFIG_PORTAL_FLAG_DATA;
    
      ETM_LOGINFO(F("setForcedCP"));
      
      EEPROM.put(CONFIG_EEPROM_START + CONFIG_DATA_SIZE, readForcedConfigPortalFlag);
      EEPROM.commit();
    }
    //////////////////////////////////////////////
    
    void clearForcedCP()
    { 
      ETM_LOGINFO(F("clearForcedCP"));

      EEPROM.put(CONFIG_EEPROM_START + CONFIG_DATA_SIZE, 0);
      EEPROM.commit();
    }
    
    //////////////////////////////////////////////

    bool isForcedCP()
    {
      uint32_t readForcedConfigPortalFlag;

      ETM_LOGINFO(F("Check if isForcedCP"));

      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false
      EEPROM.get(CONFIG_EEPROM_START + CONFIG_DATA_SIZE, readForcedConfigPortalFlag);
      
      // Return true if forced CP (0xDEADBEEF read at offset EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
      // => set flag noForcedConfigPortal = false     
      if (readForcedConfigPortalFlag == FORCED_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = false;
        return true;
      }
      else if (readForcedConfigPortalFlag == FORCED_PERS_CONFIG_PORTAL_FLAG_DATA)
      {       
        persForcedConfigPortal = true;
        return true;
      }
      else
      {       
        return false;
      }
    }
    
    //////////////////////////////////////////////
    
#if USE_DYNAMIC_PARAMETERS
    
    bool checkDynamicData()
    {
      int checkSum = 0;
      int readCheckSum;
      
      #define BUFFER_LEN      128
      char readBuffer[BUFFER_LEN + 1];
      
      uint16_t offset = CONFIG_EEPROM_START + sizeof(Ethernet_Manager_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
                
      // Find the longest pdata, then dynamically allocate buffer. Remember to free when done
      // This is used to store tempo data to calculate checksum to see of data is valid
      // We dont like to destroy myMenuItems[i].pdata with invalid data
      
      for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        if (myMenuItems[i].maxlen > BUFFER_LEN)
        {
          // Size too large, abort and flag false
          ETM_LOGERROR(F("ChkCrR: Error Small Buffer."));
          return false;
        }
      }
         
      for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = readBuffer;
        
        // Prepare buffer, more than enough
        memset(readBuffer, 0, sizeof(readBuffer));
        
        // Read more than necessary, but OK and easier to code
        EEPROM.get(offset, readBuffer);
        // NULL terminated
        readBuffer[myMenuItems[i].maxlen] = 0;

        ETM_LOGDEBUG3(F("ChkCrR:pdata="), readBuffer, F(",len="), myMenuItems[i].maxlen);      
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;  
        }   
        
        offset += myMenuItems[i].maxlen;    
      }

      EEPROM.get(offset, readCheckSum);
           
      ETM_LOGINFO3(F("ChkCrR:CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
           
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }

    //////////////////////////////////////////////
    
    bool EEPROM_getDynamicData()
    {
      int readCheckSum;
      int checkSum = 0;
      uint16_t offset = CONFIG_EEPROM_START + sizeof(Ethernet_Manager_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
           
      totalDataSize = sizeof(Ethernet_Manager_config) + sizeof(readCheckSum);
      
      for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;
        
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++,offset++)
        {
          *_pointer = EEPROM.read(offset);
          
          checkSum += *_pointer;  
        }
         
        ETM_LOGDEBUG3(F("CR:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);         
      }
      
      EEPROM.get(offset, readCheckSum);
      
      ETM_LOGINFO3(F("CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;
    }
    
    //////////////////////////////////////////////

    void EEPROM_putDynamicData()
    {
      int checkSum = 0;
      uint16_t offset = CONFIG_EEPROM_START + sizeof(Ethernet_Manager_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
                
      for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
           
        ETM_LOGDEBUG3(F("CW:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
                            
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++,offset++)
        {
          EEPROM.write(offset, *_pointer);
          
          checkSum += *_pointer;     
         }
      }
      
      EEPROM.put(offset, checkSum);
      //EEPROM.commit();
      
      ETM_LOGINFO1(F("CrWCSum=0x"), String(checkSum, HEX));
    }
#endif

    //////////////////////////////////////////////

    void saveConfigData()
    {
      int calChecksum = calcChecksum();
      Ethernet_Manager_config.checkSum = calChecksum;
      ETM_LOGINFO3(F("SaveEEPROM,sz="), EEPROM_SIZE, F(",CSum=0x"), String(calChecksum, HEX))

      EEPROM.put(CONFIG_EEPROM_START, Ethernet_Manager_config);
      
      EEPROM.commit();
    }
    
    //////////////////////////////////////////////
    
    void saveAllConfigData()
    {
      int calChecksum = calcChecksum();
      Ethernet_Manager_config.checkSum = calChecksum;
      ETM_LOGINFO3(F("SaveEEPROM,sz="), EEPROM_SIZE, F(",CSum=0x"), String(calChecksum, HEX))

      EEPROM.put(CONFIG_EEPROM_START, Ethernet_Manager_config);
      
#if USE_DYNAMIC_PARAMETERS         
      EEPROM_putDynamicData();
#endif
      
      EEPROM.commit();
    }

    //////////////////////////////////////////////
    
    void loadAndSaveDefaultConfigData()
    {
      // Load Default Config Data from Sketch
      memcpy(&Ethernet_Manager_config, &defaultConfig, sizeof(Ethernet_Manager_config));
      strcpy(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE);
      
      // Including config and dynamic data, and assume valid
      saveConfigData();
       
      ETM_LOGINFO(F("======= Start Loaded Config Data ======="));
      displayConfigData(Ethernet_Manager_config);  
    }
        
    //////////////////////////////////////////////
    
    bool getConfigData()
    {
      bool dynamicDataValid = true;
      int calChecksum;
      
      hadConfigData = false; 
      
      EEPROM.begin(EEPROM_SIZE);
      ETM_LOGINFO1(F("EEPROMsz:"), EEPROM_SIZE);
      
      if (LOAD_DEFAULT_CONFIG_DATA)
      {
        // Load Config Data from Sketch
        memcpy(&Ethernet_Manager_config, &defaultConfig, sizeof(Ethernet_Manager_config));
        strcpy(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE);
        
        // Including config and dynamic data, and assume valid
        saveAllConfigData();
                    
        ETM_LOGINFO(F("======= Start Loaded Config Data ======="));
        displayConfigData(Ethernet_Manager_config);

        // Don't need Config Portal anymore
        return true;             
      }
      else
      {
        // Load data from EEPROM
        EEPROM.get(CONFIG_EEPROM_START, Ethernet_Manager_config);
          
        ETM_LOGINFO(F("======= Start Stored Config Data ======="));
        displayConfigData(Ethernet_Manager_config);

        calChecksum = calcChecksum();

        ETM_LOGINFO3(F("CCSum=0x"), String(calChecksum, HEX),
                   F(",RCSum=0x"), String(Ethernet_Manager_config.checkSum, HEX));

#if USE_DYNAMIC_PARAMETERS
                 
        // Load dynamic data from EEPROM
        dynamicDataValid = EEPROM_getDynamicData();
        
        if (dynamicDataValid)
        {  
          ETM_LOGINFO(F("Valid Stored Dynamic Data"));       
        }
        else
        {
          ETM_LOGINFO(F("Invalid Stored Dynamic Data. Ignored"));
        }
#endif
      }
        
      if ( (strncmp(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE, strlen(ETHERNET_BOARD_TYPE)) != 0) ||
           (calChecksum != Ethernet_Manager_config.checkSum) || !dynamicDataValid || 
           ( (calChecksum == 0) && (Ethernet_Manager_config.checkSum == 0) ) )   
      {       
        // Including Credentials CSum
        ETM_LOGINFO3(F("InitEEPROM,sz="), EEPROM_SIZE, F(",DataSz="), totalDataSize);

        // doesn't have any configuration        
        if (LOAD_DEFAULT_CONFIG_DATA)
        {
          memcpy(&Ethernet_Manager_config, &defaultConfig, sizeof(Ethernet_Manager_config));
        }
        else
        {
          memset(&Ethernet_Manager_config, 0, sizeof(Ethernet_Manager_config));
             
          //strcpy(Ethernet_Manager_config.static_IP,   WM_NO_CONFIG);
          strcpy(Ethernet_Manager_config.board_name,  ETHERNET_BOARD_TYPE);
          
#if USE_DYNAMIC_PARAMETERS       
          for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
            strncpy(myMenuItems[i].pdata, WM_NO_CONFIG, myMenuItems[i].maxlen);
          }
#endif          
        }
    
        strcpy(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE);
        
#if USE_DYNAMIC_PARAMETERS
        for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          ETM_LOGDEBUG3(F("g:myMenuItems["), i, F("]="), myMenuItems[i].pdata );
        }
#endif
        
        // Don't need
        Ethernet_Manager_config.checkSum = 0;

        saveAllConfigData();
        
        return false;        
      }
      else
      {
        displayConfigData(Ethernet_Manager_config);
      }

      return true;
    }
    
#endif    // ( USE_LITTLEFS || USE_SPIFFS )

    //////////////////////////////////////////////

    // NEW
    void createHTML(String& root_html_template)
    {
      String pitem;
      
      root_html_template  = ETM_HTML_HEAD_START;
      
  #if USING_CUSTOMS_STYLE
      // Using Customs style when not NULL
      if (ETM_HTML_HEAD_CUSTOMS_STYLE)
        root_html_template  += ETM_HTML_HEAD_CUSTOMS_STYLE;
      else
        root_html_template  += ETM_HTML_HEAD_STYLE;
  #else     
      root_html_template  += ETM_HTML_HEAD_STYLE;
  #endif
      
  #if USING_CUSTOMS_HEAD_ELEMENT
      if (_CustomsHeadElement)
        root_html_template += _CustomsHeadElement;
  #endif          
      
      root_html_template += String(ETM_HTML_HEAD_END) + ETM_FLDSET_START;

#if USE_DYNAMIC_PARAMETERS      
      for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        pitem = String(ETM_HTML_PARAM);

        pitem.replace("{b}", myMenuItems[i].displayName);
        pitem.replace("{v}", myMenuItems[i].id);
        pitem.replace("{i}", myMenuItems[i].id);
        
        root_html_template += pitem;
      }
#endif
      
      root_html_template += String(ETM_FLDSET_END) + ETM_HTML_BUTTON + ETM_HTML_SCRIPT;     

#if USE_DYNAMIC_PARAMETERS      
      for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        pitem = String(ETM_HTML_SCRIPT_ITEM);
        
        pitem.replace("{d}", myMenuItems[i].id);
        
        root_html_template += pitem;
      }
#endif
      
      root_html_template += String(ETM_HTML_SCRIPT_END) + ETM_HTML_END;
      
      return;     
    }
       
    //////////////////////////////////////////////

    void serverSendHeaders()
    {
      ETM_LOGDEBUG3(F("serverSendHeaders:WM_HTTP_CACHE_CONTROL:"), WM_HTTP_CACHE_CONTROL, "=", WM_HTTP_NO_STORE);
      server->sendHeader(WM_HTTP_CACHE_CONTROL, WM_HTTP_NO_STORE);
      
#if USING_CORS_FEATURE
      // New from v1.2.0, for configure CORS Header, default to WM_HTTP_CORS_ALLOW_ALL = "*"
      ETM_LOGDEBUG3(F("serverSendHeaders:WM_HTTP_CORS:"), WM_HTTP_CORS, " : ", _CORS_Header);
      server->sendHeader(WM_HTTP_CORS, _CORS_Header);
#endif
     
      ETM_LOGDEBUG3(F("serverSendHeaders:WM_HTTP_PRAGMA:"), WM_HTTP_PRAGMA, " : ", WM_HTTP_NO_CACHE);
      server->sendHeader(WM_HTTP_PRAGMA, WM_HTTP_NO_CACHE);
      
      ETM_LOGDEBUG3(F("serverSendHeaders:WM_HTTP_EXPIRES:"), WM_HTTP_EXPIRES, " : ", "-1");
      server->sendHeader(WM_HTTP_EXPIRES, "-1");
    }
       
    //////////////////////////////////////////////
    
    void handleRequest()
    {
      if (server)
      {
        String key = server->arg("key");
        String value = server->arg("value");

        static int number_items_Updated = 0;

        if (key == "" && value == "")
        {
          // New from v1.2.0         
          serverSendHeaders();        
          //////
          
          String result;
          createHTML(result);

          ETM_LOGDEBUG1(F("h:Repl:"), result);

          // Reset configTimeout to stay here until finished.
          configTimeout = 0;
          
          if ( RFC952_hostname[0] != 0 )
          {
            // Replace only if Hostname is valid
            result.replace("Ethernet_ESP32_Manager", RFC952_hostname);
          }
          else if ( Ethernet_Manager_config.board_name[0] != 0 )
          {
            // Or replace only if board_name is valid.  Otherwise, keep intact
            result.replace("Ethernet_ESP32_Manager", Ethernet_Manager_config.board_name);
          }

          if (hadConfigData)
          {
            result.replace("[[ip]]", Ethernet_Manager_config.static_IP);
            result.replace("[[nm]]", Ethernet_Manager_config.board_name);
          }
          else
          {
            result.replace("[[ip]]", "0");
            result.replace("[[nm]]", ETHERNET_BOARD_TYPE);
          }

#if USE_DYNAMIC_PARAMETERS
          for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            String toChange = String("[[") + myMenuItems[i].id + "]]";
            result.replace(toChange, myMenuItems[i].pdata);
              
            ETM_LOGDEBUG3(F("h1:myMenuItems["), i, F("]="), myMenuItems[i].pdata );
          }
#endif

          ETM_LOGDEBUG1(F("h:HTML page size:"), result.length());
          ETM_LOGDEBUG1(F("h:HTML="), result);
          
          server->send(200, WM_HTTP_HEAD_TEXT_HTML, result);
          
          return;
        }
        
        if (number_items_Updated == 0)
        {
          memset(&Ethernet_Manager_config, 0, sizeof(Ethernet_Manager_config));
          strcpy(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE);
        }

#if USE_DYNAMIC_PARAMETERS
        if (!menuItemUpdated)
        {
          // Don't need to free
          menuItemUpdated = new bool[NUM_MENU_ITEMS];
          
          if (menuItemUpdated)
          {
            for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
            {           
              // To flag item is not yet updated
              menuItemUpdated[i] = false;           
            }
            
            ETM_LOGDEBUG(F("h: Init menuItemUpdated" ));                    
          }
          else
          {
            ETM_LOGERROR(F("h: Error can't alloc memory for menuItemUpdated" ));
          }
        }  
#endif

        static bool ip_Updated  = false;
        static bool nm_Updated  = false;
        
        if (!ip_Updated && (key == String("ip")))
        {   
          ETM_LOGDEBUG(F("h:repl ip"));
          ip_Updated = true;
          
          number_items_Updated++;
          
          if (strlen(value.c_str()) < sizeof(Ethernet_Manager_config.static_IP) - 1)
            strcpy(Ethernet_Manager_config.static_IP, value.c_str());
          else
            strncpy(Ethernet_Manager_config.static_IP, value.c_str(), sizeof(Ethernet_Manager_config.static_IP) - 1);
        }
        else if (!nm_Updated && (key == String("nm")))
        {
          ETM_LOGDEBUG(F("h:repl nm"));
          nm_Updated = true;
          
          number_items_Updated++;
          
          if (strlen(value.c_str()) < sizeof(Ethernet_Manager_config.board_name) - 1)
            strcpy(Ethernet_Manager_config.board_name, value.c_str());
          else
            strncpy(Ethernet_Manager_config.board_name, value.c_str(), sizeof(Ethernet_Manager_config.board_name) - 1);
        }
        
#if USE_DYNAMIC_PARAMETERS   
        else
        {     
          for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            if ( !menuItemUpdated[i] && (key == myMenuItems[i].id) )
            {
              ETM_LOGDEBUG3(F("h:"), myMenuItems[i].id, F("="), value.c_str() );
              
              menuItemUpdated[i] = true;
              
              number_items_Updated++;

              // Actual size of pdata is [maxlen + 1]
              memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);

              if ((int) strlen(value.c_str()) < myMenuItems[i].maxlen)
                strcpy(myMenuItems[i].pdata, value.c_str());
              else
                strncpy(myMenuItems[i].pdata, value.c_str(), myMenuItems[i].maxlen);
                
             break;   
            }
          }
        }
#endif
        
        ETM_LOGDEBUG1(F("h:items updated ="), number_items_Updated);
        ETM_LOGDEBUG3(F("h:key ="), key, ", value =", value);

        server->send(200, WM_HTTP_HEAD_TEXT_HTML, "OK");

#if USE_DYNAMIC_PARAMETERS        
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS + NUM_MENU_ITEMS)
#else
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS)
#endif 
        {
#if USE_LITTLEFS
          ETM_LOGERROR1(F("h:Updating LittleFS:"), CONFIG_FILENAME);        
#elif USE_SPIFFS
          ETM_LOGERROR1(F("h:Updating SPIFFS:"), CONFIG_FILENAME);
#else
          ETM_LOGERROR(F("h:Updating EEPROM. Please wait for reset"));
#endif

          saveAllConfigData();
          
          // Done with CP, Clear CP Flag here if forced
          if (isForcedConfigPortal)
            clearForcedCP();

          ETM_LOGWARN(F("h:Rst"));

          // Delay then reset after save data
          delay(1000);
          resetFunc();
        }
      }     // if (server)
    }

    //////////////////////////////////////////////

#ifndef CONFIG_TIMEOUT
  #warning Default CONFIG_TIMEOUT = 60s
  #define CONFIG_TIMEOUT			60000L
#endif

    void startConfigurationMode()
    {
      // turn the LED_BUILTIN ON to tell us we are in configuration mode.
      digitalWrite(LED_BUILTIN, LED_ON);

      ETM_LOGWARN1(F("CfgIP="), Ethernet.localIP() );

      if (!server)
        server = new EthernetWebServer;

      //See https://stackoverflow.com/questions/39803135/c-unresolved-overloaded-function-type?rq=1

      if (server)
      {
        server->on("/", [this]() { handleRequest(); } );
        server->begin();
      }

      // If there is no saved config Data, stay in config mode forever until having config Data.
      // or SSID, PW, Server,Token ="nothing"
      if (hadConfigData)
      {
        configTimeout = millis() + CONFIG_TIMEOUT;
                       
        ETM_LOGDEBUG3(F("s:millis() ="), millis(), F(", configTimeout ="), configTimeout);
      }
      else
      {
        configTimeout = 0;             
        ETM_LOGDEBUG(F("s:configTimeout = 0"));   
      }  

      configuration_mode = true;
    }

    //////////////////////////////////////////////

    bool connectEthernet()
    {
      // Check go see if static IP is required
      IPAddress staticIP;
      
      if (staticIP.fromString(Ethernet_Manager_config.static_IP))
      {
        // Use static IP
        ETM_LOGWARN1(F("Start connectEthernet using Static IP ="), staticIP);
        
        // If macAddress valid, use it
        if (isMacAddressValid(macAddress))
          Ethernet.begin(SelectMacAddress(macAddress), staticIP);
        else
          Ethernet.begin(SelectMacAddress(nullptr), staticIP);
        
        ethernetConnected = true;
      }
      else
      {
        // If static_IP ="nothing" or nullptr, use DHCP dynamic IP
        ETM_LOGWARN(F("Start connectEthernet using DHCP"));
        
        // If macAddress valid, use it
        if (isMacAddressValid(macAddress))
          ethernetConnected = ( Ethernet.begin(SelectMacAddress(macAddress)) == 1);
        else  
          ethernetConnected = ( Ethernet.begin(SelectMacAddress(nullptr)) == 1);
      }
    
      // give the Ethernet shield a second to initialize:
      //delay(1000);
     
      if (ethernetConnected)
      {
        ETM_LOGWARN1(F("IP:"), Ethernet.localIP());
      }
      else
      {
        ETM_LOGWARN(F("DHCPFailed"));     
      }

      return ethernetConnected;
    }
    
    ///////////////////////////////////////////////////////////////////

    uint8_t* SelectMacAddress(const uint8_t* mac)
    {
      char localBuffer[24];
      
      if (isMacAddressValid(mac))
      {
        return (uint8_t*)mac;
      }

#if USE_ETHERNET_GENERIC  
      Ethernet.MACAddress(macAddress);
#endif
      
      printMacAddress();

      if (isMacAddressValid(macAddress))
      {
      	return macAddress;
      }
      
      // Initial mac to manipulate from
      macAddress[0] = 0xFE;
      macAddress[1] = 0xED;
      macAddress[2] = 0xDE;
      macAddress[3] = 0xAD;
      macAddress[4] = 0xBE;
      macAddress[5] = 0xEF;
      
#define TOKEN_LEN				8

      char token[TOKEN_LEN];
      uint32_t curTime = millis();
      snprintf(token, sizeof(token), "%d", curTime * curTime);
     
      int mac_index = 1;
      
      ETM_LOGDEBUG3("token =", token, ", len =", TOKEN_LEN);
      
      for (uint16_t i = 0; i < TOKEN_LEN; i++)
      {
        macAddress[mac_index] ^= token[i];

        if (++mac_index > 5) 
        {
          mac_index = 1;
        }
      }
           
      snprintf(localBuffer, sizeof(localBuffer), "MAC:%02X-%02X-%02X-%02X-%02X-%02X",
                macAddress[0], macAddress[1],
                macAddress[2], macAddress[3],
                macAddress[4], macAddress[5]);
                
      ETM_LOGWARN1(F("Calculated =>"), localBuffer);

#if USE_ETHERNET_GENERIC      
      // Set for later use
      Ethernet.setMACAddress(macAddress);
#endif

      return macAddress;
    }
};

#endif    // Ethernet_ESP8266_Manager_h
