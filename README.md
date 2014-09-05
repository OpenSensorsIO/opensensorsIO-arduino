# Arduino Client for OpenSensors

This is an OpenSensors client for Arduino boards with Ethernet or WiFi connectivity. It uses MQTT v3.1 and is based
on the [Arduino MQTT client](http://knolleary.net/arduino-client-for-mqtt/) by Nick O'Leary (MIT licensed).

## Hardware prerequisites

You need an Arduino board which has network interface (Ethernet wire or WiFi), for example, an [Arduino UNO](http://arduino.cc/en/Main/arduinoBoardUno) and [Arduino ethernet shield without PoE](http://store.arduino.cc/product/A000072), or a [single Arduino shield](http://arduino.cc/en/Main/ArduinoEthernetShield).

## Software prerequisites

[Arduino IDE](http://arduino.cc/en/main/software), the most convenient way to develop Arduino software.

## Using the Library

First import the library in Arduino IDE as a zip archive. Therefore you need
to add to the zip archive files from the [mqtt directory](./osio_client).

The use "Sketch -> Import library -> Add library" in the IDE menu and point to created mqtt.zip archive
and restart the IDE. 

Then navigate to "Sketch -> Import library" and select "osio_client" from the dropdown list to add
the library to your Arduino program. Or you can do it in the code with

``` c
#include <mqtt.h>
```

## Library reference

This client library realized as C++ class named **OSIOClient**. There are such public methods to work with it:


## Code Examples

Some examples can be found in the [sample directory](./sample).
