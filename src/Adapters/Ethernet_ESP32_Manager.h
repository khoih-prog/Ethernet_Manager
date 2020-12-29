/****************************************************************************************************************************
  Ethernet_ESP32_Manager.h
  For W5x00 and ENC28J60 Ethernet shields.

  Ethernet_Manager is a library for nRF52, Teensy, STM32, SAM DUE and SAMD boards, with Ethernet W5x00 or ENC28J60 shields,
  to enable easy configuration/reconfiguration of Credentials and autoconnect/autoreconnect of Ethernet.
  AVR Mega is not supported.

  Built by Khoi Hoang https://github.com/khoih-prog/Ethernet_Manager
  Licensed under MIT license
  Version: 1.1.1

  Version  Modified By   Date      Comments
  -------  -----------  ---------- -----------
  1.0.0     K Hoang     14/12/2020 Initial coding.
  1.1.0     K Hoang     17/12/2020 Add support to ESP32/ESP8266. Add MQTT related examples to demo dynamic parameter usage
  1.1.1     K Hoang     28/12/2020 Suppress all possible compiler warnings
*****************************************************************************************************************************/

#pragma once

#ifndef Ethernet_ESP32_Manager_h
#define Ethernet_ESP32_Manager_h

#if defined(ESP32)
  #if defined(ETHERNET_USE_ESP32)
    #undef ETHERNET_USE_ESP32
  #endif
  #warning ETHERNET_USE_ESP32 from Ethernet_ESP32_Manager.h
  #define ETHERNET_USE_ESP32      true
#else
  #error This code is designed to run on ESP32 platform! Please check your Tools->Board setting.
#endif

// Increase HTTP_UPLOAD_BUFLEN to 4K, instead of default 2K in <EthernetWebServer.h>
#define HTTP_UPLOAD_BUFLEN    4096

#if USE_LITTLEFS
  // Use LittleFS
  #include "FS.h"

  // The library will be depreciated after being merged to future major Arduino esp32 core release 2.x
  // At that time, just remove this library inclusion
  #include <LITTLEFS.h>             // https://github.com/lorol/LITTLEFS
  
  FS* filesystem =      &LITTLEFS;
  #define FileFS        LITTLEFS
#elif USE_SPIFFS
  #include "FS.h"
  #include <SPIFFS.h>
  FS* filesystem =      &SPIFFS;
  #define FileFS        SPIFFS
#else
  #include <EEPROM.h>
#endif

///////// NEW for DRD /////////////
// These defines must be put before #include <ESP_DoubleResetDetector.h>
// to select where to store DoubleResetDetector's variable.
// For ESP32, You must select one to be true (EEPROM or SPIFFS)
// For ESP8266, You must select one to be true (RTC, EEPROM or SPIFFS)
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

#include <esp_wifi.h>
#define ESP_getChipId()   ((uint32_t)ESP.getEfuseMac())


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

///NEW
extern uint16_t NUM_MENU_ITEMS;
extern MenuItem myMenuItems [];

// Configurable items besides fixed Header
#define NUM_CONFIGURABLE_ITEMS    ( 2 )

typedef struct Configuration
{
  char header         [16];
  char static_IP      [16];
  char board_name     [24];
  int  checkSum;
} Ethernet_Configuration;

// Currently CONFIG_DATA_SIZE  =  ( 64 )
uint16_t CONFIG_DATA_SIZE = sizeof(Ethernet_Configuration);

///New from v1.0.13
extern bool LOAD_DEFAULT_CONFIG_DATA;
extern Ethernet_Configuration defaultConfig;

const char ETM_HTML_HEAD[]     /*PROGMEM*/ = "<!DOCTYPE html><html><head><title>Ethernet_ESP32_Manager</title><style>div,input{padding:2px;font-size:1em;}input{width:95%;}\
body{text-align: center;}button{background-color:#16A1E7;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.5rem;margin:0px;}\
</style></head><div style='text-align:left;display:inline-block;min-width:260px;'>\
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
///


class Ethernet_Manager
{

  public:
  
#ifndef LED_BUILTIN
#define LED_BUILTIN       13
#endif

// For ESP32
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
      ETM_LOGWARN(F("======= Start Default Config Data ======="));
      displayConfigData(defaultConfig);

