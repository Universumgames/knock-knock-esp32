# Klap-Klap

- [Klap-Klap](#klap-klap)
  - [Description](#description)
  - [Important files and directories](#important-files-and-directories)
  - [Project setup](#project-setup)


## Description
This project is a simple knock pattern recognizer for a door or chest. The knock pattern is stored on an SD card connected to the ESP32. The knock pattern is recognized by the ESP32 and if the pattern is correct, the door or chest is unlocked. The lock is controlled by a solenoid lock. The project is written in C with the ESP-IDF and uses the PlatformIO IDE. The project is based on the ESP32-C3 microcontroller.

## Important files and directories
- [`src/](src/): Contains the source code of the project
- [`test/](test/): Contains the test code of the project
- [`platformio.ini`](platformio.ini): Contains the configuration of the project
- [`README.md`](README.md): Contains the description of the project
- [`LICENSE`](LICENSE): Contains the license of the project
- [`CHANGELOG.md`](CHANGELOG.md): The changelog 
- [`lib/`](lib/): Contains the self written libraries
- [`documentation/`](documentation/): Contains the documentation of the project
- [`datasheets/`](datasheets/): Contains the datasheets for the used components
- [`docker/`](docker/): Contains the docker files to build the platformio environment in a docker container
- [`pinout.txt`](pinout.txt): Contains the pinout of the used microcontroller
- [`pcb/`](pcb/): Contains the pcb files


## Project setup

1. Install VS Code
2. Install PlatformIO extension
3. open PIO Home -> Platforms -> Espressif 32 -> Install (should be installed automatically when opening the project via PlatformIO)
4. building the project by clicking on checkmark in the bottom left corner (when hovering over it, it says: "Build")
5. run tests via the `pio test` command in the terminal
