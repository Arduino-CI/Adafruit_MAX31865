#define Adafruit_MAX31865_Test Adafruit_MAX31865_Base
#include "Common.cpp"

unittest(testingClassName) {
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  assertEqual("Adafruit_MAX3186_Base", thermo.className());
}

// The following tests are in BaseClass.cpp instead of Common.cpp
// because initial input values for resistance and fault from the 
// MAX31865 are initialized differently for testing purposes. 
// Since we don't have actual I/O from the device, we need to 
// initialize values in testing so we can manually change 
// them.

unittest(read_RTD) {
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
  thermo.readRTD();
  assertTrue(pinValues.isEqualTo(expected));
}

unittest(read_fault) {
  vector<int> expected{0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  BitCollector pinValues(false);
  uint8_t fault = thermo.readFault();
  assertEqual(0, fault);
  assertTrue(pinValues.isEqualTo(expected));
}

unittest(clear_fault) {
  vector<int> expected{0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2,
                       2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2};
  Adafruit_MAX31865_Test thermo(ss, mosi, miso, sck);
  thermo.begin(MAX31865_3WIRE);
  BitCollector pinValues(false);
  thermo.clearFault();
  assertTrue(pinValues.isEqualTo(expected));
}

unittest_main()
