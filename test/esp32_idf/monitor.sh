#!/usr/bin/env bash

ESP32_DEV=/dev/ttyUSB0
CWD="$(pwd)"
WD="/code"

docker run -it --rm \
       --device $ESP32_DEV \
       -v $CWD:$WD \
       -w $WD \
       espressif/idf:v4.1.1\
       idf.py -p $ESP32_DEV monitor

