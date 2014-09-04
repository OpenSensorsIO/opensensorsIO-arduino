/*
 * Insertion to test publish for topic.
 * Command line to listen test message: mosquitto_sub -i asqv8fs0moo0kv7mknev9 -u yods -P device-2-pwd -t yods/device1/sensor1"
 */

#include <SPI.h>
#include <Ethernet.h>
#include <mqtt.h>

// "Data received" handler. It's empty, in this sample we
// don't want to read any data.
void callback(char* topic, byte* payload, unsigned int length) 
{
}

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xF3, 0xDF };  // MAC address of my "Arduino ethernet" shield.
byte server[] = { 192, 168, 1, 4 };                   // IP of server with azondi configured.
byte ip[] = { 192, 168, 1, 3 };                       // "Arduino ethernet" shield IP (for case when DHCP resolving fails).
int port = 1883;                                      // We use 1883 port by default.
EthernetClient ethernetClient;                        // Standart arduino ethernet client (need to work with MQTT helper).
long unsigned int lowIn;                              // The time when the sensor outputs a low impulse.
long unsigned int pause = 2000;                       // The amount of milliseconds the sensor has to be low before we assume all motion has stopped.
boolean lockLow = true;                               // Current state is "no motion".
boolean takeLowTime;                                  // Need to save time of transition from HIGH to LOW.

// MQTT worker instance. As a parameters we pass server, port, 
// "data received" callback and instance of EthernetClient.
MQTTClient mqttClient(server, port, callback, ethernetClient);

void setup()
{
  pinMode(3, INPUT);  // We connect infrared motion sensor on this pin and will read signal from it.
  pinMode(8, OUTPUT); // We will write signal to 8 pin.
  
  Serial.begin(9600);
  Serial.println("Initializing...");
  
  // Give some time to infrared sensor to make room snapshot.
  Serial.println("Calibrating sensor");
  for(int i = 0; i < 5; i++)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Done.");
    
  if (Ethernet.begin(mac) == 0) 
  {
    Serial.println("Cannot configure with DHCP.");
    Ethernet.begin(mac, ip);
  }
  
  Serial.print("Got IP adress: ");
  Serial.println(Ethernet.localIP()); // Arduino shield IP.
  
  // Here we pass authentication parameters from Azondi repository.
  // mqttClient.connect("<client id>", "<user name>", "<password>").
  if (mqttClient.connect("3221e1gltf8vlofaf6to", "yods", "device-1-pwd")) 
  {
    Serial.println("Connected to MQTT.");
    digitalWrite(8, HIGH);
  }
  else 
  {
    Serial.println("Cannot connect to MQTT.");
    digitalWrite(8, LOW);
  }
}

void loop()
{
  char message[255];
  char time[50];
      
  if (digitalRead(3) == HIGH) // Motion detected.
  {
    if (lockLow)
    {
      lockLow = false;
      
      memset(message, 0, 255);
      memset(time, 0, 50);
      
      if (ethernetClient.connected())
      {
        strcpy(message, "Motion detected at ");
        itoa(millis() / 1000, time, 10);
        strcat(message, time);
        strcat(message, " seconds from arduino startup.");
        mqttClient.publish("yods/device1/sensor1", message);
      }
      else
      {
        ethernetClient.stop();
        digitalWrite(8, LOW);
      }  
      
      delay(50);
    }
    
    takeLowTime = true;
  }
  else // No motion.
  {
    if (takeLowTime)
    {
      lowIn = millis();
      takeLowTime = false;
    }
    
    if(lockLow == false && millis() - lowIn > pause)
    {  
      lockLow = true;                        
      
      if (ethernetClient.connected())
      {
        strcpy(message, "Motion ended at ");
        itoa((millis() - pause) / 1000, time, 10);
        strcat(message, time);
        strcat(message, " seconds from arduino startup.");
        mqttClient.publish("yods/device1/sensor1", message);
      }
      else
      {
        ethernetClient.stop();
        digitalWrite(8, LOW);
      }  

      delay(50);
    }
  }  
}
