
# ESP8266 Software Serial Beacon


## TL;DR
Send's predefined data via software defined 2nd serial device at
configurable speed and every configurable x seconds. Useful as
simulator when working on projects which are reading from serial.

## Introduction
When working on an ESP32 based project to read sml data from a
smartmeter, I couldn't find out why the ... the ESP32 didn't read
any bytes from serial input. To check my code, I took a spare
ESP8266 and built this simulator which sends out the same sml data
every five seconds. This way I found out that my code was OK but
the cable eventually got broken...

## Configuration
You may reconfigure the code to send out whatever data you need.
Please make sure you define it in the variable ser_data as hexadecimal
values, all in UPPERcase letters.

These are the main parameters to fiddle with:
* SLEEP - time in microseconds between the beacons
* BAUD1 - baud rate for default serial (means debug via USB)
* BAUD2 - baud rate for addtl. software serial device
* RXPIN - GPIO pin for reading data on softserial device
* TXPIN - GPIO pin for sending data on softserial device

## Caution with software serial
Many people report software serial to be unstable when used together
with wifi or bluetooth which I can confirm. Recently I tried to use
an ESP8266 for reading data via software serial and sending it to
a database by wifi. The ESP8266 restarted now and then, in time spans
of a few minutes up to an hour. Sometimes it mixed up up the incoming
bits, delivering wrong values. So I don't recommend using ESP8266
with software serial in production. Use ESP32 instead which has three
hardware serial devices.

