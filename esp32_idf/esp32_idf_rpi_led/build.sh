#!/usr/bin/env bash

set -e

################################################################################
#
# Build and Flash ESP32
#
################################################################################
ESP32_DEV=/dev/ttyUSB0
CWD="$(pwd)"
WD="/code"

docker run --rm \
       -v $CWD:$WD \
       -w $WD \
       espressif/idf:v4.1.1\
       idf.py build

if [[ $1 == "-f" ]]
then
docker run --rm \
       --device $ESP32_DEV \
       -v $CWD:$WD \
       -w $WD \
       espressif/idf:v4.1.1\
       idf.py -p $ESP32_DEV -b 921600 flash
fi

