#!/usr/bin/env bash

################################################################################
#
# Equivalent to make clean
#
################################################################################

docker run --rm -v $PWD:/code -w /code espressif/idf:v4.1.1 idf.py clean
