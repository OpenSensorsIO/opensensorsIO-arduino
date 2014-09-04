# MQTT plugin for "Arduino" IDE

This library gives ability to communicate with server via MQTT protocol to **Arduino** network shields. API consists of set of methods to connect to the server, subscribe for topic and publish to topic. Original code taken from [here](http://knolleary.net/arduino-client-for-mqtt/). Currently only class and files were renamed.

## Hardware prerequisites

You need any arduino shield which has network interface (cable or WIFI). In my case I used combination of [Arduino UNO](http://arduino.cc/en/Main/arduinoBoardUno) and [Arduino ethernet shield without PoE](http://store.arduino.cc/product/A000072). But this variant cn be replaces by [single shield](http://arduino.cc/en/Main/ArduinoEthernetShield). Also [data cable](http://www.adafruit.com/products/62) is necessary for programming shield. It's in any arduino shield box usually.

## Software prerequisites

To develop arduino programs, connect and use MQTT plugin you need [Arduino IDE](http://arduino.cc/en/main/software), downloaded for your OS.

## Using MQTT plugin

Before you can use plugin you must to import it in your Arduino IDE. Plugins importing as zip archives. Therefore you need to add to zip archive files which placed in [plugin folder](https://github.com/OpenSensorsIO/opensensorsIO-arduino/tree/master/mqtt). Next select: "Sketch -> Import library -> Add library" in your IDE and point to created mqtt.zip archive. After it restart your IDE. You need go to "Sketch -> Import library" and select "mqtt" from dropdown list to include plugin to your arduino program. Or you can do it manually by typing **#include <mqtt.h>**.

## Explore samples

Some samples of using MQTT arduino plugin you can found [here](https://github.com/OpenSensorsIO/opensensorsIO-arduino/tree/master/sample).
