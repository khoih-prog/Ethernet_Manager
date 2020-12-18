/****************************************************************************************************************************
  Ethernet_DUE_Manager.h
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

#ifndef Ethernet_DUE_Manager_h
#define Ethernet_DUE_Manager_h

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(ETHERNET_USE_SAM_DUE)
  #undef ETHERNET_USE_SAM_DUE
  #endif
  #warning ETHERNET_USE_SAM_DUE from Ethernet_DUE_Manager.h
  #define ETHERNET_USE_SAM_DUE      true
#else
  #error This code is designed to run on SAM DUE platform! Please check your Tools->Board setting.
#endif

// Increase HTTP_UPLOAD_BUFLEN to 4K, instead of default 2K in <EthernetWebServer.h>
#define HTTP_UPLOAD_BUFLEN    4096

//Use DueFlashStorage to simulate EEPROM
#include <DueFlashStorage.h>                 //https://github.com/sebnil/DueFlashStorage

DueFlashStorage dueFlashStorageData;

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

// RTC Memory Address for the DoubleResetDetector to use
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

const char ETM_HTML_HEAD[]     /*PROGMEM*/ = "<!DOCTYPE html><html><head><title>Ethernet_DUE_Manager</title><style>div,input{padding:2px;font-size:1em;}input{width:95%;}\
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
  
#if 0  
    // DHCP with domain
    void begin( const byte mac[] = NULL)
    {
      ETM_LOGWARN(F("GetIP:"));

      if (!Ethernet.begin(SelectMacAddress(mac))) 
      {
        ETM_LOGERROR(F("DHCP 0"));
      }
      // give the Ethernet shield a second to initialize:
      delay(1000);
      
      IPAddress myip = Ethernet.localIP();
      
      ETM_LOGWARN1(F("IP:"), myip);
    }

    // Static IP
    void begin( IPAddress local, const byte mac[] = NULL)
    {
      ETM_LOGWARN(F("UseStatIP"));

      Ethernet.begin(SelectMacAddress(mac), local);
      // give the Ethernet shield a second to initialize:
      delay(1000);
      
      IPAddress myip = Ethernet.localIP();
      ETM_LOGWARN1(F("IP:"), myip);
    }
    
    // Static IP with DNS
    void begin( IPAddress local, IPAddress dns, const byte mac[] = NULL)
    {
      ETM_LOGWARN(F("UseStatIP"));

      Ethernet.begin(SelectMacAddress(mac), local, dns);
      // give the Ethernet shield a second to initialize:
      delay(1000);
      
      IPAddress myip = Ethernet.localIP();
      ETM_LOGWARN1(F("IP:"), myip);
    }

    // Static IP with DNS, GW, SN
    void begin( IPAddress local, IPAddress dns, IPAddress gateway, IPAddress subnet, const byte mac[] = NULL)
    {
      ETM_LOGWARN(F("UseStatIP"));

      Ethernet.begin(SelectMacAddress(mac), local, dns, gateway, subnet);
      // give the Ethernet shield a second to initialize:
      delay(1000);
      
      IPAddress myip = Ethernet.localIP();
      ETM_LOGWARN1(F("IP:"), myip);
    }
#endif

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
      static int retryTimes = 0;
      
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
      
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
      }
      
      saveConfigData();
    }
    
    void resetFunc()
    {
      rstc_start_software_reset(RSTC);
    }

  private:
   
    // Initialize the Ethernet server library
    // with the IP address and port you want to use
    // (port 80 is default for HTTP):
    EthernetWebServer *server;

    bool ethernetConnected = false;

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
        String _hostname = "DUE-XXXXXX";    // + String(macAddress, HEX);
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
                 
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {
        ETM_LOGINFO3("i=", i, ",id=", myMenuItems[i].id);
        ETM_LOGINFO1("data=", myMenuItems[i].pdata);
      }      
    }

#define ETHERNET_BOARD_TYPE   "SAMDUE"
#define WM_NO_CONFIG          "blank"
    
uint16_t EEPROM_SIZE = (IFLASH1_PAGE_SIZE / sizeof(byte)) * 4;

#ifndef EEPROM_START
  #define EEPROM_START     0
  #warning EEPROM_START not defined. Set to 0
#endif