      hadConfigData = getConfigData();

      connectEthernet();

      //// New DRD ////
      //  noConfigPortal when getConfigData() OK and no DRD'ed
      if (hadConfigData && noConfigPortal)     
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
          // failed to connect to Blynk server, will start configuration mode
          //startConfigurationMode();
        }
      }
      else
      {
        ETM_LOGWARN1(F("begin:Stay in CfgPortal:"), noConfigPortal ? F("No CfgDat") : F("DRD"));
        
        // failed to connect to Blynk server, will start configuration mode
        hadConfigData = false;
        startConfigurationMode();
      }
    }

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

    String getBoardName()
    {
      return (String(Ethernet_Manager_config.board_name));
    }

    Ethernet_Configuration* getFullConfigData(Ethernet_Configuration *configData)
    {
      if (!hadConfigData)
        getConfigData();

      // Check if NULL pointer
      if (configData)
        memcpy(configData, &Ethernet_Manager_config, sizeof(Ethernet_Manager_config));

      return (configData);
    }
    
    void clearConfigData()
    {
      memset(&Ethernet_Manager_config, 0, sizeof(Ethernet_Manager_config));
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
      }
      
      saveConfigData();
    }
    
    void resetFunc()
    {
      delay(1000);
      ESP.restart();
    }

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

    Ethernet_Configuration Ethernet_Manager_config;
    
    uint16_t totalDataSize = 0;
    
    uint8_t currentBlynkServerIndex = 255;

#define RFC952_HOSTNAME_MAXLEN      24
    char RFC952_hostname[RFC952_HOSTNAME_MAXLEN + 1];

    void setRFC952_hostname(const char* iHostname = "")
    {
      if (iHostname[0] == 0)
      {
        String _hostname = "ESP32-XXXXXX";    // + String(macAddress, HEX);
        _hostname.toUpperCase();

        getRFC952_hostname(_hostname.c_str());

      }
      else
      {
        // Prepare and store the hostname only not NULL
        getRFC952_hostname(iHostname);
      }

      ETM_LOGWARN1(F("Hostname="), RFC952_hostname);
    }

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

    void displayConfigData(Ethernet_Configuration configData)
    {
      ETM_LOGWARN3(F("Header="),       configData.header,
                 F(", BoardName="),    configData.board_name);
      ETM_LOGWARN1(F("StaticIP="),      configData.static_IP);
                 
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {
        ETM_LOGINFO3("i=", i, ",id=", myMenuItems[i].id);
        ETM_LOGINFO1("data=", myMenuItems[i].pdata);
      }      
    }

#define ETHERNET_BOARD_TYPE   "ESP32"
#define WM_NO_CONFIG          "blank"
    
    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(Ethernet_Manager_config) - sizeof(Ethernet_Manager_config.checkSum)); index++)
      {
        checkSum += * ( ( (byte*) &Ethernet_Manager_config ) + index);
      }

      return checkSum;
    }

#if ( USE_LITTLEFS || USE_SPIFFS )

#define  CONFIG_FILENAME              "/etm_config.dat"
#define  CONFIG_FILENAME_BACKUP       "/etm_config.bak"

