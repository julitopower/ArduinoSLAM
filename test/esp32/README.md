# ESP32 & MPU9250

This directory contains an Arduino sketch that connects an ESP32 DevkitC with an IMU MPU-9250 via I2C. The ESP32 acts as master, and the IMU sensor as slave.

The only dependency is```MPU9250_asukiaaa```.

# Circuit

It is possible to directly connect the ESP32 board and the sensor, since both use 3.3 volts. The circuit works without pull-up resitors, but adding them is probably a better way to go about it.

# Related work

We have also developped the code to connect a Raspberry Pi to the IMU via I2C, and the code to connect a Raspberry Pi as I2C master to an ESP32. Those examples are not available in this repository yet.

# References

* https://github.com/asukiaaa/MPU9250_asukiaaa
* [MPU-9250 Product Specification](https://invensense.tdk.com/wp-content/uploads/2015/02/PS-MPU-9250A-01-v1.1.pdf)
* [MPU-9250 Register Map](https://cdn.sparkfun.com/assets/learn_tutorials/5/5/0/MPU-9250-Register-Map.pdf)
* [ESP32 DevKitC pinout](https://components101.com/sites/default/files/component_pin/ESP32-Pinout.png)
