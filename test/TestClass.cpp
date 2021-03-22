#define Adafruit_MAX31865_Test Adafruit_MAX31865
#include "Common.cpp"

unittest(testingClassName) {
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  assertEqual("Adafruit_MAX3186_CI", thermo.className());
}

unittest(begin_high) {
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  bool testBegin = thermo.begin(MAX31865_3WIRE);
  assertTrue(testBegin);
}

unittest(readRTD_high) {
  uint16_t expectedRTD = 0;
  uint16_t expectedSetRTD = 3;
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  uint16_t testRTD = thermo.readRTD();
  assert(testRTD == expectedRTD);
  thermo.setRTD(expectedSetRTD);
  testRTD = thermo.readRTD();
  assert(testRTD == expectedSetRTD);
}

unittest(getTemp_high) {
  float expectedTemp = -242.02;
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  float testTemp = thermo.temperature(100.0, 430.0);
  assert(testTemp == expectedTemp);
}

unittest(readFault_high) {
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  uint8_t expectedFault = 1;
  uint8_t testFault = thermo.readFault();
  assertEqual(0, testFault);
  thermo.setFault(expectedFault);
  testFault = thermo.readFault();
  assert(testFault == expectedFault);
}

unittest(clearFault_high) {
  uint8_t newFault = 1;
  uint8_t expectedFault = 0;
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  thermo.setFault(newFault);
  thermo.clearFault();
  uint8_t testFault = thermo.readFault();
  assert(testFault == expectedFault);
}

unittest(set_temperature) {
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  // ensure that we don't have any endless loops!
  for (float t = 0.0; t <= 100.0; t += 0.1) {
    thermo.setTemperature(t);
  }
  thermo.setTemperature(0);
  assertEqual(7621, thermo.readRTD());
  thermo.setTemperature(10);
  assertEqual(7918, thermo.readRTD());
  thermo.setTemperature(90);
  assertEqual(10266, thermo.readRTD());
  thermo.setTemperature(100);
  assertEqual(10554, thermo.readRTD());

}
unittest_main()
