#include <OSCBundle.h>

/*
OSC Bundle Nachrichten
basierend auf CNMAT Beispielsketch der OSCuino Bibliothek
*/

//Teensy und Leonardo nutzen einen anderen speziellen USB serial.
#if defined(CORE_TEENSY)|| defined(__AVR_ATmega32U4__)
#include <SLIPEncodedUSBSerial.h>
SLIPEncodedUSBSerial SLIPSerial(Serial);
#else
// Wenn kein Teensy oder Leonardo angeschlossen ist
#include <SLIPEncodedSerial.h>
SLIPEncodedSerial SLIPSerial(Serial);
#endif

int poti = A0;
int potiRoh = 0;
int potiMidi = 0;

void setup() {
  //SLIPserial wird wie der normale Serial befehl initiert.
  Serial.begin(9600);   
  while(!Serial); // speziell für Leonardo 
}


void loop(){

  potiRoh = analogRead(poti);
  //Analog Rohwerte zu MIDI konformen Werte (0-127) skalieren
  potiMidi = map(potiRoh, 0, 1024, 0, 127);

  // bei mehreren OSC Nachrichten gleichzeitig muss man diese als OSC Bundle senden
  OSCBundle bndl;
  bndl.add("/analog/0").add(potiRoh);
  bndl.add("/analog/midi/0").add(potiMidi);

  SLIPSerial.beginPacket();
  bndl.send(SLIPSerial); // sendet das vorherige OSC Bundle über den SLIP Stream
  SLIPSerial.endPacket(); // danach wird das Ende der Nachricht ausgegeben.
  bndl.empty(); // und der Speicher wird nach der Übertragung der Daten geleert

  delay(20);
}




