#define Adafruit_MAX31865_Test Adafruit_MAX31865
#include "Common.cpp"

unittest(testingClassName) {
  std::cout << std::endl;
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  assertEqual("Adafruit_MAX3186_CI", thermo.className());
  std::cout << std::endl;
}

unittest(begin_high) {
  std::cout << std::endl;
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  bool testBegin = thermo.begin(MAX31865_3WIRE);
  assertTrue(testBegin);
  std::cout << std::endl;
}

unittest(readRTD_high) {
  std::cout << std::endl;
  uint16_t expectedRTD = 0;
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  uint16_t testRTD = thermo.readRTD();
  assert(testRTD == expectedRTD);
  std::cout << std::endl;

}

unittest(getTemp_high) {
  std::cout << std::endl;
  float expectedTemp = -242.02;
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  float testTemp =  thermo.temperature(100.0, 430.0);
  assert(testTemp ==  expectedTemp);
  std::cout << std::endl;
}

unittest(readFault_high) {
  std::cout << std::endl;
  uint8_t expectedFault = 1;
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  thermo.setFault(expectedFault);
  uint8_t testFault =  thermo.readFault();
  assert(testFault == expectedFault);
  std::cout << std::endl;
}

unittest(clearFault_high) {
  std::cout << std::endl;
  uint8_t setFault = 1;
  uint8_t expectedFault = 0;
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  thermo.setFault(setFault);
  thermo.clearFault();
  uint8_t testFault = thermo.readFault();
  assert(testFault == expectedFault);
  std::cout << std::endl;
}

unittest_main()
