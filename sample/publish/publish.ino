#include <SPI.h>
#include <Ethernet.h>
#include <osio_client.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xF3, 0xDF };  // MAC address of my "Arduino ethernet" shield.
long unsigned int lowIn;                              // The time when the sensor outputs a low impulse.
long unsigned int pause = 2000;                       // The amount of milliseconds the sensor has to be low before we assume all motion has stopped.
boolean lockLow = true;                               // Current state is "no motion".
boolean takeLowTime;                                  // Need to save time of transition from HIGH to LOW.

OSIOClient osioClient;

void setup()
{
  pinMode(3, INPUT);  // We connect infrared motion sensor on this pin and will read signal from it.
  
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
  else
  {
    if (osioClient.connect("opensensors.io", "gizz", "80", "EFxXoD2m")) 
    {
      Serial.println("Connected to opensensors.io.");
    }
    else 
    {
      Serial.println("Cannot connect to opensensors.io.");
    }
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
      
      if (osioClient.connected())
      {
        Serial.println("motion...");
        strcpy(message, "Motion detected at ");
        itoa(millis() / 1000, time, 10);
        strcat(message, time);
        strcat(message, " seconds from arduino startup.");
        osioClient.publish("/users/gizz/test", message);
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
      
      if (osioClient.connected())
      {
        strcpy(message, "Motion ended at ");
        itoa((millis() - pause) / 1000, time, 10);
        strcat(message, time);
        strcat(message, " seconds from arduino startup.");
        osioClient.publish("/users/gizz/test", message);
      }

      delay(50);
    }
  }  
}
