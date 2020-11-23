#include <Arduino.h>
#include <assert.h>
#include <bitset>
#include <iostream>
#include <vector>

#include "Adafruit_MAX31865_CI.h"
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
  BitCollector(bool showData = false) : DataStreamObserver(false, false) {
    this->showData = showData;
    state = GODMODE();
    state->reset();
    state->digitalPin[sck].addObserver("thermo", this);
  }

  ~BitCollector() { state->digitalPin[sck].removeObserver("thermo"); }

  virtual void onBit(bool aBit) {
    if (aBit && !state->digitalPin[ss]) {
      int value = 0;
      value = (value << 1) + state->digitalPin[mosi];
      value = (value << 1) + state->digitalPin[miso];
      pinLog.push_back(value);
      if (showData) {
        std::cout << value << ", ";
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
  vector<int> expected{2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2,
                       2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2};
  BitCollector pinValues(true);
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  assertTrue(pinValues.isEqualTo(expected));
}

unittest(get_temp) {
  vector<int> expected{0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0,
                       2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2,
                       2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                       2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2,
                       2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  BitCollector pinValues(true);
  thermo.temperature(100.0, 430.0);
  assertTrue(pinValues.isEqualTo(expected));
}
