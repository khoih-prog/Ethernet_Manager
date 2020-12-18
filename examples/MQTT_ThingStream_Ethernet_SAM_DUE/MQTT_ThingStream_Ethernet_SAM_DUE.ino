/****************************************************************************************************************************
  MQTT_ThingStream_Ethernet_SAM_DUE.ino
  For W5x00 and ENC28J60 Ethernet shields.

  Ethernet_Manager is a library for nRF52, Teensy, STM32, SAM DUE and SAMD boards, with Ethernet W5x00 or ENC28J60 shields,
  to enable easy configuration/reconfiguration of Credentials and autoconnect/autoreconnect of Ethernet.
  AVR Mega is not supported.

  Built by Khoi Hoang https://github.com/khoih-prog/Ethernet_Manager
  Licensed under MIT license
 *****************************************************************************************************************************/

#include "defines.h"
#include "Credentials.h"
#include "dynamicParams.h"

///////////// Start MQTT ThingStream ///////////////
#include <PubSubClient.h>

// GOT FROM ThingsStream!

const char *MQTT_PREFIX_TOPIC   = "esp32-sniffer/";
const char *MQTT_ANNOUNCE_TOPIC = "/status";
const char *MQTT_CONTROL_TOPIC  = "/control";
const char *MQTT_BLE_TOPIC      = "/ble";

String topic    = MQTT_PREFIX_TOPIC + String("12345678") + MQTT_BLE_TOPIC;
String subTopic = MQTT_PREFIX_TOPIC + String("12345678") + MQTT_BLE_TOPIC;

//////////// End MQTT ThingStream ///////////////

Ethernet_Manager ethernet_manager;

IPAddress localEthernetIP;


///////////// Start MQTT ThingStream ///////////////

void mqtt_receive_callback(char* topic, byte* payload, unsigned int length);

unsigned long lastMsg = 0;

// Initialize the SSL client library
// Arguments: EthernetClient, our trust anchors


EthernetClient    ethClient;

PubSubClient* client = NULL;

/*
   Called whenever a payload is received from a subscribed MQTT topic
*/
void mqtt_receive_callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("\nMQTT Message receive [");
  Serial.print(topic);
  Serial.print("] ");
  
  for (int i = 0; i < length; i++) 
  {
    Serial.print((char)payload[i]);
  }
  
  Serial.println();
}

