# Backlog
### Inhaltsverzeichnis

- [Backlog](#backlog)
    - [Inhaltsverzeichnis](#inhaltsverzeichnis)
    - [Erster Entwurf](#erster-entwurf)
  - [Aufgabe: Planung des Projekts](#aufgabe-planung-des-projekts)
    - [Beschreibung](#beschreibung)
- [Software Backlog](#software-backlog)
  - [Aufgabe: Vertrautmachen mit der Entwicklungsumgebung](#aufgabe-vertrautmachen-mit-der-entwicklungsumgebung)
    - [Beschreibung](#beschreibung-1)
  - [Aufgabe: Umsetzung der Mustererkennung](#aufgabe-umsetzung-der-mustererkennung)
    - [Beschreibung](#beschreibung-2)
    - [Definition von „Spaß“](#definition-von-spaß)
    - [Akzeptanzkriterien](#akzeptanzkriterien)
  - [Aufgabe: Muster einspeichern](#aufgabe-muster-einspeichern)
    - [Beschreibung](#beschreibung-3)
    - [Definition von „Spaß“](#definition-von-spaß-1)
    - [Akzeptanzkriterien](#akzeptanzkriterien-1)
  - [Aufgabe: Musteraufnahme](#aufgabe-musteraufnahme)
    - [Beschreibung](#beschreibung-4)
    - [Akzeptanzkriterien](#akzeptanzkriterien-2)
  - [Aufgabe: Muster löschen](#aufgabe-muster-löschen)
    - [Beschreibung](#beschreibung-5)
    - [Akzeptanzkriterien](#akzeptanzkriterien-3)
  - [Aufgabe: Schloss öffnen](#aufgabe-schloss-öffnen)
    - [Beschreibung](#beschreibung-6)
    - [Akzeptanzkriterien](#akzeptanzkriterien-4)
  - [Aufgabe: Musterverwaltung](#aufgabe-musterverwaltung)
    - [Beschreibung](#beschreibung-7)
    - [Akzeptanzkriterien](#akzeptanzkriterien-5)
  - [Aufgabe: Musterwiedergabe](#aufgabe-musterwiedergabe)
    - [Beschreibung](#beschreibung-8)
    - [Definition von „Spaß“](#definition-von-spaß-2)
    - [Akzeptanzkriterien](#akzeptanzkriterien-6)
  - [Aufgabe: Schloss Status LED](#aufgabe-schloss-status-led)
    - [Beschreibung](#beschreibung-9)
    - [Definition von „Spaß“](#definition-von-spaß-3)
    - [Akzeptanzkriterien](#akzeptanzkriterien-7)
  - [Aufgabe: Storage Driver](#aufgabe-storage-driver)
    - [Beschreibung](#beschreibung-10)
    - [Akzeptanzkriterien](#akzeptanzkriterien-8)
  - [Aufgabe: LED-Driver](#aufgabe-led-driver)
    - [Beschreibung](#beschreibung-11)
    - [Akzeptanzkriterien](#akzeptanzkriterien-9)
- [Hardware Backlog](#hardware-backlog)
  - [Aufgabe: Anfertigung der Holzbox](#aufgabe-anfertigung-der-holzbox)
    - [Beschreibung](#beschreibung-12)
    - [Definition von „Spaß“](#definition-von-spaß-4)
    - [Akzeptanzkriterien](#akzeptanzkriterien-10)
  - [Aufgabe: Solenoid (Door-Lock)](#aufgabe-solenoid-door-lock)
    - [Beschreibung](#beschreibung-13)
    - [Akzeptanzkriterien](#akzeptanzkriterien-11)
  - [Aufgabe: Drucktaster](#aufgabe-drucktaster)
    - [Beschreibung](#beschreibung-14)
    - [Akzeptanzkriterien](#akzeptanzkriterien-12)
  - [Aufgabe: RGB-LED (WS2812b)](#aufgabe-rgb-led-ws2812b)
    - [Beschreibung](#beschreibung-15)
    - [Definition von „Spaß“](#definition-von-spaß-5)
    - [Akzeptanzkriterien](#akzeptanzkriterien-13)
  - [Aufgabe: Notöffnungsmechanismus](#aufgabe-notöffnungsmechanismus)
    - [Beschreibung](#beschreibung-16)
    - [Akzeptanzkriterien](#akzeptanzkriterien-14)
  - [Aufgabe: Mikrofon](#aufgabe-mikrofon)
    - [Beschreibung](#beschreibung-17)
    - [Definition von „Spaß“](#definition-von-spaß-6)
    - [Akzeptanzkriterien](#akzeptanzkriterien-15)
  - [Aufgabe: Spannungsversorgung](#aufgabe-spannungsversorgung)
    - [Beschreibung](#beschreibung-18)
    - [Akzeptanzkriterien](#akzeptanzkriterien-16)
  - [Aufgabe: Platine entwerfen](#aufgabe-platine-entwerfen)
    - [Beschreibung](#beschreibung-19)
    - [Akzeptanzkriterien](#akzeptanzkriterien-17)
  - [Aufgabe: Fertigstellen des Systems](#aufgabe-fertigstellen-des-systems)
    - [Beschreibung](#beschreibung-20)
    - [Akzeptanzkriterien](#akzeptanzkriterien-18)
  - [Aufgabe: Erstellen eines Videos](#aufgabe-erstellen-eines-videos)
    - [Beschreibung](#beschreibung-21)
    - [Akzeptanzkriterien](#akzeptanzkriterien-19)
  - [Aufgabe: Erstellen des Kaufpitch](#aufgabe-erstellen-des-kaufpitch)
    - [Beschreibung](#beschreibung-22)
    - [Akzeptanzkriterien](#akzeptanzkriterien-20)

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
      - [Musterwiedergabe](#aufgabe--musterverwaltung)
      - [Storage Driver](#aufgabe--storage-driver)
      - [LED Driver](#aufgabe--led-driver)


## Aufgabe: Planung des Projekts

### Beschreibung
Die Planung des Projekts umfasst die Aufteilung der Aufgaben in Sprints, die Zuweisung von Verantwortlichkeiten und die Schätzung des Zeitaufwands für die einzelnen Aufgaben. Sie dient dazu, das Projekt in überschaubare Teilaufgaben zu gliedern, erste Gedanken zu Umsetzung und diese im Nachhinein zu erleichtern.



## Aufgabe: Erstellen der Dokumentation

### Beschreibung
Kontinuierlich wird der Fortschritt des Projektes dokumentiert und die Dokumentation für jeden Sprint finalisiert.

### Akzeptanzkriterien
Die vollständige Dokumentation liegt vor.



## Aufgabe: Erstellen der 1 Minute Madness (PowerPoint)

### Beschreibung
In der "1 Minute Madness" haben wir genau eine Minute unsere Produktidee zu präsentieren. Dafür wollen wir eine PowerPoint-Präsentation erstellen.

### Akzeptanzkriterien
Die 1 Minute Madness ist präsentiert und im Vorhinein wurde eine PowerPoint-Präsentation erstellt.



# Software Backlog

## Aufgabe: Vertrautmachen mit der Entwicklungsumgebung 

### Beschreibung
Die Entwicklungsumgebung ist bisher für uns noch unbekannt, daher benötigt unser Team eine gewisse Zeit sich mit den Möglichkeiten vertraut zu machen.



## Aufgabe: Umsetzung der Mustererkennung

### Beschreibung
Die Mustererkennung sollte ähnliche Muster zuordnen können und ggf. bei zu großen Abweichungen des abgespeicherten Musters dies ausgeben. Die Schwierigkeit liegt dabei in der Verarbeitung des Mikrofonsignals und der Erkennung der Änderungen dieses Signal durch ein Klopfen. Anschließend soll das Muster mit den gespeicherten Mustern verglichen werden. Falls das Muster einem gespeicherten ähnelt, soll dies durch ein Öffnen des Verriegelungsmechanismus und der Grünen-LED zum Ausdruck gebracht werden.

### Definition von „Spaß“
Dies ist die Hauptherausforderung des gesamten Projekts und erfordert einen kreativen Lösungsansatz und eine gute Signalverarbeitung, da zwei Muster nie 100% identisch sein können.

### Akzeptanzkriterien
Der Mustererkennungs-Algorithmus soll in der Lage sein, das Muster durch das Rauschen zu erkennen und mit den eingespeicherten Mustern zu vergleichen. Anschließend soll bei einer gewissen Ähnlichkeit der Verriegelungsmechanismus und die Grüne-LED angesteuert werden können.



## Aufgabe: Muster einspeichern

### Beschreibung
Um die Muster zu speichern, müssen diese in ein simples und effizientes Format umgewandelt werden. Die Muster sollen in Dateien gespeichert werden, hierfür muss ein de-/serialisierungs-Algorithmus für die Muster geschrieben werden.

### Definition von „Spaß“
Wurde ein neues Muster aufgenommen, besteht die Herausforderung darin, dieses in ein Möglichst effizientes Format zu konvertieren und zu speichern. Dies garantiert eine schnelle und effiziente Mustererkennung und erfordert einiges an Kreativität und technischem Verständnis.

### Akzeptanzkriterien
Muster können gespeichert und abgerufen werden. Die Muster sind in einem effizienten Format gespeichert und können schnell und einfach abgerufen werden.



## Aufgabe: Musteraufnahme

### Beschreibung
Mit der Musteraufnahme ist das Aufnehmen und Filtern des Sensor-Signals gemeint. Das Mikrofon-Signal muss gefiltert und in ein verarbeitbares Format umgewandelt werden. Dieses Muster wird anschließend in der Mustererkennung sowie der Musterspeicherung verwendet. Für die Musteraufnahme kommt ein von der Musterverwaltung unabhängiger Knopf zum Einsatz.

### Akzeptanzkriterien
Störgeräusche wie Rauschen und andere Umgebungsgeräusche müssen gefiltert werden. Das Muster muss in einem effizienten Format als struct gespeichert werden und kann anschließend in der Mustererkennung verwendet werden um Muster zu vergleichen und einfacher zu speichern.



## Aufgabe: Muster löschen

### Beschreibung
Um die gespeicherten Muster von dem Flash-Speicher des ESP oder der SD-Karte entfernen zu können, muss eine Funktion im Speicher-Management implementiert werden, die das Löschen gespeicherter Mustert ermöglicht.

### Akzeptanzkriterien
Muster können nach dem Speichern auch gelöscht werden um neuen Speicherplatz zu schaffen.



## Aufgabe: Schloss öffnen

### Beschreibung
Die Kiste soll im Ruhezustand verschlossen und verriegelt sein. Sobald es (durch die Eingabe des korrekten Klopfmusters) gewünscht wird, soll das Solenoid die Falle (des Schlosses) zurück ziehen. Da das Solenoid nicht direkt durch den ESP mit Strom versorgt werden kann, kommt hier ein Relais zum Einsatz, welches mittels ESP angesteuert werden soll.

### Akzeptanzkriterien
Das Solenoid muss noch nicht angesteuert werden können. Es reicht aus, wenn das Relais umgeschaltet werden kann.



## Aufgabe: Musterverwaltung 

### Beschreibung
Die Musterverwaltung ermöglicht die Auswahl (Navigation) zwischen den einzelnen gespeicherten Mustern. Für die Muster gibt es zwei Funktionen: Muster löschen, Musterwiedergabe. Für die Musterverwaltung gibt es 4 Knöpfe: Vor, Zurück, Muster löschen, Musterwiedergabe. (Für das Aufnehmen von Mustern gibt es einen eigenständigen Knopf -> Musteraufnahme)

### Akzeptanzkriterien
Die Verwaltung sollte die einwandfreie Navigation durch die gespeicherten Muster ermöglichen, sowie den Aufruf der oben genannten Funktionen ausführen.



## Aufgabe: Musterwiedergabe

### Beschreibung

Die Musterwiedergabe soll die Möglichkeit bieten, ein gespeichertes Muster wiederzugeben. Dies ist wichtig, um die gespeicherten Muster zu überprüfen und zu löschen. Die Musterwiedergabe wird durch einen Drucktaster ausgelöst, der unabhängig von der Musterverwaltung ist. 

### Definition von „Spaß“
Interessant ist hier das gespeicherte Format eines Musters wieder in eine wiedererkennbare Form zu bringen und dieses Muster wiederzugeben.
Hierfür eine passende Darstellung zu finden und das Muster wiederzugeben ist eine kreative Herausforderung.

### Akzeptanzkriterien
Abgespeicherte Muster können wiedergegeben werden und sind in einer verständlichen Form dargestellt.



## Aufgabe: Schloss Status LED

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
Die LED zeigt den korrekten Status des Schlosses an.



## Aufgabe: Storage Driver

### Beschreibung
Der Storage Driver soll die Kommunikation zwischen Datenspeicher (on-board oder SD-Card) und dem ESP32 dienen.

### Akzeptanzkriterien
Dateien können korrekt erstellt und gelöscht werden.



## Aufgabe: LED-Driver

### Beschreibung
Der LED-Driver dient dazu die adressierbaren LEDs anzusteuern. Hierbei soll der Typ WS2812b verwendet werden und einfach, vergleichbar zu der FastLED Library, angesteuert werden können.

### Akzeptanzkriterien
Die LEDs können angesteuert werden und die Farbe wird für jede LED korrekt eingestellt.



# Hardware Backlog

## Aufgabe: Anfertigung der Holzbox

### Beschreibung
Um eine Tür zu demonstrieren, verwenden wir eine Box aus Holz, welche einen Doppelboden besitzt. Die Hardware-Komponenten werden in der verschlossenen Holzbox untergebracht. Der Doppelboden kann für die sichere und ordentliche Verkabelung der Komponenten genutzt werden, um Platz zu sparen und die Verdrahtung zu verstecken. 

### Definition von „Spaß“
Die Möglichkeit, ein eigenes und funktionales Produkt zu schaffen, trägt positiv zum Projekt bei. Der Prozess des Entwurfes und der Konstruktion der Holzbox bereichern die handwerklichen Fähigkeiten, die damit gefördert werden. 

### Akzeptanzkriterien
Die Aufgabe ist erledigt, wenn die Holzbox fertig montiert vorliegt und die jeweiligen Komponenten in der Box verbaut verden könnten. 



## Aufgabe: Solenoid (Door-Lock)

### Beschreibung
Um die Holzbox öffnen und schließen zu können wird ein Solenoid-Magnet als mechanischer Türverschluss verwendet. Der Mikrocontroller sendet ein Signal an das Solenoid, um die Tür jeweils zu verschließen oder zu entriegeln. Um das Solenoid vernünftig an die Holzbox anbringen zu können, wird eine Kerbe in die Wand gefräst. Die Ansteuerung des Solenoids erfolgt über ein Relais.

### Akzeptanzkriterien
Die Aufgabe ist erledigt, wenn die Tür mithilfe des Solenoids ohne Störungen verschlossen und entriegelt werden kann.



## Aufgabe: Drucktaster

### Beschreibung
Es werden mehrere Drucktaster eingerichtet, um Funktionen wie das Speichern, Navigieren und Löschen von Klopfmustern zu ermöglichen. Die jeweiligen Taster sind mit dem Mikrocontroller verbunden, der letztendlich die Eingaben verarbeitet. Die Taster müssen hardwaretechnisch entprellt werden.

### Akzeptanzkriterien
Die Aufgabe gilt als erledigt, wenn die Drucktaster am Gehäuse befestigt sind und ihre Funktionen in der Software erfüllen. 



## Aufgabe: RGB-LED (WS2812b)

### Beschreibung
Um den Status unseres Schlosses anzuzeigen, verwenden wir eine RGB-LED (WS2812b), welche wir zuvor konfigurieren. 

### Definition von „Spaß“
Die Herausforderung, die Ansteuerung der LED zu untersuchen und das entsprechende Datenblatt zu analysieren, um ein eigenes Protokoll im Code für die ESP_IDF zu erstellen.

### Akzeptanzkriterien
Die LED zeigt den korrekten Status des Schlosses an.



## Aufgabe: Notöffnungsmechanismus

### Beschreibung
Ein 12V-Kabel wird zum Solenoid geführt, um im Fehlerfall eine Notöffnung der Tür zu ermöglichen. Dies könnte durch einen Taster oder Schalter erfolgen, der unabhängig vom Mikrocontroller funktioniert. 

### Akzeptanzkriterien
Wenn das Schloss zu jeder Zeit oder bei Notfällen unabhängig vom Microcontroller geöffnet werden kann. Das Notöffnen des Schlosses sollte auch bei nicht vorhandener Platine und bei Softwareabsturz möglich sein.



## Aufgabe: Mikrofon

### Beschreibung
Es wird ein Mikrofon installiert, um die Klopfgeräusche und das dazugehörige Muster aufzuzeichnen. Das Mikrofon ist mit dem Microcontroller verbunden, welcher die Klopfgeräusche letztendlich analysiert, um ein Muster zu erkennen. 

### Definition von „Spaß“
Interessant ist hier die Ansteuerung des Mikrofons anhand des Datenblatts zu analysieren und die aufgenommenen Klopfgeräusche aufzunehmen und zu verwerten. 

### Akzeptanzkriterien
Die Funktion ist gegeben, wenn das Klopfgeräusch detektiert und weitergeleitet wird. 



## Aufgabe: Spannungsversorgung

### Beschreibung
Eine 12V (min. 1A) Spannungsversorgung wird verwendet, um das Solenoid und den Mikrocontroller (sowie alle anderen elektrischen Komponenten) mit Strom zu versorgen. Ein DC-DC Wandler wird eingesetzt, um die Spannung auf 5V zu reduzieren, die für den Mikrocontroller und andere elektrische Komponenten erforderlich ist.

### Akzeptanzkriterien
Die Spannungsversorgung ist fertig, wenn sowohl 12V, als auch 5V Spannungen abgegriffen werden können. Dies muss mittels Multimeter überprüft werden können.



## Aufgabe: Platine entwerfen

### Beschreibung
In unserer Kiste sollen einige der elektrischen Komponenten kompakt auf einer Platine verbaut werden. Diese Platine designen wir im Laufe dieses Projektes selber. Die Platine soll zum einen die Schalter der Musterverwaltung, den ESP, sowie die Schnittstellen zu den anderen nicht auf der Platine verbauten Komponenten unterbringen.

### Akzeptanzkriterien
Wenn die Platine designed ist und die geforderten Funktionen erfüllt. Die produzierte Platine muss noch nicht vorliegen.



## Aufgabe: Fertigstellen des Systems

### Beschreibung
Gegen Ende des Projektes werden alle Komponenten in der Holzbox montiert und elektrisch verkabelt. Softwarekomponenten sind alle zusammengeschaltet und einsatzbereit.

### Akzeptanzkriterien
Das gesamte System ist als Einheit funktionsfähig.



## Aufgabe: Erstellen eines Videos

### Beschreibung
Die Funktionen des Systems werden mittels Video beleuchtet. 

### Akzeptanzkriterien
Das Video ist erstellt und mit ggf. Text und Ton auf einem Endgerät darstellbar.



## Aufgabe: Erstellen des Kaufpitch

### Beschreibung
Die Funktionen des Systems sollen von Externen getestet werden können. Es wird über ein Verkaufskonzept nachgedacht.

### Akzeptanzkriterien
Ein Verkaufskonzept liegt vor.