/* ATTENTION! Arduino WiFiClient for linux requires Arduino IDE version 1.0.2. Otherwise it does not works. */

#include <SPI.h>
#include <WiFi.h>            // In this sample we use wireless library.
#include <PubSubClient.h>    // Include library that supports mqtt protocol.
#include <osio_client.h>     // Include client library for OpenSensors.

// Callback for working with received messages.
void callback(char* topic, byte* payload, unsigned int length) 
{
  char* clearMessage = new char[length + 1];
  memset(clearMessage, 0, length + 1);
  memcpy(clearMessage, payload, length);
  
  Serial.print("Topic ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(clearMessage);
}

char ssid[] = "Poker Party";   // Name of my WIFI network.
WiFiClient wifiClient;         // Wireless client.

// Instance of client library class.
// Client (wired or wireless), user name, device ID, device password should be supplied.
// There are two optional parameters: callback (we need it is planning to read messages from topic),
// server name (opensensors.io by default).
// In this sample we supply callback and use default server name.
OSIOClient osioClient(wifiClient, "andreybarkanov", "105", "o7EM74is", callback);

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing...");
  
  if (WiFi.begin(ssid, "noleafclover") == WL_CONNECTED)
  { 
    if (osioClient.subscribe("/users/andreybarkanov/test"))
    {
      Serial.println("Subscribed for topic on the 'opensensors.io' server.");
    }
    else 
    {
      Serial.println("Could not subscribe for topic.");
    }
  } 
  else
  {
    Serial.println("DHCP error.");
  }
}

void loop()
{
  osioClient.loop();
}
