# MISSION-TIMER
This repository contains firmware for a mission timer, 
designed to showcase state machine implementation using a custom FSM framework. 
Upon activation, the timer enters a countdown state, during which a red LED blinks to 
indicate status. The system supports real-time defusal, allowing transition to a safe state 
at any point before completion. Upon reaching zero, the timer executes a predefined terminal 
event.

## Prerequisites
The following are required to build this project:
1. [CMake](https://cmake.org/download/)
2. [Python](https://www.python.org/downloads/)
3. [Ninja](https://github.com/ninja-build/ninja)

## Build
The following platforms are supported for this project:
1. ESP-IDF
2. Mbed OS


### ESP-IDF platform prerequisites
This platform implements all the BSP requirements for various ports that use ESP-IDF.
#### ESP-IDF installation requirements
* [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html)(version 5.2.3)

### Mbed-OS platform prerequisites
This platform implements all the BSP requirements for various ports that use Mbed OS.
#### Mbed OS installation requirements
* [Mbed OS](https://os.mbed.com/docs/mbed-os/v6.16/build-tools/install-and-set-up.html)(version 6.15.1)
* [GNU Arm Embedded Toolchain](https://developer.arm.com/downloads/-/gnu-rm)(version 10.3-2021.10 )

The following ports are supported:
1. ESP32
2. STM32F429ZI

### ESP32
Using ESP-IDF
#### Build
From the project root, run:

``
python3 build.py build-application -p ESP32 -pl ESP_IDF --compile
``

#### Flashing instructions
Connect the ESP32 to your computer and run:

``
python3 build.py build-application -p ESP32 -pl ESP_IDF --flash
``

### STM32F429ZI
Using Mbed OS
#### Build instructions
From the project root, run:

``
python3 build.py build-application -p STM32F429ZI -pl mbed-os --compile
``

#### Flashing requirements
1. [stlink](https://github.com/stlink-org/stlink)(version 1.6.0)
#### Flashing instructions
Connect the STM32G070 to your computer and run:

``
python3 build.py build-application -p STM32F429ZI -pl mbed-os --flash 
``

## Documentation
The documentation will be found [here](https://example.com/)


