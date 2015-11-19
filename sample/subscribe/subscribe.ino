#include <SPI.h>
#include <Ethernet.h>        // In this sample we use wired ethernet library.
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

// MAC of arduino ethernet shield.
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xF3, 0xDF };

// Wired ethernet client.
EthernetClient ethernetClient;

// Instance of client library class.
// Client (wired or wireless), user name, device ID, device password should be supplied.
// There are two optional parameters: callback (we need it is planning to read messages from topic),
// server name (mqtt.opensensors.io by default).
// In this sample we supply callback and use default server name.
OSIOClient osioClient(ethernetClient, "gizz", "80", "EFxXoD2m", callback);

void setup()
{
  Serial.begin(9600);
  Serial.println("Initializing...");
  
  if (Ethernet.begin(mac) != 0)
  {
    if (osioClient.subscribe("/users/gizz/test")) 
    {
      Serial.println("Subscribed for topic on the 'mqtt.opensensors.io' server.");
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
