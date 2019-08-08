
# ESP8266 Software Serial Beacon

## TL;DR
Sendet vordefinierte Daten über eine zweite serielle Schnittstelle.
Geschwindigkeit und Wiederholrate sind konfigurierbar. Nützlich 
als Simulator beim Arbeiten an Projekten, die über eine serielle
Schnittstelle Daten lesen sollen.

## Einleitung
Bei der Arbeit an einem Projekt, in welchem SML-Daten von einem
Smartmeter gelesen werden sollten, zeigte der ESP32 aus nicht
ersichtlichen Gründen keine eingehenden Daten auf der Schnittstelle
an. Um meinen Code zu prüfen, nahm ich einen übrig gebliebenen
ESP8266 und baute mit ihm einen Simulator, der alle paar Sekunden
denselben SML-Datensatz sendet. Auf diese Weise fand ich heraus,
dass mein Code in Ordnung war, aber das Kabel irgendwann gebrochen
sein musste.

## Konfiguration
Der Sketch kann leicht abgeändert werden, um jedwege Daten zu senden.
Es ist dabei darauf zu achten, dass die Daten in der Variablen ser_data
in Hexadezimal und in Großbuchstaben angegeben werden.

Hier die Parameter für die gebräuchlichsten Konfigurationen:
* SLEEP - Zeit in Mikrosekunden zwischen den Durchläufen
* BAUD1 - Baudrate für die Std.-Schnittstelle (USB/Konsole am PC)
* BAUD2 - Baudrate für die 2. Schnittstelle per "Software Serial"
* RXPIN - GPIO Pin zum Lesen  von der 2. Schnittstelle
* TXPIN - GPIO Pin zum Senden auf der 2. Schnittstelle

## Hinweis zu Software Serial
In div. Foren wird immer wieder darauf hingewiesen, dass Software
Serial instabil wird, wenn es gemeinsam mit Wifi oder Bluetooth
eingesetzt wird, was ich bestätigen kann. Ursprünglich hab ich einen
ESP8266 mit Software Serial verwendet, um SML-Daten vom Smartmeter
zu lesen. Der ESP8266 startete immer 'mal wieder neu, nach keinem
bestimmten Muster. Manchmal schien auch ein Bit beim Lesen von der
zweiten Seriellen zu kippen, da es immer mal wieder unsinnige Werte
ausgab.

Der ESP8266 taugt daher imho bzgl. Software Serial nur für Testzwecke
wie diese, nicht aber für produktiven Einsatz. Dort ist ein ESP32
vorzuziehen, da er drei serielle Schnittstelen in Hardware mitbringt.