// Stating positon to store Blynk8266_WM_config
#define ETHERNET_MANAGER_EEPROM_START    (EEPROM_START + DRD_FLAG_DATA_SIZE)

    int calcChecksum()
    {
      int checkSum = 0;
      for (uint16_t index = 0; index < (sizeof(Ethernet_Manager_config) - sizeof(Ethernet_Manager_config.checkSum)); index++)
      {
        checkSum += * ( ( (byte*) &Ethernet_Manager_config ) + index);
      }

      return checkSum;
    }

    bool checkDynamicData(void)
    {
      int checkSum = 0;
      int readCheckSum;
      
      uint16_t  byteCount = 0;
      
      //#define BUFFER_LEN            128
      //char readBuffer[BUFFER_LEN + 1];
      
      #define BIG_BUFFER_LEN        768     
      byte bigBuffer[BIG_BUFFER_LEN + 1];      
      
      uint16_t offset = ETHERNET_MANAGER_EEPROM_START + sizeof(Ethernet_Manager_config);      
           
      // Make address 4-byte aligned
      if ( (offset % 4) != 0 )
      {
        offset += 4 - (offset % 4);
      }
      
      // Find the longest pdata, then dynamically allocate buffer. Remember to free when done
      // This is used to store tempo data to calculate checksum to see of data is valid
      // We dont like to destroy myMenuItems[i].pdata with invalid data
      int totalLength = 0;
            
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        totalLength += myMenuItems[i].maxlen;
        
        if ( (totalLength > BIG_BUFFER_LEN) || (myMenuItems[i].maxlen > BIG_BUFFER_LEN) )
        {
          // Size too large, abort and flag false
          ETM_LOGINFO(F("ChkCrR: Error Small Buffer."));
          return false;
        }
      }
                         
      // Both Buffers big enough, read all dynamicData to BigBuffer once 
      // as address need to be 4-byte aligned
      byte* dataPointer = (byte* ) dueFlashStorageData.readAddress(offset);
      
      // Prepare buffer, more than enough
      memset(bigBuffer, 0, sizeof(bigBuffer));
      memcpy(bigBuffer, dataPointer, sizeof(bigBuffer));               
         
      // Don't need readBuffer
      // Now to split into individual piece to add to CSum
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = (char*) bigBuffer;
        
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++, _pointer++, byteCount++)
        {
          *_pointer = bigBuffer[byteCount];
                  
          checkSum += *_pointer;  
        }    
      }
      
      memcpy(&readCheckSum, &bigBuffer[byteCount], sizeof(readCheckSum));
          
      ETM_LOGINFO3(F("ChkCrR:CrCCSum=0x"), String(checkSum, HEX), F(",CrRCSum=0x"), String(readCheckSum, HEX));
           
      if ( checkSum != readCheckSum )
      {
        return false;
      }
      
      return true;    
    }
    
    bool dueFlashStorage_get(void)
    {
      uint16_t offset = ETHERNET_MANAGER_EEPROM_START;
            
      byte* dataPointer = (byte* ) dueFlashStorageData.readAddress(offset);
      
      memcpy(&Ethernet_Manager_config, dataPointer, sizeof(Ethernet_Manager_config));
      
      offset += sizeof(Ethernet_Manager_config);
           
      // Make address 4-byte aligned
      if ( (offset % 4) != 0 )
      {
        offset += 4 - (offset % 4);
      }
            
      int checkSum = 0;
      int readCheckSum;
      
      uint16_t  byteCount = 0;
           
      byte buffer[768];
      
      dataPointer = (byte* ) dueFlashStorageData.readAddress(offset);
      
      memcpy(buffer, dataPointer, sizeof(buffer));
      
      totalDataSize = sizeof(Ethernet_Manager_config) + sizeof(readCheckSum);
   
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
        totalDataSize += myMenuItems[i].maxlen;
        
        // Actual size of pdata is [maxlen + 1]
        memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
                      
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++,_pointer++, byteCount++)
        {
          *_pointer = buffer[byteCount];
          
          checkSum += *_pointer;  
         }     
      }
      
      memcpy(&readCheckSum, &buffer[byteCount], sizeof(readCheckSum));
      
      byteCount += sizeof(readCheckSum);      
      
      ETM_LOGINFO3(F("CrCCSum=0x"), String(checkSum, HEX), F(",CrRCSum=0x"), String(readCheckSum, HEX));
      ETM_LOGINFO1(F("TotalDataSz="), totalDataSize);          
      
      if ( checkSum != readCheckSum)
      {
        return false;
      }
      
      return true;
    }    
    
    void dueFlashStorage_put(void)
    {
      uint16_t offset = ETHERNET_MANAGER_EEPROM_START;
      
      dueFlashStorageData.write(offset, (byte *) &Ethernet_Manager_config, sizeof(Ethernet_Manager_config));
      
      offset += sizeof(Ethernet_Manager_config);
      
      // Make address 4-byte aligned
      if ( (offset % 4) != 0 )
      {
        offset += 4 - (offset % 4);
      }
      
      int       checkSum = 0;
      uint16_t  byteCount = 0;
           
      // Use 2K buffer, if need more memory, can reduce this
      byte buffer[2048];
         
      for (int i = 0; i < NUM_MENU_ITEMS; i++)
      {       
        char* _pointer = myMenuItems[i].pdata;
        
        //ETM_LOGINFO3(F("pdata="), myMenuItems[i].pdata, F(",len="), myMenuItems[i].maxlen);
                     
        for (uint16_t j = 0; j < myMenuItems[i].maxlen; j++, _pointer++, /*offset++,*/ byteCount++)
        {
          if (byteCount >= sizeof(buffer))
          {
            ETM_LOGINFO1(F("Danger:dynamic data too long >"), sizeof(buffer));
          }
          
          buffer[byteCount] = *_pointer;          
          checkSum += *_pointer;     
         }
      }
           
      memcpy(&buffer[byteCount], &checkSum, sizeof(checkSum));
      
      byteCount += sizeof(checkSum);
      
      dueFlashStorageData.write(offset, buffer, byteCount);
      
      ETM_LOGINFO3(F("CrCCSum=0x"), String(checkSum, HEX), F(",byteCount="), byteCount);
    }
    
    void saveConfigData()
    {
      int calChecksum = calcChecksum();
      Ethernet_Manager_config.checkSum = calChecksum;
      
      ETM_LOGINFO3(F("SaveData,sz="), totalDataSize, F(",WCSum=0x"), String(calChecksum, HEX));

      dueFlashStorage_put();
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
      int calChecksum; 
      
      hadConfigData = false;    
          
      // For DUE, DATA_LENGTH = ((IFLASH1_PAGE_SIZE/sizeof(byte))*4) = 1KBytes
      ETM_LOGINFO1(F("Simulate EEPROM, sz:"), DATA_LENGTH);

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
        // Load stored config / dynamic data from dueFlashStorage
        // Verify ChkSum
        //dynamicDataValid = dueFlashStorage_get();
        dynamicDataValid = checkDynamicData();
        
        calChecksum = calcChecksum();

        ETM_LOGINFO3(F("CCSum=0x"), String(calChecksum, HEX),
                   F(",RCSum=0x"), String(Ethernet_Manager_config.checkSum, HEX));
                   
        if (dynamicDataValid)
        {
          dueFlashStorage_get();
             
          ETM_LOGDEBUG(F("Valid Stored Dynamic Data"));      
          ETM_LOGINFO(F("======= Start Stored Config Data ======="));
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

      if ( (strncmp(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE, strlen(ETHERNET_BOARD_TYPE)) != 0) ||
           (calChecksum != Ethernet_Manager_config.checkSum) || !dynamicDataValid )
      {
        // Including Credentials CSum
        ETM_LOGINFO1(F("InitEEPROM,Datasz="), totalDataSize);
        
        // doesn't have any configuration        
        if (LOAD_DEFAULT_CONFIG_DATA)
        {
          memcpy(&Ethernet_Manager_config, &defaultConfig, sizeof(Ethernet_Manager_config));
        }
        else
        {  
          memset(&Ethernet_Manager_config, 0, sizeof(Ethernet_Manager_config));

          for (int i = 0; i < NUM_MENU_ITEMS; i++)
          {
            // Actual size of pdata is [maxlen + 1]
            memset(myMenuItems[i].pdata, 0, myMenuItems[i].maxlen + 1);
          }
          
          // Including Credentials CSum
          ETM_LOGINFO1(F("InitEEPROM,Datasz="), totalDataSize);

          // doesn't have any configuration
          strcpy(Ethernet_Manager_config.static_IP,   WM_NO_CONFIG);
          strcpy(Ethernet_Manager_config.board_name,  WM_NO_CONFIG);

          for (int i = 0; i < NUM_MENU_ITEMS; i++)
          {
            strncpy(myMenuItems[i].pdata, WM_NO_CONFIG, myMenuItems[i].maxlen);
          }
        }
        
        strcpy(Ethernet_Manager_config.header, ETHERNET_BOARD_TYPE);

        for (int i = 0; i < NUM_MENU_ITEMS; i++)
        {
          ETM_LOGDEBUG3(F("g:myMenuItems["), i, F("]="), myMenuItems[i].pdata );
        }
                
        // Don't need
        Ethernet_Manager_config.checkSum = 0;

        dueFlashStorage_put();

        return false;
      }
      else
      {
        displayConfigData(Ethernet_Manager_config);
      }

      return true;
    }

    // NEW
    void createHTML(String& root_html_template)
    {
      String pitem;
      
      root_html_template = String(ETM_HTML_HEAD);
     
      if (NUM_MENU_ITEMS > 0)
      {
        root_html_template += String(ETM_FLDSET_START);
           
        for (int i = 0; i < NUM_MENU_ITEMS; i++)
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
        for (int i = 0; i < NUM_MENU_ITEMS; i++)
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
            result.replace("Ethernet_DUE_Manager", RFC952_hostname);
          }
          else if ( Ethernet_Manager_config.board_name[0] != 0 )
          {
            // Or replace only if board_name is valid.  Otherwise, keep intact
            result.replace("Ethernet_DUE_Manager", Ethernet_Manager_config.board_name);
          }

          result.replace("[[ip]]",     Ethernet_Manager_config.static_IP);
          result.replace("[[nm]]",     Ethernet_Manager_config.board_name);

          for (int i = 0; i < NUM_MENU_ITEMS; i++)
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

        for (int i = 0; i < NUM_MENU_ITEMS; i++)
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
#if USE_SPIFFS
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

      for (int i = 0; i < len; i++)
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
#endif    // Ethernet_DUE_Manager_h
