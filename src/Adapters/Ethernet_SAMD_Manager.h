/****************************************************************************************************************************
  Ethernet_SAMD_Manager.h
  For W5x00 and ENC28J60 Ethernet shields.

  Ethernet_Manager is a library for nRF52, Teensy, STM32, SAM DUE and SAMD boards, with Ethernet W5x00 or ENC28J60 shields,
  to enable easy configuration/reconfiguration of Credentials and autoconnect/autoreconnect of Ethernet.
  AVR Mega is not supported.

  Built by Khoi Hoang https://github.com/khoih-prog/Ethernet_Manager
  Licensed under MIT license
  Version: 1.3.0

  Version  Modified By   Date      Comments
  -------  -----------  ---------- -----------
  1.0.0     K Hoang     14/12/2020 Initial coding.
  1.1.0     K Hoang     17/12/2020 Add support to ESP32/ESP8266. Add MQTT related examples to demo dynamic parameter usage
  1.1.1     K Hoang     28/12/2020 Suppress all possible compiler warnings
  1.2.0     K Hoang     22/02/2021 Optimize code and use better FlashStorage_SAMD and FlashStorage_STM32. 
                                   Add customs HTML header feature. Fix bug.
  1.3.0     K Hoang     16/05/2021 Add support to RP2040-based boards such as RASPBERRY_PI_PICO
 *****************************************************************************************************************************/

#pragma once

#ifndef Ethernet_SAMD_Manager_h
#define Ethernet_SAMD_Manager_h

#if ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
   || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) \
   || defined(ARDUINO_SAMD_MKRWAN1310) || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) \
   || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) \
   || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) )
  #if defined(ETHERNET_USE_SAMD)
  #undef ETHERNET_USE_SAMD
  #endif
  #warning ETHERNET_USE_SAMD from Ethernet_SAMD_Manager.h
  #define ETHERNET_USE_SAMD      true
#else
  #error This code is designed to run on SAMD platform! Please check your Tools->Board setting.
#endif

// Increase HTTP_UPLOAD_BUFLEN to 4K, instead of default 2K in <EthernetWebServer.h>
#define HTTP_UPLOAD_BUFLEN    4096

// Include EEPROM-like API for FlashStorage
//#include <FlashAsEEPROM.h>                //https://github.com/cmaglie/FlashStorage
#include <FlashAsEEPROM_SAMD.h>             //https://github.com/khoih-prog/FlashStorage_SAMD

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
// These defines must be put before #include <DoubleResetDetector_Generic.h>
// to select where to store DoubleResetDetector_Generic's variable.
// Otherwise, library will use default EEPROM storage
#define  DRD_FLAG_DATA_SIZE     4

#ifndef DOUBLERESETDETECTOR_DEBUG
  #define DOUBLERESETDETECTOR_DEBUG     false
#endif

#include <DoubleResetDetector_Generic.h>      //https://github.com/khoih-prog/DoubleResetDetector_Generic

// Number of seconds after reset during which a
// subseqent reset will be considered a double reset.
#define DRD_TIMEOUT 10

// RTC Memory Address for the DoubleResetDetector_Generic to use
#define DRD_ADDRESS 0

DoubleResetDetector_Generic* drd;

///////// NEW for DRD /////////////

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
  bool *menuItemUpdated = NULL;
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

const char ETM_HTML_HEAD_START[] /*PROGMEM*/ = "<!DOCTYPE html><html><head><title>Ethernet_SAMD_Manager</title>";

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
      drd = new DoubleResetDetector_Generic(DRD_TIMEOUT, DRD_ADDRESS);  
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

      // Check if NULL pointer
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
      // Best one. Possibly don't need the WDT
      NVIC_SystemReset();
      
