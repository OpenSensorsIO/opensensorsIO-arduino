/*
 * Insertion to test subscribe for topic.
 * Command line to publish test message: mosquitto_pub -i asqv8fs0moo0kv7mknev9 -u yods -P device-2-pwd -t yods/device1/sensor1 -m "How are you?"
 */

#include <SPI.h>
#include <Ethernet.h>
#include <mqtt.h>

// "Data received" handler.
void callback(char* topic, byte* payload, unsigned int length) 
{
  //int payloadLength = strlen((char*)payload);
  char* clearMessage = new char[length + 1];
  memset(clearMessage, 0, length + 1);
  memcpy(clearMessage, payload, length);
  
  Serial.print("Topic ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(clearMessage);
}

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xF3, 0xDF };  // MAC address of my "Arduino ethernet" shield.
byte server[] = { 192, 168, 1, 4 };                   // IP of server with azondi configured.
byte ip[] = { 192, 168, 1, 3 };                       // "Arduino ethernet" shield IP (for case when DHCP resolving fails).
int port = 1883;                                      // We use 1883 port by default.
EthernetClient ethernetClient;                        // Standart arduino ethernet client (need to work with MQTT helper).

// MQTT worker instance. As a parameters we pass server, port, 
// "data received" callback and instance of EthernetClient.
MQTTClient mqttClient(server, port, callback, ethernetClient);

void setup()
{
  delay(5000); // Pause to open serial debug console.
  Serial.begin(9600);
  Serial.println("Initializing...");
  
  if (Ethernet.begin(mac) == 0) 
  {
    Serial.println("Cannot configure with DHCP.");
    Ethernet.begin(mac, ip);
  }
  
  Serial.print("Got IP adress: ");
  Serial.println(Ethernet.localIP()); // Arduino shield IP.
  
  // Here we pass authentication parameters from Azondi repository
  // mqttClient.connect("<client id>", "<user name>", "<password>")
  if (mqttClient.connect("3221e1gltf8vlofaf6to", "yods", "device-1-pwd")) 
  {
    Serial.println("Connected to MQTT.");
    
    // Subscribe for topic.
    mqttClient.subscribe("yods/device1/sensor1");
  }
  else 
  {
    Serial.println("Cannot connect to MQTT.");
  }
}

void loop()
{
  if (ethernetClient.connected())
  {
    mqttClient.loop();
  }
  else
  {
    ethernetClient.stop();
  }
}
