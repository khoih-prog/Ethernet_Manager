/****************************************************************************************************************************
  AM2315_Ethernet.ino
  For W5x00, LAN8720 and ENC28J60 Ethernet shields.

  Ethernet_Manager is a library for nRF52, Teensy, STM32, SAM DUE and SAMD boards, with Ethernet W5x00, LAN8720 or ENC28J60 shields,
  to enable easy configuration/reconfiguration of Credentials and autoconnect/autoreconnect of Ethernet.
  AVR Mega is not supported.

  Built by Khoi Hoang https://github.com/khoih-prog/Ethernet_Manager
  Licensed under MIT license
 *****************************************************************************************************************************/
 
#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_AM2315.h>        // To install Adafruit AM2315 library

// Connect RED of the AM2315 sensor to 5.0V
// Connect BLACK to Ground
// Connect WHITE to i2c clock (SCL) - on '168/'328 Arduino Uno/Duemilanove/etc that's Analog 5
// Connect YELLOW to i2c data (SDA) - on '168/'328 Arduino Uno/Duemilanove/etc that's Analog 4

Adafruit_AM2315 AM2315;

#define AM2315_DEBUG     true

Ethernet_Manager ethernet_manager;

IPAddress localEthernetIP;

// Use to detect W5100 shield. The linkStatus() is not working with W5100, only W5200 and W5500
// To check if W5100 using Ethernet and EthernetLarge libraries
bool isW5500 = true;

#define READ_INTERVAL        30000L          //read AM2315 interval 30s

void ReadData()
{
  static float temperature, humidity;

  if (!AM2315.readTemperatureAndHumidity(&temperature, &humidity))
  {
#if AM2315_DEBUG
    Serial.println(F("\nFailed to read data from AM2315"));
#endif

    return;
  }

#if AM2315_DEBUG
  Serial.print(F("\nTemp *C: "));
  Serial.print(String(temperature));
  Serial.print(F(", Humid %: "));
  Serial.println(String(humidity));
#endif
}

void heartBeatPrint()
{
  static int num        = 1;
  static int linkStatus = 0;
  
  localEthernetIP = Ethernet.localIP();
  
#if ( (USE_ETHERNET2 || USE_ETHERNET3) && !(USE_NATIVE_ETHERNET) )
  // To modify Ethernet2 library
  linkStatus = Ethernet.link();
  ET_LOGINFO3("localEthernetIP = ", localEthernetIP, ", linkStatus = ", (linkStatus == 1) ? "LinkON" : "LinkOFF" );
  
  if ( ( linkStatus == 1 ) && ((uint32_t) localEthernetIP != 0) )
#else

  // The linkStatus() is not working with W5100. Just using IP != 0.0.0.0
  // Better to use ping for W5100
  linkStatus = (int) Ethernet.linkStatus();
  ET_LOGINFO3("localEthernetIP = ", localEthernetIP, ", linkStatus = ", (linkStatus == LinkON) ? "LinkON" : "LinkOFF" );
  
  if ( ( (linkStatus == LinkON) || !isW5500 ) && ((uint32_t) localEthernetIP != 0) )
#endif
  {
    Serial.print(F("H"));
  }
  else
    Serial.print(F("F"));

  if (num == 80)
  {
    Serial.println();
    num = 1;
  }
  else if (num++ % 10 == 0)
  {
    Serial.print(F(" "));
  }
}

void check_status()
{
  #define STATUS_CHECK_INTERVAL     60000L
  
  static unsigned long checkstatus_timeout = STATUS_CHECK_INTERVAL;
  static unsigned long readData_timeout    = READ_INTERVAL;

  // ReadData every READ_INTERVAL (30) seconds: we don't need to read frequently.
  if (millis() > readData_timeout)
  {
    ReadData();
    readData_timeout = millis() + READ_INTERVAL;
  }
  
  // Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to send updates frequently if there is no status change.
  if (millis() > checkstatus_timeout)
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
  }
}

