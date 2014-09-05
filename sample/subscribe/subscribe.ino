#include <SPI.h>
#include <Ethernet.h>
#include <osio_client.h>

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

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xF3, 0xDF };  
OSIOClient osioClient;

void setup()
{
  delay(5000); 
  Serial.begin(9600);
  Serial.println("Initializing...");
  
  if (Ethernet.begin(mac) != 0)
  {
    // Here we connect without server name ("opensensors.oi" used by default).
    if (osioClient.connect("gizz", "80", "EFxXoD2m")) 
    {
      Serial.println("Connected to opensensors.io.");
      osioClient.subscribe("/users/gizz/test", callback);
    }
    else 
    {
      Serial.println("Cannot connect to opensensors.io.");
    }
  } 
  else
  {
    Serial.println("DHCP error.");
  }
}

void loop()
{
  if (osioClient.connected())
  {
    osioClient.loop();
  }
}
