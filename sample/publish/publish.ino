#include <SPI.h>
#include <Ethernet.h>        // In this sample we use wired ethernet library.
#include <PubSubClient.h>    // Include library that supports mqtt protocol.
#include <osio_client.h>     // Include client library for OpenSensors.

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xF3, 0xDF };  // MAC address of my "Arduino ethernet" shield.
long unsigned int lowIn;                              // The time when the sensor outputs a low impulse.
long unsigned int pause = 2000;                       // The amount of milliseconds the sensor has to be low before we assume all motion has stopped.
boolean lockLow = true;                               // Current state is "no motion".
boolean takeLowTime;                                  // Need to save time of transition from HIGH to LOW.

// Wired ethernet client.
EthernetClient ethernetClient;

// Instance of client library class.
// Client (wired or wireless), user name, device ID, device password should be supplied.
// There are two optional parameters: callback (we need it is planning to read messages from topic),
// server name (mqtt.opensensors.io by default).
// In this sample don't need to supply callback and use default server name.
OSIOClient osioClient(ethernetClient, "gizz", "80", "EFxXoD2m");

void setup()
{
  // We connect infrared motion sensor on this pin and will read signal from it.
  pinMode(3, INPUT);
  
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
    Serial.println("DHCP error.");
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
      
      Serial.println("motion...");
      strcpy(message, "Motion detected at ");
      itoa(millis() / 1000, time, 10);
      strcat(message, time);
      strcat(message, " seconds from arduino startup.");
      if (osioClient.publish("/users/gizz/test", message))
      {
        Serial.println("Begin motion: message published.");
      }
      else
      {
        Serial.println("Begin motion: error publishing message.");
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
      
      strcpy(message, "Motion ended at ");
      itoa((millis() - pause) / 1000, time, 10);
      strcat(message, time);
      strcat(message, " seconds from arduino startup.");
      
      if (osioClient.publish("/users/gizz/test", message))
      {
        Serial.println("Stop motion: message published.");
      }
      else
      {
        Serial.println("Stop motion: error publishing message.");
      }  

      delay(50);
    }
  }  
}
