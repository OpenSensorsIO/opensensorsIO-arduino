# Arduino Client for OpenSensors

This is the OpenSensors client for Arduino boards with Ethernet or WiFi connectivity. It uses MQTT v3.1 and the [Arduino MQTT client](http://knolleary.net/arduino-client-for-mqtt/) by Nick O'Leary (MIT licensed) as a dependency.

## Hardware prerequisites

You need an Arduino board with a network interface (Ethernet wire or WiFi), for example, an [Arduino UNO](http://arduino.cc/en/Main/arduinoBoardUno) and [Arduino ethernet shield without PoE](http://store.arduino.cc/product/A000072), or a [single Arduino shield](http://arduino.cc/en/Main/ArduinoEthernetShield).

## Software prerequisites

[Arduino IDE](http://arduino.cc/en/main/software) or another IDE, Codebender.cc etc.

## Using the Library

1. Download the [Arduino MQTT client](http://knolleary.net/arduino-client-for-mqtt/) dependency, created by Nick O'Leary, from [here](https://github.com/OpenSensorsIO/opensensorsIO-arduino/blob/master/bin/pubsubclient.zip).

2. Import the Arduino MQTT client file you just downloaded into the Arduino IDE. To do this we go to the Arduino IDE toolbar, go to Sketch -> Import Library -> Add library and add PubSubClient.zip

3. Restart the Arduino IDE

4. Download the OpenSensors Arduino Client from [here](https://github.com/OpenSensorsIO/opensensorsIO-arduino/blob/master/bin/osio_client.zip).

5. Import the OpenSensors Arduino Client into the Arduino IDE, mirroring step 2, add osio_client.zip

6. To implement in your sketch, you will need to now add the two libraries to your sketch. Navigate to Sketch -> Import library, select pubsubclient and then osio_client from the drop down list. Alternatively, type:

``` c
#include <pubsubclient.h>
#include <osio_client.h>
```

## Library reference

This client library realized as C++ class named **OSIOClient**. There are such public methods to work with it:

Constructors which initialize necessary connection parameters. There are some overrides of it ("server name" and "callback" parameters are not mandatory):

``` c
OSIOClient::OSIOClient(Client & client, char * userName, char * deviceId, char * devicePassword);
OSIOClient::OSIOClient(Client & client, char * userName, char * deviceId, char * devicePassword, char * serverName);
OSIOClient::OSIOClient(Client & client, char * userName, char * deviceId, char * devicePassword, void (*callback)(char*,uint8_t*,unsigned int));
OSIOClient::OSIOClient(Client & client, char * userName, char * deviceId, char * devicePassword, char * serverName, void (*callback)(char*,uint8_t*,unsigned int));
```

Method to process iteration of receiving data (callback supplied in constructor (if necessary)):

``` c
boolean OSIOClient::loop();
```

Method to publish message to topic:

``` c
boolean OSIOClient::publish(char* topic, char* payload);
```

Method to subscribe for topic:

``` c
boolean OSIOClient::subscribe(char* topic);
```

## Code Examples

Some examples can be found in the [sample directory](./sample).
