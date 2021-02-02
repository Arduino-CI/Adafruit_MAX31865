#!/bin/bash

# Remove this file when https://github.com/Arduino-CI/arduino_ci/issues/278 is fixed

# arduino_ci runs this script in its GitHub Action because it is referenced by CUSTOM_INIT_SCRIPT
# arduino_ci ensures that the script is run in the libraries directory

export SHALLOW='--depth 1 --branch master --single-branch '
# If you want the full repository with history, execute the following
# git fetch --unshallow

# add missing libraries
export GITHUB="https://github.com/Arduino-CI"
if [ ! -d "./Adafruit_BusIO" ] ; then
  git clone $SHALLOW $GITHUB/Adafruit_BusIO.git
fi
