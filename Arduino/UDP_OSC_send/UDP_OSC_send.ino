#include <OSCMessage.h>
#include <OSCBundle.h>

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>    

EthernetUDP Udp;

//the Arduino's IP
IPAddress ip(192, 168, 2, 6);
//destination IP
IPAddress outIp(192, 168, 2, 3);

//port numbers
const unsigned int inPort = 8001;
const unsigned int outPort = 8000;

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // you can find this written on the board of some Arduino Ethernets or shields


void setup() {
  Ethernet.begin(mac,ip);
  Udp.begin(inPort);

  Serial.begin(9600);
  //Set the Arduino IP as Host destiny at TouchOSC settings
  Serial.print("My IP: ");
  Serial.println(Ethernet.localIP());
}


void loop(){
  OSCBundle bndl;

  int potiraw = analogRead(0);
  int poti = map(potiraw, 0, 1024, 0, 127);

  //debug poti value
  Serial.println(potiraw);
  Serial.println(poti);

  //the message wants an OSC address as first argument
  bndl.add("/analog/0").add((int32_t)poti);
  bndl.add("/label").add((int32_t)poti);

  Udp.beginPacket(outIp, outPort);
  bndl.send(Udp); // send the bytes to the SLIP stream
  Udp.endPacket(); // mark the end of the OSC Packet
  bndl.empty(); // free space occupied by message

  delay(20);
}






