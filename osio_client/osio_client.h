#ifndef osio_client_h
#define osio_client_h

#include <Arduino.h>
#include "SPI.h"
#include "Ethernet.h"

// Default MQTT port
#define MQTT_PORT 1883

// Default server name
#define OSIO_SERVERNAME "opensensors.io"

// MQTT_MAX_PACKET_SIZE : Maximum packet size
#define MQTT_MAX_PACKET_SIZE 128

// MQTT_KEEPALIVE : keepAlive interval in Seconds
#define MQTT_KEEPALIVE 15

#define MQTTPROTOCOLVERSION 3
#define MQTTCONNECT     1 << 4  // Client request to connect to Server
#define MQTTCONNACK     2 << 4  // Connect Acknowledgment
#define MQTTPUBLISH     3 << 4  // Publish message
#define MQTTPUBACK      4 << 4  // Publish Acknowledgment
#define MQTTPUBREC      5 << 4  // Publish Received (assured delivery part 1)
#define MQTTPUBREL      6 << 4  // Publish Release (assured delivery part 2)
#define MQTTPUBCOMP     7 << 4  // Publish Complete (assured delivery part 3)
#define MQTTSUBSCRIBE   8 << 4  // Client Subscribe request
#define MQTTSUBACK      9 << 4  // Subscribe Acknowledgment
#define MQTTUNSUBSCRIBE 10 << 4 // Client Unsubscribe request
#define MQTTUNSUBACK    11 << 4 // Unsubscribe Acknowledgment
#define MQTTPINGREQ     12 << 4 // PING Request
#define MQTTPINGRESP    13 << 4 // PING Response
#define MQTTDISCONNECT  14 << 4 // Client is Disconnecting
#define MQTTReserved    15 << 4 // Reserved

#define MQTTQOS0        (0 << 1)
#define MQTTQOS1        (1 << 1)
#define MQTTQOS2        (2 << 1)

class OSIOClient 
{
private:
  EthernetClient * _client;
  uint8_t buffer[MQTT_MAX_PACKET_SIZE];
  uint16_t nextMsgId;
  unsigned long lastOutActivity;
  unsigned long lastInActivity;
  bool pingOutstanding;
  void (*callback)(char*,uint8_t*,unsigned int);
  uint16_t readPacket();
  uint8_t readByte();
  boolean write(uint8_t header, uint8_t* buf, uint16_t length);
  uint16_t writeString(char* string, uint8_t* buf, uint16_t pos);
  boolean connect(char * serverName, char *, char *, char *, char *, uint8_t, uint8_t, char*);
  boolean publish(char * topic, uint8_t * payload, unsigned int length, boolean retained);
  boolean publish_P(char * topic, uint8_t PROGMEM * payload, unsigned int length, boolean retained);
public:
  OSIOClient();
  boolean connect(char * userName, char * deviceId, char * devicePassword);
  boolean connect(char * serverName, char * userName, char * deviceId, char * devicePassword);
  void disconnect();
  boolean publish(char * topic, char * payload);
  boolean subscribe(char * topic, void (*callback)(char*,uint8_t*,unsigned int));
  boolean loop();
  boolean connected();
};

#endif
