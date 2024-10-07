# Backlog

Features:
- Software:
    - Mustererkennung
    - Muster einspeichern
    - Muster löschen
    - Schloss öffnen
    - Display für Musterverwaltung
    - RGB-LED (WS2812b) für Schloss-Status (rot -> verschlossen, grün -> entriegelt, blau -> Aufnahme-Modus, orange -> knapp daneben ist auch vorbei)
    - Dependency Features
      - Display Driver
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
    
## Aufgabe 1: Umsetzung der Mustererkennung

### Beschreibung

Die Mustererkennung sollte ähnliche Muster zuordnen können und ggf. bei zu großen Abweichungen des abgespeicherten Musters dies ausgeben. Die Schwierigkeit liegt dabeiinf der Verarbeitung des Mikrofonsignals und der Erkennung der Änderungen dieses Signal durch ein klopfen. Anschließend soll das uster mit den gespeicherten Mustern verglichen werden. Falls ein Muster 
M### Definition von „Spaß“
msöglich) die Motivation und Spaß bei der Ausführung der Aufgabe bringen könnten. Was könnte die Aufgabe interessant machen? Was könnte man daraus lernen?

### Definition von „erledigt“
Legen Sie die Bedingungen fest, unter denen die verantwortliche Person die Aufgabe als erledigt betrachten kann.Beschreibung



## Aufgabe 2: Wie in der Vorlage für Aufgabe 1## Aufgabe 1:  Umsetzung der Mustererkennung
### Beschreibung
Definieren Sie die Aufgabe so, dass die verantwortliche Person sie ausführen kann, ohne weitere Erklärungen zu benötigen. Definieren Sie alle Abhängigkeiten oder Informationen, die geklärt werden müssen. Definieren Sie, wie die Lösung aussehen muss, damit sie akzeptabel ist.

### Definition von „Spaß“
möglich) die Motivation und Spaß bei der Ausführung der Aufgabe bringen könnten. Was könnte die Aufgabe interessant machen? Was könnte man daraus lernen?

### Definition von „erledigt“
Legen Sie die Bedingungen fest, unter denen die verantwortliche Person die Aufgabe als erledigt betrachten kann.Beschreibung

Die Hardware 