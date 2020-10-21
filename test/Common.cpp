#include <bitset>
#include <iostream>
#include <vector>
#include <assert.h> 

#include "Arduino.h"
#include "ArduinoUnitTests.h"
#include "Adafruit_MAX31865_CI.h"

const byte ss = 10;
const byte mosi = 11;
const byte miso = 12;
const byte sck = 13;

class BitCollector : public DataStreamObserver {
private:
  bool showData;
  vector<int> pinLog;
  GodmodeState *state;

public:
  BitCollector(bool showData = false)
      : DataStreamObserver(false, false) {
    this->showData = showData;
    state = GODMODE();
    state->reset();
    state->digitalPin[sck].addObserver("thermo", this);
    // std::cout << "BitCollector()" <<  std::endl;
  }

  ~BitCollector() { state->digitalPin[sck].removeObserver("thermo"); }

  virtual void onBit(bool aBit) {
    // std::cout << "onBit()" <<  std::endl;
    if (aBit && !state->digitalPin[ss]) {
      int value = 0;
      value = (value << 1) + state->digitalPin[mosi];
      value = (value << 1) + state->digitalPin[miso];
      pinLog.push_back(value);
      if (showData) {
        // std::cout.width(2);
        // std::bitset<2> bits(value & 0xFF);
        std::cout << value << ", ";
        // std::cout << std::endl;
      }
    }
  }

  bool isEqualTo(const vector<int> &expected) {
    if (pinLog.size() != expected.size()) {
      return false;
    }
    for (int i = 0; i < pinLog.size(); ++i) {
      if (pinLog.at(i) != expected.at(i)) {
        return false;
      }
    }
    return true;
  }

  virtual String observerName() const { return "BitCollector"; }
};

unittest(begin) {
  std::cout << std::endl;
  vector<int> expected{2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2};
  BitCollector pinValues(false);
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  assertTrue(pinValues.isEqualTo(expected));
  std::cout << std::endl;
}

unittest(get_temp) {
  std::cout << std::endl;
  vector<int> expected{0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  BitCollector pinValues(false);
  thermo.temperature(100.0, 430.0);
  assertTrue(pinValues.isEqualTo(expected));
  std::cout << std::endl;
}

//Purposely Didn't Include Base Level Tests for Read Fault, Clear Fault, and Read Resistance in Low Level Tests 
//because base value will not be the same as CI value because the Base value set fault is an empty register and 
//the CI fault is initiallized to 0. The Max31865 Device will suply these values at runtime therefore testing is
//not adequeate in these areas anyways. With high level tests these tests should still be comprehensive enough. 