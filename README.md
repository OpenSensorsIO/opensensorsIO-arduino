# Arduino Client for OpenSensors

This is an OpenSensors client for Arduino boards with Ethernet or WiFi connectivity. It uses MQTT v3.1 and the [Arduino MQTT client](http://knolleary.net/arduino-client-for-mqtt/) by Nick O'Leary (MIT licensed).

## Hardware prerequisites

You need an Arduino board which has network interface (Ethernet wire or WiFi), for example, an [Arduino UNO](http://arduino.cc/en/Main/arduinoBoardUno) and [Arduino ethernet shield without PoE](http://store.arduino.cc/product/A000072), or a [single Arduino shield](http://arduino.cc/en/Main/ArduinoEthernetShield).

## Software prerequisites

[Arduino IDE](http://arduino.cc/en/main/software), the most convenient way to develop Arduino software.

## Using the Library

First import the Arduino MQTT client in Arduino IDE as a zip archive. Use "Sketch -> Import library -> Add library" in the IDE menu and point to pubsubclient.zip archive placed [here](./pubsubclient) and restart the IDE. 
 
Second import the client library for OpenSensors (it using previously imported library) in Arduino IDE as a zip archive. Therefore you need
to add to the zip archive files from the [osio_client directory](./osio_client).

Use "Sketch -> Import library -> Add library" in the IDE menu and point to created osio_client.zip archive
and restart the IDE. 

Then navigate to "Sketch -> Import library" and select "pubsubclient" and then "osio_client" from the dropdown list to add
the libraries to your Arduino program. Or you can do it in the code with

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
