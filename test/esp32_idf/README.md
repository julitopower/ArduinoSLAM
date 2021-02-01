# ESP32-IDF

This is an example of coding an ESP32 using the ESP32-IDF SDK. The scripts provided use the officially published Docker image to build, flash and monitor the code.

Board is assumed to be accessible through ```/dev/ttyUSB0```. Change the execution scripts if yours uses a different serial device.

# Usage

* ```build.sh```: Build and flash
* ```cms.sh```: Execute an arbitrary command on the build container
* ```clean.sh```: Equivalent to ```make clean```
* ```interactive.sh```: Interactive terminal session inside the build container
