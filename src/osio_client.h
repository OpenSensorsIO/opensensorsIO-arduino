#ifndef osio_client_h
#define osio_client_h

#include <Arduino.h>
#include "Client.h"
#include "PubSubClient.h"

// Default MQTT port - Use port 8883 for TLS secure messaging
#define MQTT_PORT 1883

// Default server name
#define OSIO_SERVERNAME "mqtt.opensensors.io"

class OSIOClient 
{
private:
  PubSubClient * _mqttClient;
  char * _userName;
  char * _deviceId;
  char * _devicePassword;
  boolean _authenticatedInServer;
  boolean connectIfNecessary();
  void initialize(Client & client, char * userName, char * deviceId, char * devicePassword, char * serverName, void (*callback)(char*,uint8_t*,unsigned int));
public:
  OSIOClient(Client & client, char * userName, char * deviceId, char * devicePassword); 
  OSIOClient(Client & client, char * userName, char * deviceId, char * devicePassword, char * serverName);
  OSIOClient(Client & client, char * userName, char * deviceId, char * devicePassword, void (*callback)(char*,uint8_t*,unsigned int));
  OSIOClient(Client & client, char * userName, char * deviceId, char * devicePassword, char * serverName, void (*callback)(char*,uint8_t*,unsigned int));
  ~OSIOClient();
  boolean publish(char * topic, char * payload);
  boolean subscribe(char * topic);
  boolean loop();
};

#endif