#define  CREDENTIALS_FILENAME         "/etm_cred.dat"
#define  CREDENTIALS_FILENAME_BACKUP  "/etm_cred.bak"
    
    bool checkDynamicData()
    {
      int checkSum = 0;
      int readCheckSum;
      char* readBuffer;
           
      File file = FileFS.open(CREDENTIALS_FILENAME, "r");
      ETM_LOGINFO(F("LoadCredFile "));

      if (!file)
      {
        ETM_LOGINFO(F("failed"));

        // Trying open redundant config file
        file = FileFS.open(CREDENTIALS_FILENAME_BACKUP, "r");
        
        ETM_LOGINFO(F("LoadBkUpCredFile "));

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
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        if (myMenuItems[i].maxlen > maxBufferLength)
          maxBufferLength = myMenuItems[i].maxlen;
      }
      
      if (maxBufferLength > 0)
      {
        readBuffer = new char[ maxBufferLength + 1 ];
        
        // check to see NULL => stop and return false
        if (readBuffer == NULL)
        {
          ETM_LOGINFO(F("ChkCrR: Error can't allocate buffer."));
          return false;
        }     
        else
        {
          ETM_LOGINFO1(F("ChkCrR: Buffer allocated, Sz="), maxBufferLength + 1);
        }          
      }
      else
      {
        ETM_LOGINFO(F("ChkCrR: Error maxBufferLength == 0."));
        return false;
      }   
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = readBuffer;

        // Actual size of pdata is [maxlen + 1]
        memset(readBuffer, 0, myMenuItems[i].maxlen + 1);
        
        file.readBytes(_pointer, myMenuItems[i].maxlen);
  
        ETM_LOGINFO3(F("ChkCrR:pdata="), readBuffer, F(",len="), myMenuItems[i].maxlen);
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;  
        }       
      }

      file.readBytes((char *) &readCheckSum, sizeof(readCheckSum));
      
      ETM_LOGINFO(F("OK"));
      file.close();
      
      ETM_LOGINFO3(F("CrCCSum=0x"), String(checkSum, HEX), F(",CrRCSum=0x"), String(readCheckSum, HEX));
      
      // Free buffer
      if (readBuffer != NULL)
      {
        free(readBuffer);
        ETM_LOGINFO(F("Buffer freed"));
      }
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }

    bool loadDynamicData()
    {
      int checkSum = 0;
      int readCheckSum;
      totalDataSize = sizeof(Ethernet_Configuration) + sizeof(readCheckSum);
      
      File file = FileFS.open(CREDENTIALS_FILENAME, "r");
      
      ETM_LOGINFO(F("LoadCredFile "));

      if (!file)
      {
        ETM_LOGINFO(F("failed"));

        // Trying open redundant config file
        file = FileFS.open(CREDENTIALS_FILENAME_BACKUP, "r");
        
        ETM_LOGINFO(F("LoadBkUpCredFile "));

        if (!file)
        {
          ETM_LOGINFO(F("failed"));
          return false;
        }
      }
     
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
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
      
      ETM_LOGINFO3(F("CrCCSum=0x"), String(checkSum, HEX), F(",CrRCSum=0x"), String(readCheckSum, HEX));
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }

    void saveDynamicData()
    {
      int checkSum = 0;
    
      File file = FileFS.open(CREDENTIALS_FILENAME, "w");
      
      ETM_LOGINFO(F("SaveCredFile "));
     
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
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
           
      ETM_LOGINFO1(F("CrWCSum="), String(checkSum, HEX));
      
      // Trying open redundant Auth file
      file = FileFS.open(CREDENTIALS_FILENAME_BACKUP, "w");
      
      ETM_LOGINFO(F("SaveBkUpCredFile "));
     
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
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

    void loadConfigData()
    {
      ETM_LOGINFO(F("LoadCfgFile "));
      
      // file existed
      File file = FileFS.open(CONFIG_FILENAME, "r");
         
      if (!file)
      {
        ETM_LOGINFO(F("failed"));

        // Trying open redundant config file
        file = FileFS.open(CONFIG_FILENAME_BACKUP, "r");
        
        ETM_LOGINFO(F("LoadBkUpCfgFile "));

        if (!file)
        {
          ETM_LOGINFO(F("failed"));
          return;
        }
      }
     
      file.readBytes((char *) &Ethernet_Manager_config, sizeof(Ethernet_Manager_config));

      ETM_LOGINFO(F("OK"));
      file.close();
    }

    void saveConfigData()
    {
      ETM_LOGINFO(F("SaveCfgFile "));

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
      
      ETM_LOGINFO(F("SaveBkUpCfgFile "));
      
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
      
      saveDynamicData();
    }
    
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

    // Return false if init new EEPROM or SPIFFS. No more need trying to connect. Go directly to config mode
    bool getConfigData()
    {
      bool dynamicDataValid;
      int calChecksum;   
      
      hadConfigData = false;
      
      // Format SPIFFS if not yet
      if (!FileFS.begin(true))
      {
        ETM_LOGERROR(F("SPIFFS failed! Formatting."));
        
        if (!FileFS.begin())
        {
          ETM_LOGERROR(F("SPIFFS failed! Pls use EEPROM."));
          return false;
        }
      }

      // Use new LOAD_DEFAULT_CONFIG_DATA logic
      if (LOAD_DEFAULT_CONFIG_DATA)
      {     
        // Load Config Data from Sketch
        loadAndSaveDefaultConfigData();
        
        // Don't need Config Portal anymore
        return true; 
      }
      else if ( ( FileFS.exists(CONFIG_FILENAME)      || FileFS.exists(CONFIG_FILENAME_BACKUP) ) &&
                ( FileFS.exists(CREDENTIALS_FILENAME) || FileFS.exists(CREDENTIALS_FILENAME_BACKUP) ) )
      {   
        // Load stored config data from LittleFS
        loadConfigData();
        
        // Load stored default data from LittleFS
        dynamicDataValid = checkDynamicData();
        
        // Verify ChkSum        
        calChecksum = calcChecksum();

        ETM_LOGWARN3(F("CCSum=0x"), String(calChecksum, HEX),
                   F(",RCSum=0x"), String(Ethernet_Manager_config.checkSum, HEX));
                   
        if (dynamicDataValid)
        {
          loadDynamicData();
          
          ETM_LOGDEBUG(F("Valid Stored Dynamic Data"));
          ETM_LOGWARN(F("======= Start Stored Config Data ======="));
          
          displayConfigData(Ethernet_Manager_config);
          
          // Don't need Config Portal anymore
          return true;
        }
        else
        {
          // Invalid Stored config data => Config Portal
          ETM_LOGWARN(F("Invalid Stored Dynamic Data. Load default from Sketch"));
          
          // Load Default Config Data from Sketch, better than just "blank"
          loadAndSaveDefaultConfigData();
                           
          // Need Config Portal here as data can be just dummy
          // Even if you don't open CP, you're OK on next boot if your default config data is valid 
          return false;
        }      
      }
      else    
      {
        // Not loading Default config data, but having no config file => Config Portal
        return false;
      }    

      if ( (strncmp(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE, strlen(ETHERNET_BOARD_TYPE)) != 0) ||
           (calChecksum != Ethernet_Manager_config.checkSum) || !dynamicDataValid )
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

          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
          }
              
          strcpy(Ethernet_Manager_config.static_IP,   WM_NO_CONFIG);
          strcpy(Ethernet_Manager_config.board_name,  WM_NO_CONFIG);
          
          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            strncpy(myMenuItems[i].pdata, WM_NO_CONFIG, myMenuItems[i].maxlen);
          }
        }
    
        strcpy(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE);
        
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          ETM_LOGDEBUG3(F("g:myMenuItems["), i, F("]="), myMenuItems[i].pdata );
        }
        
        // Don't need
        Ethernet_Manager_config.checkSum = 0;

        saveConfigData();
        
        return false;
      }
      else
      {
        displayConfigData(Ethernet_Manager_config);
      }

      return true;
    }

