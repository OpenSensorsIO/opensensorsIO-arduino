#include "osio_client.h"
#include <string.h>

OSIOClient::OSIOClient(Client & client, char * userName, char * deviceId, char * devicePassword)
{
  this->initialize(client, userName, deviceId, devicePassword, OSIO_SERVERNAME, 0);
}

OSIOClient::OSIOClient(Client & client, char * userName, char * deviceId, char * devicePassword, char * serverName)
{
  this->initialize(client, userName, deviceId, devicePassword, serverName, 0);  
}

OSIOClient::OSIOClient(Client & client, char * userName, char * deviceId, char * devicePassword, void (*callback)(char*,uint8_t*,unsigned int))
{
  this->initialize(client, userName, deviceId, devicePassword, OSIO_SERVERNAME, callback);  
}

OSIOClient::OSIOClient(Client & client, char * userName, char * deviceId, char * devicePassword, char * serverName, void (*callback)(char*,uint8_t*,unsigned int))
{
  this->initialize(client, userName, deviceId, devicePassword, serverName, callback);  
}

void OSIOClient::initialize(Client & client, char * userName, char * deviceId, char * devicePassword, char * serverName, void (*callback)(char*,uint8_t*,unsigned int))
{
  this->_mqttClient = new PubSubClient(serverName, MQTT_PORT, callback, client);
  this->_userName = userName;
  this->_deviceId = deviceId;
  this->_devicePassword = devicePassword;
  this->_authenticatedInServer = false;
}

OSIOClient::~OSIOClient()
{
  this->_mqttClient->disconnect();
  delete this->_mqttClient;
}

boolean OSIOClient::connectIfNecessary()
{
  if (this->_mqttClient->connected() && this->_authenticatedInServer)
  {
    return true;
  }

  boolean result = this->_mqttClient->connect(this->_deviceId, this->_userName, this->_devicePassword);
  this->_authenticatedInServer = result;
  return result;
}

boolean OSIOClient::loop() 
{
  this->_mqttClient->loop();
}

boolean OSIOClient::publish(char* topic, char* payload) 
{
  if (!this->connectIfNecessary())
  {
    return false;
  }
  return this->_mqttClient->publish(topic, payload);
}

boolean OSIOClient::subscribe(char* topic)
{
  if (!this->connectIfNecessary())
  {
    return false;
  }
  return this->_mqttClient->subscribe(topic);
}
