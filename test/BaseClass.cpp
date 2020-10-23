#define Adafruit_MAX31865_Test Adafruit_MAX31865_Base
#include "Common.cpp"

unittest(testingClassName) {
  std::cout << std::endl;
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  assertEqual("Adafruit_MAX3186_Base", thermo.className());
  std::cout << std::endl;
}

unittest(read_RTD) {
  std::cout << std::endl;
  vector<int> expected{0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 
                        2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 
                        0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 
                        0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 
                        0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                        0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 
                        0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 
                        0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
                        2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 
                        2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 
                        0, 0, 0, 0, 0, 0, 0, 0};
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  BitCollector pinValues(false);
  thermo.readRTD();
  assertTrue(pinValues.isEqualTo(expected));
  std::cout << std::endl;
}

unittest(read_fault) {
  std::cout << std::endl;
  vector<int> expected{0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  BitCollector pinValues(false);
  uint8_t fault = thermo.readFault();
  assertEqual(0, fault);
  assertTrue(pinValues.isEqualTo(expected));
  std::cout << std::endl;
}

unittest(clear_fault) {
  std::cout << std::endl;
  vector<int> expected{0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 
                        2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 
                        0, 0, 0, 0, 0, 2};
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  BitCollector pinValues(false);
  thermo.clearFault();
  assertTrue(pinValues.isEqualTo(expected));
  std::cout << std::endl;
}

unittest_main()