void initEthernet()
{
#if ( defined(USE_UIP_ETHERNET) && USE_UIP_ETHERNET )
  ET_LOGWARN(F("======== USE_UIP_ETHERNET ========"));
#elif USE_NATIVE_ETHERNET
  ET_LOGWARN(F("======== USE_NATIVE_ETHERNET ========"));
#elif USE_ETHERNET_GENERIC
  ET_LOGWARN(F("=========== USE_ETHERNET_GENERIC ==========="));
#elif USE_ETHERNET_ESP8266
  ET_LOGWARN(F("=========== USE_ETHERNET_ESP8266 ==========="));
#elif USE_ETHERNET_ENC
  ET_LOGWARN(F("=========== USE_ETHERNET_ENC ==========="));  
#else
  ET_LOGWARN(F("========================="));
#endif

  ET_LOGWARN(F("Default SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), MOSI);
  ET_LOGWARN1(F("MISO:"), MISO);
  ET_LOGWARN1(F("SCK:"),  SCK);
  ET_LOGWARN1(F("SS:"),   SS);
  ET_LOGWARN(F("========================="));

#if defined(ESP8266)

  #define PIN_D5            14        // Pin D5 mapped to pin GPIO14/HSCLK of ESP8266
  #define PIN_D6            12        // Pin D6 mapped to pin GPIO12/HMISO of ESP8266
  #define PIN_D7            13        // Pin D7 mapped to pin GPIO13/RXD2/HMOSI of ESP8266
  
  // Connection for ESP8266
  // MOSI: D7/GPIO13, MISO: D6/GPIO12, SCK: D5/GPIO14, CS/SS: D2/GPIO4
  
  // For ESP8266, change for other boards if necessary
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   D2    // For ESP8266
  #endif

  ET_LOGWARN1(F("ESP8266 setCsPin:"), USE_THIS_SS_PIN);

  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
    // For ESP8266
    // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
    // Ethernet           0                 X            X            X            X        0
    // Ethernet2          X                 X            X            X            X        0
    // Ethernet3          X                 X            X            X            X        0
    // EthernetLarge      X                 X            X            X            X        0
    // Ethernet_ESP8266   0                 0            0            0            0        0
    // D2 is safe to used for Ethernet, Ethernet2, Ethernet3, EthernetLarge libs
    // Must use library patch for Ethernet, EthernetLarge libraries
    Ethernet.init (USE_THIS_SS_PIN);

  #elif USE_CUSTOM_ETHERNET
  
    // You have to add initialization for your Custom Ethernet here
    // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
    Ethernet.init(USE_THIS_SS_PIN);
  
  #endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )

#elif defined(ESP32)

  #define PIN_D18           18        // Pin D18 mapped to pin GPIO18/VSPI_SCK of ESP32
  #define PIN_D19           19        // Pin D19 mapped to pin GPIO19/VSPI_MISO of ESP32
  #define PIN_D23           23        // Pin D23 mapped to pin GPIO23/VSPI_MOSI of ESP32
   
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // Connection for ESP32
  // MOSI: GPIO23, MISOP: GPIO19, SCK: GPIO18, CS/SS: GPIO22
  
  #ifndef USE_THIS_SS_PIN
    #define USING_M5STACK_W5500     false
    #if USING_M5STACK_W5500
      #warning Using M5Stack_Core_ESP32 with W5500 mudule
      #define USE_THIS_SS_PIN   26    // For M5Stack_Core_ESP32 with W5500 mudule
    #else
      #define USE_THIS_SS_PIN   22    // For ESP32
    #endif
  #endif

  ET_LOGWARN1(F("ESP32 setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
    // Must use library patch for Ethernet, EthernetLarge libraries
    // ESP32 => GPIO2,4,5,13,15,21,22 OK with Ethernet, Ethernet2, EthernetLarge
    // ESP32 => GPIO2,4,5,15,21,22 OK with Ethernet3
  
    //Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (USE_THIS_SS_PIN);
  
  #elif USE_CUSTOM_ETHERNET
  
    // You have to add initialization for your Custom Ethernet here
    // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
    Ethernet.init(USE_THIS_SS_PIN); 
  
  #endif  //( USE_ETHERNET_GENERIC || USE_ETHERNET_LARGE )

#else   //defined(ESP8266)
  // unknown board, do nothing, use default SS = 10
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   10    // For other boards
  #endif

  #if defined(BOARD_NAME)
    ET_LOGWARN3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);
  #else
    ET_LOGWARN1(F("Unknown board setCsPin:"), USE_THIS_SS_PIN);
  #endif

  // For other boards, to change if necessary
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC || USE_NATIVE_ETHERNET )
    // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries
  
    Ethernet.init (USE_THIS_SS_PIN);
  
  #elif USE_CUSTOM_ETHERNET
  
    // You have to add initialization for your Custom Ethernet here
    // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
    Ethernet.init(USE_THIS_SS_PIN);
    
  #endif  //( USE_ETHERNET_GENERIC || USE_ETHERNET_LARGE )

#endif    //defined(ESP8266)

  // Just info to know how to connect correctly
  #if defined(CUR_PIN_MISO)
    ET_LOGWARN(F("Currently Used SPI pinout:"));
    ET_LOGWARN1(F("MOSI:"), CUR_PIN_MOSI);
    ET_LOGWARN1(F("MISO:"), CUR_PIN_MISO);
    ET_LOGWARN1(F("SCK:"),  CUR_PIN_SCK);
    ET_LOGWARN1(F("SS:"),   CUR_PIN_SS);
  #else
    ET_LOGWARN(F("Currently Used SPI pinout:"));
    ET_LOGWARN1(F("MOSI:"), MOSI);
    ET_LOGWARN1(F("MISO:"), MISO);
    ET_LOGWARN1(F("SCK:"),  SCK);
    ET_LOGWARN1(F("SS:"),   SS);
  #endif
  
  ET_LOGWARN(F("========================="));
}

#if USING_CUSTOMS_STYLE
const char NewCustomsStyle[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}\
button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";
#endif

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  delay(200);

#if ( USE_LITTLEFS || USE_SPIFFS)
  Serial.println("\nStart AM2315_Ethernet using " + String(CurrentFileFS) + " on " + String(BOARD_NAME));
#else
  Serial.println("\nStart AM2315_Ethernet on " + String(BOARD_NAME));
#endif

  Serial.println("Ethernet Shield type : " + String(SHIELD_TYPE));
  Serial.println(ETHERNET_MANAGER_VERSION);
  
#if (ESP32 || ESP8266)
  Serial.println(ESP_DOUBLE_RESET_DETECTOR_VERSION);
#else  
  Serial.println(DOUBLERESETDETECTOR_GENERIC_VERSION);
#endif
  
  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card

  if (!AM2315.begin())
  {
    Serial.println(F("Sensor not found, check wiring & pullups!"));
  }

  initEthernet();

  //////////////////////////////////////////////
  
#if USING_CUSTOMS_STYLE
  ethernet_manager.setCustomsStyle(NewCustomsStyle);
#endif

#if USING_CUSTOMS_HEAD_ELEMENT
  ethernet_manager.setCustomsHeadElement("<style>html{filter: invert(10%);}</style>");
#endif

#if USING_CORS_FEATURE  
  ethernet_manager.setCORSHeader("Your Access-Control-Allow-Origin");
#endif

  ethernet_manager.begin();

  //////////////////////////////////////////////

  localEthernetIP = Ethernet.localIP();

  if ( (uint32_t) localEthernetIP != 0 )
  {
    Serial.print(F("Connected! IP address: "));
    Serial.println(localEthernetIP);
  }
  else
  {
    Serial.println(F("Ethernet not Connected! Please check."));
  }

  // Detect W5100 only in Ethernet and EthernetLarge libraries
#if (USE_ETHERNET_GENERIC)
  isW5500 = (Ethernet.hardwareStatus() == EthernetW5500);
  Serial.print(F("Ethernet type is "));
  Serial.println(isW5500 ? "W5500" : "W5100");
#endif
}

#if (USE_DYNAMIC_PARAMETERS)
void displayCredentials()
{
  Serial.println("\nYour stored Credentials :");

  for (int i = 0; i < NUM_MENU_ITEMS; i++)
  {
    Serial.println(String(myMenuItems[i].displayName) + " = " + myMenuItems[i].pdata);
  }
}

void displayCredentialsOnce()
{
  static bool displayedCredentials = false;

  if (!displayedCredentials)
  {
    for (int i = 0; i < NUM_MENU_ITEMS; i++)
    {
      if (!strlen(myMenuItems[i].pdata))
      {
        break;
      }

      if ( i == (NUM_MENU_ITEMS - 1) )
      {
        displayedCredentials = true;
        displayCredentials();
      }
    }
  }
}
#endif

void loop()
{
  ethernet_manager.run();
  
  check_status();

#if (USE_DYNAMIC_PARAMETERS)
  displayCredentialsOnce();
#endif  
}
