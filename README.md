OSCuino
=======

Examples for using OSCuino with Pure Data &amp; Max/MSP



=======
Beispiele für die verwendung von OSCuino.
OSCuino ermöglicht die kommunikation mit OSC über die Serielle oder  Ethernet Schnittstelle eines Arduino/Teensy. 

weitere Infos zu OSCuino findet man bei CNMAT: http://cnmat.berkeley.edu/oscuino

=======
für die Kommunikation werden folgende Erweiterungen benötigt:

Arduino:
- OSCuino Library: https://github.com/CNMAT/OSC

Max/MSP
- odot Objekte: http://cnmat.berkeley.edu/downloads

Pure Data
- odot Objekte: http://cnmat.berkeley.edu/downloads

=======
Raspberry Pi & OSCuino

OSCuino & Pure Data funktionieren auch mit dem Raspberry Pi. Die "print" Funktion in den Pure Data Beispielen sollte mit einem "gate" Objekt verbunden werden und hauptsächlich für das debuggin genutzt werden. Die Datenausgabe des "comport" und die dadurch kontinuierliche Ausgabe an die Konsole von Pure Data kann den Prozessor des Raspberry Pi stark belasten, wodurch es zu  Latenzen kommen kann.

