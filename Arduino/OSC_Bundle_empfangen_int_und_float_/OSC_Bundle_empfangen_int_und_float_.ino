/*

 Steuern von digitalen Ausgängen (HIGH/LOW) durch OSC Nachrichten.
 Der Status der Ausgänge wird nach dem Verarbeiten zurückgesendet.
 
 OSC Nachricht = Digitaler Ausgang
 "/led/2" = Pin 12
 "/led/1" = Pin 13
 "/9" =  Pin 9
 
 basiert auf CNMAT Beispiel.
 weitere Infos:
 http://cnmat.berkeley.edu/oscuino
 
 */
#include <OSCBundle.h>
#include <OSCBoards.h>
#include <SoftPWM.h>


#ifdef BOARD_HAS_USB_SERIAL
#include <SLIPEncodedUSBSerial.h>
SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
#else
#include <SLIPEncodedSerial.h>
SLIPEncodedSerial SLIPSerial(Serial);
#endif

OSCBundle bundleOUT;



//callback Funktion "LEDcontrol"
void LEDcontrol( OSCMessage &msg, int addrOffset)
{
  // wenn am Nachrichtencontainer nach "/led" noch "/1" hängt,
  // wird dieser und sein anliegender Wert hier verarbeitet.
  if (msg.match( "/1" , addrOffset ))
  {
    if (msg.getInt(0) == 1)
    {
      pinMode(13, OUTPUT);
      digitalWrite(13, HIGH);

      // sendet den Status der LED 1.
      bundleOUT.add("/status/led/1").add(1);
      bundleOUT.add("/statusmessage").add("LED1 an");
    }
    else if (msg.getInt(0) == 0)
    {
      pinMode(13, OUTPUT);
      digitalWrite(13, LOW);
      bundleOUT.add("/status/led/1").add(0);
      bundleOUT.add("/statusmessage").add("LED1 aus");
    }
  }
  // falls der Nachrichtencontainer mit "/2" weiter geht, 
  // dann wird das folgende ausgeführt
  else if (msg.match("/2" , addrOffset))
  {
    if (msg.getInt(0) == 1)
    {
      pinMode(12, OUTPUT);
      digitalWrite(12, HIGH);
      bundleOUT.add("/status/led/2").add(1);

    }
    else if (msg.getInt(0) == 0)
    {
      pinMode(12, OUTPUT);
      digitalWrite(12, LOW);
      bundleOUT.add("/status/led/2").add(0);

    }
  }
}
// callback Funktion für "/9" + Float Wert
void LEDpwm ( OSCMessage &msg,  int adressOffset)
{
  // wenn der Wert als Float eingeht
  if (msg.isFloat(0))
  {
    float LEDpwm = msg.getFloat(0);
    int LED9 = LEDpwm * 127;
    pinMode(9, OUTPUT);
    analogWrite(9,(int)LED9);
    bundleOUT.add("/status/led/3").add(LED9);
  }
}


void setup() {
  // Baudrate des SLIPSerial kann an auch schneller arbeiten, 
  // entsprechend der möglich zur Verfügungstellenden Baurate des Sender bzw. Empfängers.
  SLIPSerial.begin(9600);

#if ARDUINO >= 100
  while(!Serial);   // Leonardo bug
#endif

}


void loop(){ 
  OSCBundle bundleIN;
  int size;

  while(!SLIPSerial.endofPacket())
    if( (size =SLIPSerial.available()) > 0)
    {
      while(size--)
        bundleIN.fill(SLIPSerial.read());
    }
  // falls keine Fehler vorliegt, wird der Nachrichtencontainer an die o.g. callback Funktion weitergeleitet
  if(!bundleIN.hasError()){
    bundleIN.route("/led", LEDcontrol);
    bundleIN.route("/9", LEDpwm);

    SLIPSerial.beginPacket();
    bundleOUT.send(SLIPSerial);
    SLIPSerial.endPacket();
    bundleOUT.empty(); // leer des bundle Speichers für neue Nachrichten
    delay(20);

  }
}
