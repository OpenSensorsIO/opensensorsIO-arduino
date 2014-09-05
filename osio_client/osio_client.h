#ifndef osio_client_h
#define osio_client_h

#include <Arduino.h>
#include "Client.h"
#include "PubSubClient.h"

// Default MQTT port
#define MQTT_PORT 1883

// Default server name
#define OSIO_SERVERNAME "opensensors.io"

class OSIOClient 
{
private:
  PubSubClient * _mqttClient;
  Client * _client;
  char * _serverName;
  char * _userName;
  char * _deviceId;
  char * _devicePassword;
  boolean authenticatedInServer;
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
