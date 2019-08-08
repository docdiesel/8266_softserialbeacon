/*
 * ==== 8266_softwareserialbeacon.ino ====
 * 
 * (en) This is just a small sketch for ESP 8266 that's writing some data
 *      via serial line. I needed some dummy device to simulate a smartmeter,
 *      sending SML data at 9600 baud. You may change data and parameters 
 *      to simulate other devices.
 *      
 * (de) Dieser kleine EPS8266-Sketch schickt Daten über eine serielle Schnittstelle.
 *      Ich hab's verwendet, um einen Smartmeter zu simulieren. Der Code kann durch
 *      Anpassungf aber auch andere Geräte simulieren.
 *
 */

#include <SoftwareSerial.h>

#define SLEEP 5000    // ms to wait between beacons
#define BAUD1 115200  // for USB debugging
#define BAUD2 9600    // for the simulator line
#define RXPIN 13      // pins for the simulator
#define TXPIN 15

//-- here's some sample sml data as UPPERCASE HEX string; this is what we send out to software serial
char ser_data[] = "1B1B1B1B0101010176070011095D533D620062007263010176010107001109651BBF0B0901454D48000042B29B01016395460076070011095D533E620062007263070177010B0901454D48000042B29B070100620AFFFF7262016509652CEB7A77078181C78203FF0101010104454D480177070100000009FF010101010B0901454D48000042B29B0177070100010800FF6401018201621E52FF56000675AA750177070100020800FF6401018201621E52FF560016F4C97D0177070100010801FF0101621E52FF56000675AA750177070100020801FF0101621E52FF560016F4C97D0177070100010802FF0101621E52FF5600000000000177070100020802FF0101621E52FF5600000000000177070100100700FF0101621B52FF550000041A0177078181C78205FF017262016509652CEC01018302BA9AC4F8D4416AD27116536C043FE9A11B8506BA593F025925C33BC251F66EB695346FF31CD89E31E9DA96329AF9CF66010101630ECD0076070011095D53416200620072630201710163033F00001B1B1B1B1A";

// define soft serial object; RX = GPIO13, TX = GPIO15
SoftwareSerial softSerial(RXPIN, TXPIN, false, 256);

//== fire up your ESP
void setup() {
  Serial.begin(BAUD1);     // standard serial/USB
  softSerial.begin(BAUD2); // default is 8N1
}

//== beacon going round and round and round and ...
void loop() {
  Serial.println("ping");  // just to see it's working
  write2softserial();      // send out the beacon light
  delay(SLEEP);            // waiting for Godot
}

//-- function to write payload out to soft serial
void write2softserial(void){
  // get chars of hexstring and convert them to binary bytes
  for (int i=0; i<sizeof(ser_data)-1; i+=2){

    int xhigh = hexchar2int(ser_data[i]);
    int xlow  = hexchar2int(ser_data[i+1]);

    if ((xhigh < 0) || (xlow < 0)){
      // somebody put non-hex chars into the payload string?
      Serial.print("messy hex string for data to send: ");      
      Serial.print(ser_data[i]);   Serial.print(ser_data[i+1]);
      Serial.println();
    } else {
      softSerial.write( xhigh * 16 + xlow );
    }
  }
}

//-- funtion to convert uppercase hex string to binary bytes
int hexchar2int(char hx){
  int v = hx - int('0');  
  if (v >  9){ v = hx - int('A') + 10; }  // gt 9 must be a letter
  if (v > 15){ v = -1; }  // gt 15 means somebody messed with the hex data...
  return v;
}
