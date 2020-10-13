#define Adafruit_MAX31865_Test Adafruit_MAX31865_Base
#include "Common.cpp"

unittest(testingClassName) {
  Adafruit_MAX31865_Test thermo(d4, d5, d6, d7);
  assertEqual("Adafruit_MAX3186_Base", thermo.className());
}

unittest_main()
