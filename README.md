# gaggia_classic_pro_pid
PID interface for the Gaggia Classic Pro. Most likely will work on the Silvia as well.


## Current Status
C++ Skeleton for the ESP platform

## ESP32 IO
* Input
  * Rotary encoder + built-in push button
  * MAX31865 (SPI)
  * Steam button
  
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

### Links
https://protofusion.org/wordpress/2019/02/gaggia-classic-seamless-pid-upgrade/comment-page-1/?unapproved=806734&moderation-hash=bb7ce05928096aa19418bb35727e8a61#comment-806734