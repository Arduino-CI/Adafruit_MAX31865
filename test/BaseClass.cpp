#define Adafruit_MAX31865_Test Adafruit_MAX31865_Base
#include "Common.cpp"

unittest(testingClassName) {
  std::cout << std::endl;
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  assertEqual("Adafruit_MAX3186_Base", thermo.className());
  std::cout << std::endl;
}

unittest_main()
