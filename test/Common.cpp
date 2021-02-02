#include <Arduino.h>
#include <assert.h>
#include <bitset>
#include <iostream>
#include <vector>

#include "Adafruit_MAX31865_CI.h"
#include "ArduinoUnitTests.h"

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
        std::cout << value << " ";
      }
    }
  }

  bool isEqualTo(const vector<int> &expected) {
    std::cout << __FILE__ << ':' << __LINE__ << " isEqualTo()" << std::endl;
    if (pinLog.size() != expected.size()) {
      return false;
    }
    for (int i = 0; i < pinLog.size(); ++i) {
      if (pinLog.at(i) != expected.at(i)) {
        std::cerr << "pinLog.at(" << i << ") = " << pinLog.at(i)
                  << " while expected.at(" << i << ") is " << expected.at(i)
                  << std::endl;
        std::cout << __FILE__ << ':' << __LINE__ << " isEqualTo() returning false" << std::endl;
        return false;
      }
    }
    std::cout << __FILE__ << ':' << __LINE__ << " isEqualTo() returning true" << std::endl;
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
  BitCollector pinValues(false);
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  std::cout << __FILE__ << ':' << __LINE__ << " begin()" << std::endl;
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
  BitCollector pinValues(false);
  thermo.temperature(100.0, 430.0);
  std::cout << __FILE__ << ':' << __LINE__ << " getTemp()" << std::endl;
  assertTrue(pinValues.isEqualTo(expected));
}
