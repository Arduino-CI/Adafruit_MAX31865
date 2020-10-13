#include <bitset>
#include <iostream>
#include <vector>

#include "Arduino.h"
#include "ArduinoUnitTests.h"
#include "Adafruit_MAX31865_CI.h"

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

const byte rs = 1;
const byte rw = 2;
const byte enable = 3;
const byte d0 = 10;
const byte d1 = 11;
const byte d2 = 12;
const byte d3 = 13;
const byte d4 = 14;
const byte d5 = 15;
const byte d6 = 16;
const byte d7 = 17;

class BitCollector : public DataStreamObserver {
private:
  bool fourBitMode;
  bool showData;
  vector<int> pinLog;
  GodmodeState *state;

public:
  BitCollector(bool showData = false, bool fourBitMode = true)
      : DataStreamObserver(false, false) {
    this->fourBitMode = fourBitMode;
    this->showData = showData;
    state = GODMODE();
    state->reset();
    state->digitalPin[enable].addObserver("lcd", this);
  }

  ~BitCollector() { state->digitalPin[enable].removeObserver("lcd"); }

  virtual void onBit(bool aBit) {
    if (aBit) {
      int value = 0;
      value = (value << 1) + state->digitalPin[rs];
      value = (value << 1) + state->digitalPin[rw];
      value = (value << 1) + state->digitalPin[d7];
      value = (value << 1) + state->digitalPin[d6];
      value = (value << 1) + state->digitalPin[d5];
      value = (value << 1) + state->digitalPin[d4];
      value = (value << 1) + state->digitalPin[d3];
      value = (value << 1) + state->digitalPin[d2];
      value = (value << 1) + state->digitalPin[d1];
      value = (value << 1) + state->digitalPin[d0];
      pinLog.push_back(value);
      if (showData) {
        std::cout.width(5);
        std::cout << std::right << value << " : " << ((value >> 9) & 1) << "  "
                  << ((value >> 8) & 1) << "  ";
        if (fourBitMode) {
          std::bitset<4> bits((value >> 4) & 0x0F);
          if ((pinLog.size() - 1) % 2) {
            std::cout << "    ";
          }
          std::cout << bits;
        } else {
          std::bitset<8> bits(value & 0xFF);
          std::cout << bits;
        }
        std::cout << std::endl;
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
  //Implementation Not Finnished
  vector<int> expected{48, 48, 48, 32, 32, 128, 0, 192, 0, 16, 0, 96};
  Adafruit_MAX31865_Test thermo(d4, d5, d6, d7);
  BitCollector pinValues(false); // test the next line
  thermo.begin(MAX31865_3WIRE);
  assertTrue(true);

}

unittest(readRTD) {
  //Not Yet Implemented
  Adafruit_MAX31865_Test thermo(d4, d5, d6, d7);
  assertTrue(true);
}

unittest(get_temp) {
  //Not Yet Implemented
  Adafruit_MAX31865_Test thermo(d4, d5, d6, d7);
  assertTrue(true);
}