#else     // USE_EEPROM

#ifndef EEPROM_SIZE
  #define EEPROM_SIZE     1024
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
  #if (EEPROM_START + FLAG_DATA_SIZE + CONFIG_DATA_SIZE > EEPROM_SIZE)
    #error EPROM_START + FLAG_DATA_SIZE + CONFIG_DATA_SIZE > EEPROM_SIZE. Please adjust.
  #endif
#endif

// Stating positon to store Blynk8266_WM_config
#define ETHERNET_MANAGER_EEPROM_START    (EEPROM_START + FLAG_DATA_SIZE)

    bool checkDynamicData(void)
    {
      int checkSum = 0;
      int readCheckSum;
      
      #define BUFFER_LEN      128
      char readBuffer[BUFFER_LEN + 1];
      
      uint16_t offset = ETHERNET_MANAGER_EEPROM_START + sizeof(Ethernet_Manager_config);
                
      // Find the longest pdata, then dynamically allocate buffer. Remember to free when done
      // This is used to store tempo data to calculate checksum to see of data is valid
      // We dont like to destroy myMenuItems[i].pdata with invalid data      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        if (myMenuItems[i].maxlen > BUFFER_LEN)
        {
          // Size too large, abort and flag false
          ETM_LOGINFO(F("ChkCrR: Error Small Buffer."));
          return false;
        }
      }
         
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = readBuffer;
        
        // Prepare buffer, more than enough
        memset(readBuffer, 0, sizeof(readBuffer));
        
        // Read more than necessary, but OK and easier to code
        EEPROM.get(offset, readBuffer);
        // NULL terminated
        readBuffer[myMenuItems[i].maxlen] = 0;
   
        ETM_LOGINFO3(F("ChkCrR:pdata="), readBuffer, F(",len="), myMenuItems[i].maxlen);
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++)
        {         
          checkSum += *_pointer;  
        }   
        
        offset += myMenuItems[i].maxlen;    
      }

      EEPROM.get(offset, readCheckSum);
           
      ETM_LOGINFO3(F("ChkCrR:CrCCsum="), String(checkSum, HEX), F(",CrRCsum="), String(readCheckSum, HEX));
           
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }


    bool EEPROM_getDynamicData(void)
    {
      int readCheckSum;
      int checkSum = 0;
      uint16_t offset = ETHERNET_MANAGER_EEPROM_START + sizeof(Ethernet_Manager_config);
           
      totalDataSize = sizeof(Ethernet_Manager_config) + sizeof(readCheckSum);
      
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
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
   
        ETM_LOGINFO3(F("CR:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);         
      }
      
      EEPROM.get(offset, readCheckSum);
      
      ETM_LOGINFO3(F("CrCCsum="), String(checkSum, HEX), F(",CrRCsum="), String(readCheckSum, HEX));
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;
    }

    void EEPROM_putDynamicData(void)
    {
      int checkSum = 0;
      uint16_t offset = ETHERNET_MANAGER_EEPROM_START + sizeof(Ethernet_Manager_config);
                
      for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
            
        //ETM_LOGINFO3(F("CW:pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
                            
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
    
    void saveConfigData()
    {
      int calChecksum = calcChecksum();
      Ethernet_Manager_config.checkSum = calChecksum;
      
      ETM_LOGINFO1(F("Save,WCSum=0x"), String(calChecksum, HEX));

      EEPROM.put(ETHERNET_MANAGER_EEPROM_START, Ethernet_Manager_config);
      EEPROM_putDynamicData();
      
      EEPROM.commit();
    }
    
    void loadAndSaveDefaultConfigData(void)
    {
      // Load Default Config Data from Sketch
      memcpy(&Ethernet_Manager_config, &defaultConfig, sizeof(Ethernet_Manager_config));
      strcpy(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE);
      
      // Including config and dynamic data, and assume valid
      saveConfigData();
       
      ETM_LOGDEBUG(F("======= Start Loaded Config Data ======="));
      displayConfigData(Ethernet_Manager_config);
    }
    
    bool getConfigData()
    {
      bool dynamicDataValid;
      
      hadConfigData = false; 
      
      EEPROM.begin(EEPROM_SIZE);
      ETM_LOGINFO1(F("EEPROMsz:"), EEPROM_SIZE);
      
      EEPROM.get(ETHERNET_MANAGER_EEPROM_START, Ethernet_Manager_config);
    
      ETM_LOGINFO(F("======= Start Stored Config Data ======="));
      displayConfigData(Ethernet_Manager_config);

      int calChecksum = calcChecksum();

      ETM_LOGWARN3(F("CCSum=0x"), String(calChecksum, HEX),
                 F(",RCSum=0x"), String(Ethernet_Manager_config.checkSum, HEX));
                      
      if (LOAD_DEFAULT_CONFIG_DATA)
      {
        // Load default dynamicData, if checkSum OK => valid data => load
        // otherwise, use default in sketch and just assume it's OK        
        if (checkDynamicData())
        {   
          ETM_LOGDEBUG(F("Valid Stored Dynamic Data"));
        
          EEPROM_getDynamicData();
          dynamicDataValid = true;
        }
        else
        {
          ETM_LOGWARN(F("Invalid Stored Dynamic Data. Ignored"));
          dynamicDataValid = false;
        }           
      }
      else
      {           
        dynamicDataValid = EEPROM_getDynamicData();    
      }  
      
      if ( (strncmp(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE, strlen(ETHERNET_BOARD_TYPE)) != 0) ||
           (calChecksum != Ethernet_Manager_config.checkSum) || !dynamicDataValid )
      {
        // Including Credentials CSum
        ETM_LOGINFO3(F("InitEEPROM,sz="), EEPROM_SIZE, F(",Datasz="), totalDataSize);
        
        // doesn't have any configuration        
        if (LOAD_DEFAULT_CONFIG_DATA)
        {
          memcpy(&Ethernet_Manager_config, &defaultConfig, sizeof(Ethernet_Manager_config));
        }
        else
        {  
          memset(&Ethernet_Manager_config, 0, sizeof(Ethernet_Manager_config));

          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
          }
          
          // Including Credentials CSum
          ETM_LOGINFO3(F("InitEEPROM,sz="), EEPROM_SIZE, F(",Datasz="), totalDataSize);

          // doesn't have any configuration
          strcpy(Ethernet_Manager_config.static_IP,   WM_NO_CONFIG);
          strcpy(Ethernet_Manager_config.board_name,  WM_NO_CONFIG);

          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            strncpy(myMenuItems[i].pdata, WM_NO_CONFIG, myMenuItems[i].maxlen);
          }
        }
        
        strcpy(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE);

        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          ETM_LOGDEBUG3(F("g:myMenuItems["), i, F("]="), myMenuItems[i].pdata );
        }
                
        // Don't need
        Ethernet_Manager_config.checkSum = 0;

        EEPROM.put(ETHERNET_MANAGER_EEPROM_START, Ethernet_Manager_config);
        EEPROM_putDynamicData();
        EEPROM.commit();

        return false;
      }
      else
      {
        displayConfigData(Ethernet_Manager_config);
      }

      return true;
    }

