#!/bin/bash

# set up directories
bundle exec ensure_arduino_installation.rb

# get custom version of Adafruit_BusIO
git clone https://github.com/Arduino-CI/Adafruit_BusIO.git
mv Adafruit_BusIO "$(bundle exec arduino_library_location.rb)/Adafruit BusIO"
