# ESP32-IDF - Raspberry Pi - Led - I2C

This projects contains esp32-idf and raspberry pi code. It sets the esp32 as an I2C slave, and the Raspberry Pi as the I2C master. The master then sends commands to the esp32 board to control the on/off status of a led. With this project we demonstrate the use the esp32 as I2C slave, and Raspberry Pi as master, which is something we need for the actual final SLAM architecture, which is roughly as follows:

* esp32 I2C master -> Reads -> MCU-9250
* esp32 -> Controls -> Servo that turns an ultrasonic sensor
* esp32 -> Reads -> Ultrasonic sensor
* esp32 -> commands -> DC motors
* Raspberry Pi I2C master -> Writes navigation commands -> esp32 I2C slave
* Raspberry Pi I2C master -> reads <angle, distance, time, imu> -> esp32 I2C slave


For the ESP32 code, it uses the ESP32-IDF SDK. The scripts provided use the officially published Docker image to build, flash and monitor the code. Board is assumed to be accessible through ```/dev/ttyUSB0```. Change the execution scripts if yours uses a different serial device.

# ESP32 scripts

* ```build.sh```: Build and flash
* ```cms.sh```: Execute an arbitrary command on the build container
* ```clean.sh```: Equivalent to ```make clean```
* ```interactive.sh```: Interactive terminal session inside the build container
* ```monitor.sh```: Connecto to the board and monitor execution

# Build

## ESP32

1. Connect the esp32 board to a USB port
2. Execute ```./build.sh```
3. Verify it works by executing ```./monitor.sh```

## Raspberry Pi

The code is small enough to be directly compiled on the Raspberry. It requires ```make``` and ```gcc >= 4.9```, and [wiringpi](http://wiringpi.com/). You can install the library by executing:

```
sudo apt-get install wiringpi
```

To build follow these steps:

1. ssh into your Raspberry
2. Go to the root of the package
3. Execute ```make```
