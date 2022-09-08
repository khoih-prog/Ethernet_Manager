/****************************************************************************************************************************
  Ethernet_RP2040.ino
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

Ethernet_Manager ethernet_manager;

IPAddress localEthernetIP;

void heartBeatPrint()
{
  static int num  = 1;
  
  localEthernetIP = ETH.localIP();
 
  if ( ( (uint32_t) localEthernetIP != 0 ) )
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
  #define STATUS_CHECK_INTERVAL     10000L
  
  static unsigned long checkstatus_timeout = STATUS_CHECK_INTERVAL;

  // Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to send updates frequently if there is no status change.
  if ((millis() > checkstatus_timeout))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
  }
}

#if USING_CUSTOMS_STYLE
const char NewCustomsStyle[] /*PROGMEM*/ = "<style>div,input{padding:5px;font-size:1em;}input{width:95%;}body{text-align: center;}\
button{background-color:blue;color:white;line-height:2.4rem;font-size:1.2rem;width:100%;}fieldset{border-radius:0.3rem;margin:0px;}</style>";
#endif

void WiFiEvent(WiFiEvent_t event)
{
#if ( ( defined(ESP_ARDUINO_VERSION_MAJOR) && (ESP_ARDUINO_VERSION_MAJOR >= 2) ) && ( ARDUINO_ESP32_GIT_VER != 0x46d5afb1 ) )
  //#warning Using ESP32 core v2.0.0+
  // Core v2.0.0+
 switch (event)
  {
    case SYSTEM_EVENT_ETH_START:
      ETM_LOGERROR(F("ETH Started"));
      //set eth hostname here
      ETH.setHostname("WT32-ETH01");
      break;
    case SYSTEM_EVENT_ETH_CONNECTED:
      ETM_LOGERROR(F("ETH Connected"));
      break;

    case SYSTEM_EVENT_ETH_GOT_IP:
      if (!ethernet_manager.isEthernetConnected())
      {
        ETM_LOGERROR3(F("ETH MAC:"), ETH.macAddress(), F(", IPv4:"), ETH.localIP());

        if (ETH.fullDuplex())
        {
          ETM_LOGERROR1(F("FULL_DUPLEX, Link Speed (Mbps)"), ETH.linkSpeed());
        }
        else
        {
          ETM_LOGERROR1(F("HALF_DUPLEX, Link Speed (Mbps)"), ETH.linkSpeed());
        }

        ethernet_manager.setEthernetConnected();
      }

      break;

    case SYSTEM_EVENT_ETH_DISCONNECTED:
      ETM_LOGERROR(F("ETH Disconnected"));
      ethernet_manager.setEthernetDisconnected();
      break;

    case SYSTEM_EVENT_ETH_STOP:
      ETM_LOGERROR(F("\nETH Stopped"));
      ethernet_manager.setEthernetDisconnected();
      break;

    default:
      break;
  }
  
#else

  //#warning Using ESP32 core v1.0.6-
  
  // Core v1.0.6-
  switch (event)
  {
    case SYSTEM_EVENT_ETH_START:
      ETM_LOGERROR(F("ETH Started"));
      //set eth hostname here
      ETH.setHostname("WT32-ETH01");
      break;
    case SYSTEM_EVENT_ETH_CONNECTED:
      ETM_LOGERROR(F("ETH Connected"));
      break;

    case SYSTEM_EVENT_ETH_GOT_IP:
      if (!ethernet_manager.isEthernetConnected())
      {
        ETM_LOGERROR3(F("ETH MAC:"), ETH.macAddress(), F(", IPv4:"), ETH.localIP());

        if (ETH.fullDuplex())
        {
          ETM_LOGERROR1(F("FULL_DUPLEX, Link Speed (Mbps)"), ETH.linkSpeed());
        }
        else
        {
          ETM_LOGERROR1(F("HALF_DUPLEX, Link Speed (Mbps)"), ETH.linkSpeed());
        }

        ethernet_manager.setEthernetConnected();
      }

      break;

    case SYSTEM_EVENT_ETH_DISCONNECTED:
      ETM_LOGERROR(F("ETH Disconnected"));
      ethernet_manager.setEthernetDisconnected();
      break;

    case SYSTEM_EVENT_ETH_STOP:
      ETM_LOGERROR(F("\nETH Stopped"));
      ethernet_manager.setEthernetDisconnected();
      break;

    default:
      break;
  }
#endif  
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  //while (!Serial);

  // Using this if Serial debugging is not necessary or not using Serial port
  while (!Serial && (millis() < 5000));

  Serial.print("\nStart Ethernet_WT32_ETH01 on "); Serial.println(BOARD_NAME); 
  Serial.print("Ethernet Shield type : "); Serial.println(SHIELD_TYPE);
  Serial.println(WEBSERVER_WT32_ETH01_VERSION);
  Serial.println(ETHERNET_MANAGER_VERSION);
  Serial.println(ESP_DOUBLE_RESET_DETECTOR_VERSION);

  WiFi.onEvent(WiFiEvent);

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

  localEthernetIP = ETH.localIP();

  if ( (uint32_t) localEthernetIP != 0 )
  {
    Serial.print(F("Connected! IP address: "));
    Serial.println(localEthernetIP);
  }
  else
  {
    Serial.println(F("Ethernet not Connected! Please check."));
  }
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
