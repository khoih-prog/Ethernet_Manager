/****************************************************************************************************************************
  MQTT_ThingStream_QNEthernet_Teensy.ino
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
  
  for (unsigned int i = 0; i < length; i++) 
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


void heartBeatPrint()
{
  static int num = 1;
  
  if (ethernet_manager.link_status())
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

void setup()
{
  // Debug console
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStarting MQTT_ThingStream_QNEthernet_Teensy on "); Serial.print(BOARD_NAME);
  Serial.print(" " ); Serial.println(SHIELD_TYPE);
  Serial.println(ETHERNET_MANAGER_VERSION);
  Serial.println(DOUBLERESETDETECTOR_GENERIC_VERSION);

#if USE_NATIVE_ETHERNET
  ET_LOGWARN(F("======== USE_NATIVE_ETHERNET ========"));
#elif USE_QN_ETHERNET
  ET_LOGWARN(F("=========== USE_QN_ETHERNET ==========="));
#else
  ET_LOGWARN(F("========================="));
#endif

#if USE_NATIVE_ETHERNET

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  Serial.println(F("========================="));

  Serial.print(F("Using mac index = "));
  Serial.println(index);

  Serial.print(F("Connected! IP address: "));
  Serial.println(Ethernet.localIP());

#else

  #if USING_DHCP
    // Start the Ethernet connection, using DHCP
    Serial.println("QNEthernet using DHCP");
  #else   
    // Start the Ethernet connection, using static IP
    Serial.println("QNEthernet using static IP"); 
  #endif
#endif
 
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
