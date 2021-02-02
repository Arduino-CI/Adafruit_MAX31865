#!/bin/bash

# this script has two use cases
# 1 - CI testing and local development of this library only (SHALLOW)
# 2 - Development of this library AND the supporting libraries
# comment this out if you want full depth for the supporting libraries (case 2)
export SHALLOW='--depth 1 --branch master --single-branch '
# use this if you started with SHALLOW and now want the full repository with history
# git fetch --unshallow

# add missing libraries
export GITHUB="https://github.com/Arduino-CI"
if [ ! -d "./Adafruit_BusIO" ] ; then
  git clone $SHALLOW $GITHUB/Adafruit_BusIO.git
fi
