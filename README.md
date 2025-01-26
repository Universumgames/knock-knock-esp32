# Klap-Klap

- [Klap-Klap](#klap-klap)
  - [Description](#description)
  - [Important files and directories](#important-files-and-directories)
  - [Contributing Setup](#contributing-setup)
  - [Project setup](#project-setup)

URL to repository: https://github.com/Universumgames/knock-knock-esp32

## Description
This project is a simple knock pattern recognizer for a door or chest. The knock pattern is stored on an SD card connected to the ESP32. The knock pattern is recognized by the ESP32 and if the pattern is correct, the door or chest is unlocked. The lock is controlled by a solenoid lock. The project is written in C with the ESP-IDF and uses the PlatformIO IDE. The project is based on the ESP32-C3 microcontroller.

## Important files and directories
- [`documentation/sprint_plan.md`](documentation/sprint_plan.md): Contains the Sprint Plan and detailed description by whom the task was completed
- [`documentation/backlog.md`](documentation/backlog.md): Contains the backlog, a detailed beakdown of the seperate task of this project
- [`src/`](src/): Contains the source code of the project
- [`test/`](test/): Contains the test code of the project
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

## Contributing Setup
- install clang-format
  - Debian/Ubuntu: `sudo apt install clang-format`
  - Arch: `sudo pacman -S clang`
  - MacOS: `brew install clang-format`
  - Windows: `pip3 install clang-format`
- configure githooks
  - run `git config core.hooksPath .githooks`
- configure IDE to use clang-format
  - VS Code: install the `Clang-Format` extension (https://marketplace.visualstudio.com/items?itemName=xaver.clang-format)
  - CLion: enable clang-format (https://www.jetbrains.com/help/clion/clangformat-as-alternative-formatter.html)

## Project setup

1. Install VS Code
2. Install PlatformIO extension
3. open PIO Home -> Platforms -> Espressif 32 -> Install (should be installed automatically when opening the project via PlatformIO)
4. building the project by clicking on checkmark in the bottom left corner (when hovering over it, it says: "Build")
5. run tests via the `pio test` command in the terminal