#if ( defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) || defined(__SAMD51G19A__)  )
      // For SAMD51
      // see Table 17-5 Timeout Period (valid values 0-11)
      WDT->CONFIG.reg = 5; 
      WDT->CTRLA.reg = WDT_CTRLA_ENABLE;
      // To check if OK or bit.ENABLE/CLEAR
      while (WDT->SYNCBUSY.bit.WEN == 1);
      
      // use the WDT watchdog timer to force a system reset.
      WDT->CLEAR.reg= 0x00;
      // To check if OK or bit.ENABLE/CLEAR
      while (WDT->SYNCBUSY.bit.WEN == 1);
#else   
      // For SAMD21, etc
      // see Table 17-5 Timeout Period (valid values 0-11)
      WDT->CONFIG.reg = 5; 
      WDT->CTRL.reg = WDT_CTRL_ENABLE;
      while (WDT->STATUS.bit.SYNCBUSY == 1);
      
      // use the WDT watchdog timer to force a system reset.
      WDT->CLEAR.reg= 0x00;
      while (WDT->STATUS.bit.SYNCBUSY == 1);
#endif      
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
      ETM_LOGDEBUG1(F("Set CustomsStyle to : "), ETM_HTML_HEAD_CUSTOMS_STYLE);
    }
    
    const char* getCustomsStyle()
    {
      ETM_LOGDEBUG1(F("Get CustomsStyle = "), ETM_HTML_HEAD_CUSTOMS_STYLE);
      return ETM_HTML_HEAD_CUSTOMS_STYLE;
    }
#endif

#if USING_CUSTOMS_HEAD_ELEMENT    
    //sets a custom element to add to head, like a new style tag
    void setCustomsHeadElement(const char* CustomsHeadElement = NULL) 
    {
      _CustomsHeadElement = CustomsHeadElement;
      ETM_LOGDEBUG1(F("Set CustomsHeadElement to : "), _CustomsHeadElement);
    }
    
    const char* getCustomsHeadElement()
    {
      ETM_LOGDEBUG1(F("Get CustomsHeadElement = "), _CustomsHeadElement);
      return _CustomsHeadElement;
    }
#endif
    
#if USING_CORS_FEATURE   
    void setCORSHeader(const char* CORSHeaders = NULL)
    {     
      _CORS_Header = CORSHeaders;

      ETM_LOGDEBUG1(F("Set CORS Header to : "), _CORS_Header);
    }
    
    const char* getCORSHeader()
    {      
      ETM_LOGDEBUG1(F("Get CORS Header = "), _CORS_Header);
      return _CORS_Header;
    }
#endif
          
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

/////////////////////////////////////
    
    // Add customs headers from v1.1.0
    
#if USING_CUSTOMS_STYLE
    const char* ETM_HTML_HEAD_CUSTOMS_STYLE = NULL;
#endif
    
#if USING_CUSTOMS_HEAD_ELEMENT
    const char* _CustomsHeadElement = NULL;
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
        String _hostname = "SAMD-XXXXXX";    // + String(macAddress, HEX);
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

#define ETHERNET_BOARD_TYPE   "SAMD"
#define WM_NO_CONFIG          "blank"

// DRD_FLAG_DATA_SIZE is 4, to store DRD flag, defined in DRD
#if (EEPROM_SIZE < DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE)
  #error EEPROM_SIZE must be > CONFIG_DATA_SIZE.
#endif

#ifndef EEPROM_START
  #define EEPROM_START     0
  #warning EEPROM_START not defined. Set to 0
#else
  #if (EEPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE > EEPROM_SIZE)
    #error EPROM_START + DRD_FLAG_DATA_SIZE + CONFIG_DATA_SIZE + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE > EEPROM_SIZE. Please adjust.
  #endif
#endif

