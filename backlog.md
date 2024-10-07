# Backlog
### Inhaltsverzeichnis

- [Backlog](#backlog)
    - [Inhaltsverzeichnis](#inhaltsverzeichnis)
    - [Erster Entwurf](#erster-entwurf)
- [Software Backlog](#software-backlog)
  - [Aufgabe : Umsetzung der Mustererkennung](#aufgabe--umsetzung-der-mustererkennung)
    - [Beschreibung](#beschreibung)
    - [Definition von „Spaß“](#definition-von-spaß)
    - [Akzeptanzkriterien](#akzeptanzkriterien)
  - [Aufgabe : Muster einspeichern](#aufgabe--muster-einspeichern)
    - [Beschreibung](#beschreibung-1)
    - [Definition von „Spaß“](#definition-von-spaß-1)
    - [Akzeptanzkriterien](#akzeptanzkriterien-1)
  - [Aufgabe : Musteraufnahme](#aufgabe--musteraufnahme)
    - [Beschreibung](#beschreibung-2)
    - [Definition von „Spaß“](#definition-von-spaß-2)
    - [Akzeptanzkriterien](#akzeptanzkriterien-2)
  - [Aufgabe : Muster löschen](#aufgabe--muster-löschen)
    - [Beschreibung](#beschreibung-3)
    - [Akzeptanzkriterien](#akzeptanzkriterien-3)
  - [Aufgabe : Schloss öffnen](#aufgabe--schloss-öffnen)
    - [Beschreibung](#beschreibung-4)
    - [Akzeptanzkriterien](#akzeptanzkriterien-4)
  - [Aufgabe : Musterverwaltung](#aufgabe--musterverwaltung)
    - [Beschreibung](#beschreibung-5)
    - [Akzeptanzkriterien](#akzeptanzkriterien-5)
  - [Aufgabe : Schloss Status LED](#aufgabe--schloss-status-led)
    - [Beschreibung](#beschreibung-6)
    - [Definition von „Spaß“](#definition-von-spaß-3)
    - [Akzeptanzkriterien](#akzeptanzkriterien-6)
- [Hardware Backlog](#hardware-backlog)
  - [Aufgabe : Anfertigung der Holzbox](#aufgabe--anfertigung-der-holzbox)
    - [Beschreibung](#beschreibung-7)
    - [Definition von „Spaß“](#definition-von-spaß-4)
    - [Akzeptanzkriterien](#akzeptanzkriterien-7)
  - [Aufgabe : Solenoid (Door-Lock)](#aufgabe--solenoid-door-lock)
    - [Beschreibung](#beschreibung-8)
    - [Akzeptanzkriterien](#akzeptanzkriterien-8)
  - [Aufgabe : Drucktaster (Klopfmuster speichern und löschen)](#aufgabe--drucktaster-klopfmuster-speichern-und-löschen)
    - [Beschreibung](#beschreibung-9)
    - [Akzeptanzkriterien](#akzeptanzkriterien-9)
  - [Aufgabe : RGB-LED (WS2812b)](#aufgabe--rgb-led-ws2812b)
    - [Beschreibung](#beschreibung-10)
    - [Definition von „Spaß“](#definition-von-spaß-5)
    - [Akzeptanzkriterien](#akzeptanzkriterien-10)
  - [Aufgabe : Notöffnungsmechanismus](#aufgabe--notöffnungsmechanismus)
    - [Beschreibung](#beschreibung-11)
    - [Akzeptanzkriterien](#akzeptanzkriterien-11)
  - [Aufgabe : Mikrofon](#aufgabe--mikrofon)
    - [Beschreibung](#beschreibung-12)
    - [Definition von „Spaß“](#definition-von-spaß-6)
    - [Akzeptanzkriterien](#akzeptanzkriterien-12)
  - [Aufgabe : Spannungsversorgung](#aufgabe--spannungsversorgung)
    - [Beschreibung](#beschreibung-13)
    - [Akzeptanzkriterien](#akzeptanzkriterien-13)

### Erster Entwurf

Features:
- Software:
    - [Mustererkennung](#aufgabe--umsetzung-der-mustererkennung)
    - [Muster einspeichern](#aufgabe--muster-einspeichern)
    - [Musteraufnahme](#aufgabe--musteraufnahme)
    - [Muster löschen](#aufgabe--muster-löschen)
    - [Schloss öffnen](#aufgabe--schloss-öffnen)
    - [Musterverwaltung](#aufgabe--musterverwaltung)
    - [Schloss Status LED](#aufgabe--schloss-status-led)
    - Dependency Features
      - Musterwiedergabe
      - Storage (SPIFFS/SD Card) Driver
      - LED Driver (Done, refactored and rewritten from example github code)
- Hardware: 
  - Box bauen ggf. doppelter Boden
  - Solenoid (Door-Lock), um die Tür zu verschließen
  - Notöffnungsmechanismus -> 12V-Kabel zum Solenoid (wichtig für den Fehlerfall)
  - Drucktaster, um die jeweiligen Muster zu speichern, in Liste navigieren, löschen
  - Mikrophon, um die Klopfmuster zu erkennen
  - RGB-LED (WS2812b) für Schloss-Status
  - Spannungsversorgung 12V 1A (AC-AC-Wandler auf 5V)

# Software Backlog

## Aufgabe : Umsetzung der Mustererkennung

### Beschreibung
Die Mustererkennung sollte ähnliche Muster zuordnen können und ggf. bei zu großen Abweichungen des abgespeicherten Musters dies ausgeben. Die Schwierigkeit liegt dabei in der Verarbeitung des Mikrofonsignals und der Erkennung der Änderungen dieses Signal durch ein Klopfen. Anschließend soll das Muster mit den gespeicherten Mustern verglichen werden. Falls ein Muster einem gespeicherten ähnelt, soll dies durch ein Öffnen des Verriegelungsmechanismus und der Grünen-LED zum Ausdruck gebracht werden.

### Definition von „Spaß“
Dies ist die Hauptherausforderung des gesamten Projekts, die Mustererkennung zu implementieren ist die Hauptfunktion des Projekts und erfordert einen kreativen Lösungsansatz und eine gute Signalverarbeitung, da zwei Muster nie 100% identisch sein können.

### Akzeptanzkriterien
Der Mustererkennungs-Algorithmus soll in der Lage sein, das Muster zu erkennen aus dem Rauschen und mit den eingespeicherten Mustern zu vergleichen.



## Aufgabe : Muster einspeichern

### Beschreibung
Um die Muster zu speichern, müssen diese in ein simples und effizientes Format umgewandelt werden. Die Muster sollen intern auf dem ESP im Flash-Speicher gespeichert werden oder auf einer SD-Karte. Hierfür muss zusätzlich noch ein Speicher-Management implementiert werden, sowie ein de-/serialisierungs-Algorithmus für die Muster.

### Definition von „Spaß“
Wurde ein neues Muster aufgenommen, besteht die Herausforderung darin, dieses in ein Möglichst effizientes Format zu konvertieren und zu speichern. Dies garantiert eine schnelle und effiziente Mustererkennung und erfordert einiges an Kreativität und technischem Verständnis.

### Akzeptanzkriterien
Muster können gespeichert und abgerufen werden. Die Muster sind in einem effizienten Format gespeichert und können schnell und einfach abgerufen werden.



## Aufgabe : Musteraufnahme

### Beschreibung
Mit Musteraufnahme ist das Aufnehmen und Filtern des Sensor-Signals gemeint. Das Mikrofon-Signal muss gefiltert und in ein verarbeitbares und speichereffizientes Format umgewandelt werden. Dieses Muster wird anschließend in der Mustererkennung sowie der Musterspeicherung verwendet. Für die Musteraufnahme kommt ein von der Musterverwaltung unabhängiger Knopf zum Einsatz.

### Definition von „Spaß“ 


### Akzeptanzkriterien
Störgeräusche wie Rauschen und andere Umgebungsgeräusche müssen gefiltert werden. Das Muster muss in einem effizienten Format als struct gespeichert werden und kann anschließend in der Mustererkennung verwendet werden um Muster zu vergleichen und einfacher zu speichern.



## Aufgabe : Muster löschen

### Beschreibung
Um die gespeicherten Muster von dem Flash-Speicher des ESP oder der SD-Karte entfernen zu können, muss eine Funktion im Speicher-Management implementiert werden, die das Löschen gespeicherter Mustert ermöglicht.

### Akzeptanzkriterien
Muster können nach dem speichern auch gelöscht werden um neuen Speicherplatz zu schaffen.



## Aufgabe : Schloss öffnen

### Beschreibung
Die Kiste soll im Ruhezustand verschlossen und verriegelt sein. Sobald es (durch die Eingabe des korrekten Klopfmusters) gewünscht wird, soll das Solenoid die Falle (des Schlosses) zurück ziehen. Da das Solenoid nicht direkt durch den ESP mit Strom versorgt werden kann, kommt hier ein Relais zum Einsatz, welches mittels ESP angesteuert werden soll.

### Akzeptanzkriterien
Das Solenoid muss noch nicht angesteuert werden können. Es reicht aus, wenn das Relais umgeschaltet werden kann.



## Aufgabe : Musterverwaltung 

### Beschreibung
Die Musterverwaltung ermöglicht die Auswahl (Navigation) zwischen die einzelnen gespeicherten Mustern. Für die Muster gibt es zwei Funktionen: Muster löschen, Musterwiedergabe. Für die Musterverwaltung gibt es 4 Knöpfe: Vor, Zurück, Muster löschen, Musterwiedergabe. (Für das Aufnehmen von Mustern gibt es einen eigenständigen Knopf -> Musteraufnahme)

### Akzeptanzkriterien
Die Verwaltung sollte die einwandfreie Navigation durch die gespeicherten Muster ermöglichen, sowie den Aufruf der oben genannten Funktionen ausführen.


## Aufgabe : Schloss Status LED

### Beschreibung
An der Truhe befindet sich eine adressierbare LED (WS2812b) soll den Status des Schlosses anzeigen.
Die grundlegenden Status sind:
- Rot: Schloss ist verriegelt
- Grün: Schloss ist entriegelt
- Blau: aktuell wird ein Muster aufgenommen
- Orange: Muster ist fast korrekt
- Weiß: Fehlerfall

Unter Umständen müssen diese Status noch erweitert werden um weitere Informationen anzuzeigen, die erst im Laufe der Entwicklung aufgedeckt 
werden.

### Definition von „Spaß“
Interessant ist hier die Ansteuerung der LED anhand des Datenblatts zu analysieren und dieses eigene Protokoll im Code für die ESP-IDF zu entwickeln.

### Akzeptanzkriterien
Die LED zeigt den korrekten Status des Schlosses an und kann auch bei einem Systemabsturz oder Fehlerfall noch den "Fehlerfall" Status anzeigen.

# Hardware Backlog

## Aufgabe : Anfertigung der Holzbox

### Beschreibung
Um eine Tür zu demonstrieren, verwenden wir eine Box aus Holz, welche einen Doppelboden besitzt. Die Hardware-Komponenten werden in der verschlossenen Holzbox untergebracht. Der Doppelboden kann für die sichere und ordentliche Verkabelung der Komponenten genutzt werden, um Platz zu sparen und die Verdrahtung zu verstecken. 

### Definition von „Spaß“
Die Möglichkeit, ein eigenes und funktionales Produkt zu schaffen, trägt positiv zum Projekt bei. Der Prozess des Entwurfes und der Konstruktion der Holzbox bereichern die handwerklichen Fähigkeiten, die damit gefördert werden. 

### Akzeptanzkriterien
Die Aufgabe ist erledigt, wenn die Holzbox fertig montiert vorliegt und die jeweiligen Komponenten, Platz in der Box finden. 



## Aufgabe : Solenoid (Door-Lock)

### Beschreibung
Um die Holzbox öffnen und schließen zu können wird ein Solenoid-Magnet als mechanischer Türverschluss verwendet. Der Mikrocontroller sendet ein Signal an das Solenoid, um die Tür jeweils zu verschließen oder zu entriegeln. Um das Solenoid vernünftig an die Holzbox anbringen zu können, wird eine Kerbe in die Wand gefräst. 

### Akzeptanzkriterien
Die Aufgabe ist erledigt, wenn die Tür mithilfe des Solenoids ohne Störungen verschlossen und entriegelt werden kann. 



## Aufgabe : Drucktaster (Klopfmuster speichern und löschen)

### Beschreibung
Es werden mehrere Drucktaster eingerichtet, um Funktionen wie das Speichern, Navigieren und Löschen von Klopfmustern zu ermöglichen. Die jeweiligen Taster sind mit dem Mikrocontroller verbunden, der letztendlich die Eingaben verarbeitet. Wenn der Benutzer einen Muster-Speicher-Taster drückt, wechselt das System in den Speichermodus. Der jeweilige Benutzer klopft das neue Muster, das vom Mikrocontroller gespeichert wird. Über einen weiteren Taster kann das ausgewählte Muster wieder gelöscht werden. 

### Akzeptanzkriterien
Die Aufgabe gilt als erledigt, wenn die Drucktaster am Gehäuse befestigt sind und ihre Funktionen in der Software erfüllen. 



## Aufgabe : RGB-LED (WS2812b)

### Beschreibung
Um den Status unseres Schlosses anzuzeigen, verwenden wir eine RGB-LED (WS2812b), welche wir zuvor konfigurieren. Sie leuchtet grün, wenn das Schloss entriegelt ist und rot, wenn das Schloss verschlossen ist. Wenn die LED blau leuchtet, bedeutet dies, dass wir uns im Aufnahme-Modus befinden. Die Farbe Orange zeigt den Fehlerfall an, wenn das gespeicherte Muster nicht erraten wurde. 

### Definition von „Spaß“
Die Herausforderung, die Ansteuerung der LED zu untersuchen und das entsprechende Datenblatt zu analysieren, um ein eigenes Protokoll im Code für die ESP_IDF zu erstellen.

### Akzeptanzkriterien
Die LED zeigt den korrekten Status des Schlosses an und kann auch bei einem Systemabsturz oder Fehlerfall noch den "Fehlerfall" Status anzeigen.


## Aufgabe : Notöffnungsmechanismus

### Beschreibung
Ein 12V-Kabel wird zum Solenoid geführt, um im Fehlerfall eine Notöffnung der Tür zu ermöglichen. Dies könnte durch einen Taster oder Schalter erfolgen, der unabhngig vom Mikrocontroller funktoniert. 

### Akzeptanzkriterien
Wenn das Schloss zu jeder Zeit oder bei Notfällen unabhängig vom Microcontroller geöffnet werden kann.



## Aufgabe : Mikrofon

### Beschreibung
Es wird ein Mikrofon installiert, um die Klopfgeräusche und das dazugehörige Muster aufzuzeichnen. Das Mikrofon ist mit dem Microcontroller verbunden, welcher die Klopfgeräusche letztendlich analysiert, um ein Muster zu rkennen. 

### Definition von „Spaß“
Interessant ist hier die Ansteuerung des Mikrofons anhand des Datenblatts zu analysieren und die aufgenommenen Klopfgeräusche aufzunehmen und zu verwerten. 

### Akzeptanzkriterien
Die Funktion ist gegeben, wenn das Klopfmuster erkannt und weitergeleitet wird. 



## Aufgabe : Spannungsversorgung

### Beschreibung
Eine 12V 1A Spannungsversorgung wird verwendet, um das Solenoid und den Mikrocontroller mit Strom zu versorgen. Ein AC-Ac Wandler wird eingesetzt, um die Spannung auf 5V zu reduzieren, die für den Mikrocontroller und andere digitale Komponenten erforderlich ist. 

### Akzeptanzkriterien
Die Spannungsversorgung ist fertig, wenn sowohl 12V, als auch 5V Spannungen abgegriffen werden können. Dies muss mittels Multimeter überprüft werden.