#endif      // ( USE_LITTLEFS || USE_SPIFFS )

    // NEW
    void createHTML(String& root_html_template)
    {
      String pitem;
      
      root_html_template = String(ETM_HTML_HEAD);
     
      if (NUM_MENU_ITEMS > 0)
      {
        root_html_template += String(ETM_FLDSET_START);
           
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          pitem = String(ETM_HTML_PARAM);

          pitem.replace("{b}", myMenuItems[i].displayName);
          pitem.replace("{v}", myMenuItems[i].id);
          pitem.replace("{i}", myMenuItems[i].id);
          
          root_html_template += pitem;      
        }
            
        root_html_template += String(ETM_FLDSET_END);
      }
      
      root_html_template += String(ETM_HTML_BUTTON) + String(ETM_HTML_SCRIPT);   
           
      if (NUM_MENU_ITEMS > 0)
      {        
        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          pitem = String(ETM_HTML_SCRIPT_ITEM);
          
          pitem.replace("{d}", myMenuItems[i].id);
          
          root_html_template += pitem;        
        }
      }
      
      root_html_template += String(ETM_HTML_SCRIPT_END) + String(ETM_HTML_END);
      
      return;      
    }
    ////
    
    void handleRequest()
    {
      if (server)
      {
        String key = server->arg("key");
        String value = server->arg("value");

        //static int number_items_Updated = 0;
        static int number_items_Updated = -1;

        if (key == "" && value == "")
        {
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

          result.replace("[[ip]]",     Ethernet_Manager_config.static_IP);
          result.replace("[[nm]]",     Ethernet_Manager_config.board_name);

          for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            String toChange = String("[[") + myMenuItems[i].id + "]]";
            result.replace(toChange, myMenuItems[i].pdata);
              
            ETM_LOGDEBUG3(F("h1:myMenuItems["), i, F("]="), myMenuItems[i].pdata );
          }

          server->send(200, "text/html", result);
          
          return;
        }
        
        if (number_items_Updated < 0)
        {
          number_items_Updated = 0;
          memset(&Ethernet_Manager_config, 0, sizeof(Ethernet_Manager_config));
          strcpy(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE);
        }
        
        ETM_LOGINFO1(F("h:items updated ="), number_items_Updated);
        ETM_LOGINFO3(F("h:key ="), key, ", value =", value);
        
        if (key == String("ip"))
        {
          ETM_LOGINFO(F("h:ip"));

          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Ethernet_Manager_config.static_IP) - 1)
            strcpy(Ethernet_Manager_config.static_IP, value.c_str());
          else
            strncpy(Ethernet_Manager_config.static_IP, value.c_str(), sizeof(Ethernet_Manager_config.static_IP) - 1);
        }
        else if (key == String("nm"))
        {
          ETM_LOGINFO(F("h:nm"));

          number_items_Updated++;
          if (strlen(value.c_str()) < sizeof(Ethernet_Manager_config.board_name) - 1)
            strcpy(Ethernet_Manager_config.board_name, value.c_str());
          else
            strncpy(Ethernet_Manager_config.board_name, value.c_str(), sizeof(Ethernet_Manager_config.board_name) - 1);
        }

        //ETM_LOGINFO(F("h:OK"));

        for (uint16_t i = 0; i < NUM_MENU_ITEMS; i++)
        {
          if (key == myMenuItems[i].id)
          {
            //ETM_LOGDEBUG3(F("h:"), myMenuItems[i].id, F("="), value.c_str() );
            number_items_Updated++;

            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);

            if ((int) strlen(value.c_str()) < myMenuItems[i].maxlen)
              strcpy(myMenuItems[i].pdata, value.c_str());
            else
              strncpy(myMenuItems[i].pdata, value.c_str(), myMenuItems[i].maxlen);
                             
            ETM_LOGINFO3(F("h2:myMenuItems["), i, F("]="), myMenuItems[i].pdata );            
          }
        }
        
        server->send(200, "text/html", "OK");

        // NEW
        if (number_items_Updated == NUM_CONFIGURABLE_ITEMS + NUM_MENU_ITEMS)
        {
#if USE_LITTLEFS
          ETM_LOGWARN1(F("h:Updating LittleFS:"), CONFIG_FILENAME);        
#elif USE_SPIFFS
          ETM_LOGWARN1(F("h:Updating SPIFFS:"), CONFIG_FILENAME);
#else
          ETM_LOGWARN(F("h:Updating EEPROM. Please wait for reset"));
#endif

          saveConfigData();

          ETM_LOGWARN(F("h:Rst"));

          // Delay then reset after save data
          //delay(200);
          resetFunc();
        }
      }     // if (server)
    }

    void startConfigurationMode()
    {
#define CONFIG_TIMEOUT			60000L

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
        configTimeout = millis() + CONFIG_TIMEOUT;
      else
        configTimeout = 0;

      configuration_mode = true;
    }

    bool connectEthernet()
    {
      // Check go see if static IP is required
      IPAddress staticIP;
      
      if (staticIP.fromString(Ethernet_Manager_config.static_IP))
      {
        // Use static IP
        ETM_LOGWARN1(F("Start connectEthernet using Static IP ="), staticIP);
        
        Ethernet.begin(SelectMacAddress(NULL), staticIP);
        ethernetConnected = true;
      }
      else
      {
        // If static_IP ="nothing"  or NULL, use DHCP dynamic IP
        ETM_LOGWARN(F("Start connectEthernet using DHCP"));
        
        ethernetConnected = ( Ethernet.begin(SelectMacAddress(NULL)) == 1);
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

    byte* SelectMacAddress(const byte mac[])
    {
      if (mac != NULL) 
      {
        return (byte*)mac;
      }

      macAddress[0] = 0xFE;
      macAddress[1] = 0xAB;
      macAddress[2] = 0xCD;
      macAddress[3] = 0xEF;
      macAddress[4] = 0xED;
      macAddress[5] = 0xBA;
      
      const char* token = String(millis()).c_str();

      int len = strlen(token);
      int mac_index = 1;

      for (uint16_t i = 0; i < len; i++)
      {
        macAddress[mac_index] ^= token[i];

        if (++mac_index > 5) {
          mac_index = 1;
        }
      }
      
      char localBuffer[24];
      
      snprintf(localBuffer, sizeof(localBuffer), "MAC:%02X-%02X-%02X-%02X-%02X-%02X",
                macAddress[0], macAddress[1],
                macAddress[2], macAddress[3],
                macAddress[4], macAddress[5]);
                
      ETM_LOGWARN(localBuffer);

      return macAddress;
    }

    byte macAddress[6];

};

#endif    // Ethernet_ESP32_Manager_h
