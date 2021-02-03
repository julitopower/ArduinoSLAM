# Arduino & ESP32 & Raspberry Pi SLAM

This repository contains a series of code, evolving into a SLAM implementation for a chip mobile robot. We are not there yet, but are having a lot of fun through the journey.

# Structure

* **./sketches** - contains arduino sketches for Arduino Uno R3 and ESP32
* **./esp32_idf** - contains ESP32 code using Espressif IDF (Iot Development Framework), which is independent of the Arduino IDE, and offers a lot more flexibility. For insance Espressif ESP32 Arduino Core does not support setting a esp32 devices as I2C slave.
