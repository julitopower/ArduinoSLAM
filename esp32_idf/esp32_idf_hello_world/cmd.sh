#!/usr/bin/env bash

################################################################################
#
# Run an arbitrary command on the build container in non-interactive mode
#
################################################################################

ESP32_DEV=/dev/ttyUSB0
CWD="$(pwd)"
WD="/code"

docker run --rm \
       --device $ESP32_DEV \
       -v $CWD:$WD \
       -w $WD \
       espressif/idf:v4.1.1\
       "$@"
