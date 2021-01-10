# gaggia_classic_pro_pid
PID interface for the Gaggia Classic Pro. Most likely will work on the Silvia as well.


## Current Status
PID example
Currently working on finishing the MAX31865 driver
Need to settle on a design for the fault
Verified working display and display driver
Need to design interface

## ESP32 IO
* Input
  * Rotary encoder + built-in push button
  * MAX31865 (SPI)
  * Steam button
  * Brew button
  
* Output
  * 40 A SSR
  * Display

## Components
* ESP32-WROOM32 - ESP32DEVKIT1
* 40 A SSR - 3V 
* Rotary Encoder
* 2.8" ILI9341 240x320 SPI LCD Display Touch
* pt100 via MAX31865 SPI

## Software Modules
* LVGL and driver for the LCD Display
* Rotary encoder driver
* PID algorithm

## Steps
1) Develop PID algorithm
2) Develop rotary encoder driver
3) Develop temperature sensor driver
4) Attempt simulating with PID
5) Develop display driver
6) Get LVGL to work with display
7) Combine all for finished product

## CLion and WSL Setup
* Use this [script](https://github.com/abobija/idfx) to flash and monitor from WSL2 without USB support
* Make sure IDF_PATH is setup in CLion's environmental variable list
* CMake Variables
  * -DIDF_PATH=/home/druep/Development/sdk/esp-idf  
  * -DIDF_PYTHON_ENV_PATH=/home/druep/.espressif/python_env/idf4.3_py3.8_env -G Ninja 
  * -DCMAKE_TOOLCHAIN_FILE=~/Development/sdk/esp-idf/tools/cmake/toolchain-esp32.cmake 
  * -DTARGET=esp32
  
I've had issues with CLion using the proper python interpreter. The Espressif toolchain sets up a virtual environment.
Clion kept using /usr/bin/python. So, to fix this I just installed the required Python modules
  /usr/bin/python -m pip install -r $IDF_PATH/requirements.txt
  
## Build Steps
Building is fairly straightforward and uses CMake and your generator of choice
If building for the ESP32, then make sure to pass the CMAKE_TOOLCHAIN_FILE variable
You can also just use the ./scripts/build-esp32.sh

You can build without specifying the toolchain, but it currently only builds some
tests that don't rely on espressif toolchains.

## GUI Simulation
It is possible to [*mostly] test the gui from Windows. To do so, the flag `-DBUILD_LVGL_SIMULATION=TRUE` should be passed to CMake

### Links
https://protofusion.org/wordpress/2019/02/gaggia-classic-seamless-pid-upgrade/comment-page-1/?unapproved=806734&moderation-hash=bb7ce05928096aa19418bb35727e8a61#comment-806734