void reconnect() 
{
  // Loop until we're reconnected
  while (!client->connected()) 
  {
    Serial.print("Attempting MQTT connection to ");
    Serial.println(MQTT_SERVER);

    // Attempt to connect

    int connect_status = client->connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS, topic.c_str(), 2, false, "");

    if (connect_status)                                
    {
      Serial.println("...connected");
      
      // Once connected, publish an announcement...
      String data = "Hello from MQTTClient_SSL on " + String(BOARD_NAME);

      client->publish(topic.c_str(), data.c_str());

      Serial.println("Published connection message successfully!");
     
      Serial.print("Subcribed to: ");
      Serial.println(subTopic);
      
      // ... and resubscribe
      client->subscribe(subTopic.c_str());
      // for loopback testing
      client->subscribe(topic.c_str());
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client->state());
      Serial.println(" try again in 5 seconds");
      
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

///////////// End MQTT ThingStream ///////////////

// Use to detect W5100 shield. The linkStatus() is not working with W5100 
// in Ethernet and EthernetLarge libraries
bool isW5500 = true;

void heartBeatPrint()
{
  static int num        = 1;
  static int linkStatus = 0;
  
  localEthernetIP = Ethernet.localIP();
  
#if (USE_ETHERNET2 || USE_ETHERNET3)
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
  #define STATUS_CHECK_INTERVAL     10000L
  
  static unsigned long checkstatus_timeout = STATUS_CHECK_INTERVAL;

  // Send status report every STATUS_REPORT_INTERVAL (60) seconds: we don't need to send updates frequently if there is no status change.
  if ((millis() > checkstatus_timeout))
  {
    heartBeatPrint();
    checkstatus_timeout = millis() + STATUS_CHECK_INTERVAL;
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\nStart MQTT_ThingStream_Ethernet_SAM_DUE on " + String(BOARD_NAME)); 
  Serial.println("Ethernet Shield type : " + String(SHIELD_TYPE));
  Serial.println(ETHERNET_MANAGER_VERSION);

  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH); // Deselect the SD card
  
#if USE_ETHERNET_WRAPPER

  EthernetInit();

#else

  #if ( defined(USE_UIP_ETHERNET) && USE_UIP_ETHERNET )
    ET_LOGWARN(F("======== USE_UIP_ETHERNET ========"));
  #elif USE_NATIVE_ETHERNET
    ET_LOGWARN(F("======== USE_NATIVE_ETHERNET ========"));
  #elif USE_ETHERNET
    ET_LOGWARN(F("=========== USE_ETHERNET ==========="));
  #elif USE_ETHERNET2
    ET_LOGWARN(F("=========== USE_ETHERNET2 ==========="));
  #elif USE_ETHERNET3
    ET_LOGWARN(F("=========== USE_ETHERNET3 ==========="));
  #elif USE_ETHERNET_LARGE
    ET_LOGWARN(F("=========== USE_ETHERNET_LARGE ==========="));
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
  #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2  || USE_ETHERNET_ENC || USE_NATIVE_ETHERNET )
    // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries
  
    Ethernet.init (USE_THIS_SS_PIN);
  
  #elif USE_ETHERNET3
    // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
    #ifndef ETHERNET3_MAX_SOCK_NUM
      #define ETHERNET3_MAX_SOCK_NUM      4
    #endif
  
    Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
  
  #elif USE_CUSTOM_ETHERNET
  
    // You have to add initialization for your Custom Ethernet here
    // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
    Ethernet.init(USE_THIS_SS_PIN);
    
  #endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )
  
#endif  //USE_ETHERNET_WRAPPER

  // Just info to know how to connect correctly
  ET_LOGWARN(F("========================="));
  ET_LOGWARN(F("Currently Used SPI pinout:"));
  ET_LOGWARN1(F("MOSI:"), MOSI);
  ET_LOGWARN1(F("MISO:"), MISO);
  ET_LOGWARN1(F("SCK:"), SCK);
  ET_LOGWARN1(F("SS:"), SS);
  
#if USE_ETHERNET3
  ET_LOGWARN1(F("SPI_CS:"), SPI_CS);
#endif
  ET_LOGWARN(F("========================="));
 
  ethernet_manager.begin();

  localEthernetIP = Ethernet.localIP();

#if (USE_ETHERNET2 || USE_ETHERNET3)
  // To modify Ethernet2 library
  if ( (uint32_t) localEthernetIP != 0 )
#else
  if ( (uint32_t) localEthernetIP != 0 )
#endif
  {
    Serial.print(F("Connected! IP address: "));
    Serial.println(localEthernetIP);
  }
  else
  {
    Serial.println(F("Ethernet not Connected! Please check."));
  }

// Detect W5100 only in Ethernet and EthernetLarge libraries
#if ( USE_ETHERNET || USE_ETHERNET_LARGE)
  isW5500 = (Ethernet.hardwareStatus() == EthernetW5500);
  Serial.print(F("Ethernet type is "));
  Serial.println(isW5500 ? "W5500" : "W5100");
#endif
  
  Serial.println("***************************************");
  Serial.println(topic);
  Serial.println("***************************************");
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

#define MQTT_PUBLISH_INTERVAL_MS      20000L

String data         = "Hello from MQTT_ThingStream on " + String(BOARD_NAME) + " with " + String(SHIELD_TYPE);
const char *pubData = data.c_str();

void loop()
{
  static bool           inConfigMode = true;
  static unsigned long  currentMillis;

  
  inConfigMode = ethernet_manager.run();

  if (!inConfigMode)
  {
    if (!client)
    {
       client = new PubSubClient(MQTT_SERVER, atoi(MQTT_PORT), mqtt_receive_callback, ethClient);

      // Note - the default maximum packet size is 256 bytes. If the
      // combined length of clientId, username and password exceed this use the
      // following to increase the buffer size:
      //client->setBufferSize(256);
    }
    
    if (!client->connected()) 
    {
      reconnect();
    }
  
    // Sending Data
    currentMillis = millis();
    
    if (currentMillis - lastMsg > MQTT_PUBLISH_INTERVAL_MS)
    {
      lastMsg = currentMillis;
  
      if (!client->publish(topic.c_str(), pubData))
      {
        Serial.println("Message failed to send.");
      }
  
      Serial.print("\nMQTT Message Send : " + topic + " => ");
      Serial.println(data);
    }
    
    client->loop();
    
    check_status();
  
  #if (USE_DYNAMIC_PARAMETERS)
    displayCredentialsOnce();
  #endif
  }
}