// Stating positon to store Blynk8266_WM_config
#define CONFIG_EEPROM_START    (EEPROM_START + DRD_FLAG_DATA_SIZE)

    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(Ethernet_Manager_config) - sizeof(Ethernet_Manager_config.checkSum)); index++)
      {
        checkSum += * ( ( (byte*) &Ethernet_Manager_config ) + index);
      }

      return checkSum;
    }
    
    //////////////////////////////////////////////
    
    void setForcedCP(bool isPersistent)
    {
      uint32_t readForcedConfigPortalFlag = isPersistent? FORCED_PERS_CONFIG_PORTAL_FLAG_DATA : FORCED_CONFIG_PORTAL_FLAG_DATA;
    
      ETM_LOGERROR(isPersistent ? F("setForcedCP Persistent") : F("setForcedCP non-Persistent"));

      EEPROM.put(CONFIG_EEPROM_START + CONFIG_DATA_SIZE, readForcedConfigPortalFlag);      
      EEPROM.commit();
    }
    
    //////////////////////////////////////////////
    
    void clearForcedCP()
    {
      EEPROM.put(CONFIG_EEPROM_START + CONFIG_DATA_SIZE, 0);     
      EEPROM.commit();
    }
    
    //////////////////////////////////////////////

    bool isForcedCP()
    {
      uint32_t readForcedConfigPortalFlag;

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
      // It's too bad that emulate EEPROM.read()/write() can only deal with bytes. 
      // Have to read/write each byte. To rewrite the library
      
      int checkSum = 0;
      int readCheckSum;
      
      uint16_t offset = CONFIG_EEPROM_START + sizeof(Ethernet_Manager_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
           
      #define BUFFER_LEN      128
      char readBuffer[BUFFER_LEN + 1];
                     
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
                  
      ETM_LOGERROR3(F("ChkCrR:CrCCsum=0x"), String(checkSum, HEX), F(",CrRCsum=0x"), String(readCheckSum, HEX));
           
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;    
    }
    
    //////////////////////////////////////////////
    
    bool EEPROM_getDynamicData()
    {          
      int checkSum = 0;
      int readCheckSum;
      
      totalDataSize = sizeof(Ethernet_Manager_config) + sizeof(readCheckSum);
          
      // Using FORCED_CONFIG_PORTAL_FLAG_DATA
      //offset += FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
      uint16_t offset = CONFIG_EEPROM_START + sizeof(Ethernet_Manager_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
      
      uint8_t* _pointer;
   
      for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        _pointer = (uint8_t *) myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;
        
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
               
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++, _pointer++, offset++)
        {
          *_pointer = EEPROM.read(offset);          
          checkSum += *_pointer;  
        }       
      }

      EEPROM.get(offset, readCheckSum);
         
      ETM_LOGERROR3(F("CrCCSum="), String(checkSum, HEX), F(",CrRCSum="), String(readCheckSum, HEX));
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
     
      return true;
    }
    
    //////////////////////////////////////////////
    
    void EEPROM_putDynamicData()
    {
      // It's too bad that emulate EEPROM.read()/writ() can only deal with bytes. 
      // Have to read/write each byte. To rewrite the library          
      int checkSum = 0;
      
      // Using FORCED_CONFIG_PORTAL_FLAG_DATA
      //offset += FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
      uint16_t offset = CONFIG_EEPROM_START + sizeof(Ethernet_Manager_config) + FORCED_CONFIG_PORTAL_FLAG_DATA_SIZE;
      uint8_t* _pointer;
    
      for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        _pointer = (uint8_t *) myMenuItems[i].pdata;
      
        ETM_LOGDEBUG3(F("pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++,offset++)
        {
          EEPROM.write(offset, *_pointer);
          
          checkSum += *_pointer;     
        }
      }

      EEPROM.put(offset, checkSum);
     
      ETM_LOGERROR1(F("CrCCSum=0x"), String(checkSum, HEX));
      
      EEPROM.commit();
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
    
    bool EEPROM_get()
    {      
      EEPROM.get(CONFIG_EEPROM_START, Ethernet_Manager_config);
      
      NULLTerminateConfig();
      
      return true;
    }
    
    //////////////////////////////////////////////
    
    void EEPROM_put()
    {
      EEPROM.put(CONFIG_EEPROM_START, Ethernet_Manager_config);
      EEPROM.commit();      
    }
    
    //////////////////////////////////////////////
    
    void saveConfigData()
    {
      int calChecksum = calcChecksum();
      Ethernet_Manager_config.checkSum = calChecksum;
      
      ETM_LOGINFO1(F("SaveEEPROM,Sz="), EEPROM.length());
      ETM_LOGINFO3(F("DataSz="), totalDataSize, F(",WCSum=0x"), String(calChecksum, HEX));
      
      EEPROM_put();
      
#if USE_DYNAMIC_PARAMETERS        
      EEPROM_putDynamicData();
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
    
    bool getConfigData()
    {
      bool dynamicDataValid = true;
      int calChecksum; 
      
      hadConfigData = false; 
      
      // Use new LOAD_DEFAULT_CONFIG_DATA logic
      if (LOAD_DEFAULT_CONFIG_DATA)
      {     
        // Load Config Data from Sketch
        loadAndSaveDefaultConfigData();
        
        // Don't need Config Portal anymore
        return true; 
      }
      else
      {   
        // Get config data
        EEPROM_get();
        
        // Verify ChkSum
        calChecksum = calcChecksum();

        ETM_LOGERROR3(F("CCSum=0x"), String(calChecksum, HEX),
                     F(",RCSum=0x"), String(Ethernet_Manager_config.checkSum, HEX));
        
#if USE_DYNAMIC_PARAMETERS        
        // Load stored dynamic data from EEPROM
        dynamicDataValid = checkDynamicData();              
#endif
       
        // If checksum = 0 => FlashStorage has been cleared (by uploading new FW, etc) => force to CP
        if ( (calChecksum != 0) && (calChecksum == Ethernet_Manager_config.checkSum) )
        {           
          if (dynamicDataValid)
          {
#if USE_DYNAMIC_PARAMETERS          
            // CkSum verified, Now get valid config/ dynamic data
            EEPROM_getDynamicData();
            
            ETM_LOGERROR(F("Valid Stored Dynamic Data"));
#endif            
            ETM_LOGERROR(F("======= Start Stored Config Data ======="));
            displayConfigData(Ethernet_Manager_config);
            
            // Don't need Config Portal anymore
            return true;
          }
          else
          {
            // Invalid Stored config data => Config Portal
            ETM_LOGERROR(F("Invalid Stored Dynamic Data. Load default from Sketch"));
            
            // Load Default Config Data from Sketch, better than just "blank"
            loadAndSaveDefaultConfigData();
                             
            // Need Config Portal here as data can be just dummy
            // Even if you don't open CP, you're OK on next boot if your default config data is valid 
            return false;
          }      
        }
      }

      if ( (strncmp(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE, strlen(ETHERNET_BOARD_TYPE)) != 0) ||
           (calChecksum != Ethernet_Manager_config.checkSum) || !dynamicDataValid || 
           ( (calChecksum == 0) && (Ethernet_Manager_config.checkSum == 0) ) )   
      {
        // Including Credentials CSum
        ETM_LOGERROR1(F("InitCfgFile,sz="), sizeof(Ethernet_Manager_config));

        // doesn't have any configuration        
        if (LOAD_DEFAULT_CONFIG_DATA)
        {
          memcpy(&Ethernet_Manager_config, &defaultConfig, sizeof(Ethernet_Manager_config));
        }
        else
        {
          memset(&Ethernet_Manager_config, 0, sizeof(Ethernet_Manager_config));

#if USE_DYNAMIC_PARAMETERS
          for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
          }
#endif
              
          //strcpy(Ethernet_Manager_config.static_IP,   WM_NO_CONFIG);
          strcpy(Ethernet_Manager_config.board_name,  ETHERNET_BOARD_TYPE);
          
#if USE_DYNAMIC_PARAMETERS
          for (uint8_t i = 0; i < NUM_MENU_ITEMS; i++)
          {
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

        saveConfigData();
        
        return false;   
      }
      else
      {
        displayConfigData(Ethernet_Manager_config);
      }

      return true;
    }

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
          ETM_LOGERROR(F("h:Updating EEPROM. Please wait for reset"));

          saveConfigData();
          
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
                       
        ETM_LOGDEBUG3(F("s:millis() = "), millis(), F(", configTimeout = "), configTimeout);
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

#endif    // Ethernet_SAMD_Manager_h
