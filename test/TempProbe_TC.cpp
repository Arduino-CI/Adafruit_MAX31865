#include "Arduino.h"
#include "ArduinoUnitTests.h"

#ifdef ARDUINO_CI
#include "Adafruit_MAX31865_CI.h"
#else
#include "Adafruit_MAX31865.h"
#endif

// Adafruit MAX31865
// This device is an interface and sensor between a thermocouple (temperature
// sensor). With The Adafruit MAX31865 you can either read a resistance, or a
// fault.
//
// Device I/O:
// This device has 5 pins: Vin (3V or 5V powersupply, the same as the
// microcontroler), GND (Ground), CLK (Clock), SDO (MOSI: Master Out Slave In),
// SDI (MISO: Master In Slave Out), and CS (Slave Select).
//
// Connection with the thermocouple:
// The Adafruit MAX31865 can connect to three different types of thermocouples,
// two wire, three wire, or four wire. You'll need to look at the sensor's
// documentation to find the wiring requirments. The board has four pins used
// for connection with the thermocouple, they are labeled on the board: RTD+
// (Resistance Positive), RTD- (Resistance Negative), F+ (Fault Plus), and F-
// (Fault Negative).
//
// Using Adafruit MAX31865
// There are 5 functions needed to use Adafruit MAX31865: the constructor,
// begin, readRTD (Read Resistance), temperature(), readFault(), and
// clearFault().
//
// Here is a description of those functions:
//
// Constructor:
// To use the constructor you will have to set which pins you want to use, the
// functions are labled below. Adafruit_MAX31865 thermo = Adafruit_MAX31865(CS
// (Slave Select), DI (MOSI), DO (MISO), CLK (Clock));
//
// Begin:
// Call this after calling the constructor and before anything else. Returns
// true if successful. Default is a 2 wire thermocouple but you can specify 2,3,
// and 4 wire by passing in MAX31865_2WIRE, MAX31865_3WIRE, and MAX31865_4WIRE.
// bool successful = thermo.begin(max31865_numwires_t x = MAX31865_2WIRE);
//
// Read Resistance:
// Returns the resitance of the device.
// uint16_t rtd = thermo.readRTD();
//
// Get Temperature:
// To get the temperature you will need to know the Nominal Resistance, and the
// Resistor Reference of your temperature sensor. This must be set according to
// your thermocouple. Read your thermocouple
//  manual to find these values.
// float temp = thermo.temperature(float RTDnominal, float refResistor)
//
// Read Fault:
// Returns a fault number in hex. You can compare with returned fault with the
// defualt fault values given below uint8_t fault = thermo.readFault();
//
// Faults:
// MAX31865_FAULT_HIGHTHRESH (RTD High Threshold)
// MAX31865_FAULT_LOWTHRESH (RTD Low Threshold)
// MAX31865_FAULT_REFINLOW (REFIN- > 0.85 x Bias)
// MAX31865_FAULT_REFINHIGH (REFIN- < 0.85 x Bias - FORCE- open)
// MAX31865_FAULT_RTDINLOW (RTDIN- < 0.85 x Bias - FORCE- open)
// MAX31865_FAULT_OVUV (Under/Over Voltage)
//
// Clear Fault:
// Once Fault is read clear fault so that it returns to its default state of 0
// wich is no fault. thermo.clearFault();
//
// How to use the Device:
// To use the device you must call the constructor, call begin, and then you can
// either call readRTD(), or temperature(). Once you have read either, or both
// you can check for a fault, use the data accordingly, and then clear the fault
// before reading again.
//
// How to use this TC_tempProbe class:
// Call the constructor TC_tempProbe tempProbe = TC_tempProbe();
// Since this class is build for Tank Controller class, it will automatically
// set the device to a three wire thermocouple, set the pins that the tank
// controller has delegated for it, and it has values for RTDnominal, and the
// refResistore. This class is pretty straightforward and you can the functions
// and how to call them below.

class TempProbe_TC {
private:
  Adafruit_MAX31865 thermo = Adafruit_MAX31865(45, 43, 41, 39);

  // RTDnominal, and refResistor for pt100
  const int RTDnominal = 100;
  const int refResistor = 430;

public:
  TempProbe_TC() {
    thermo.begin(MAX31865_3WIRE); // Start pt100 temperature probe with 3 wire configuration
  }

  uint16_t getResistance() { return thermo.readRTD(); }
  float getTemperature() { return thermo.temperature(RTDnominal, refResistor); }
  uint8_t readFault() { return thermo.readFault(); }
  void clearFault() { thermo.clearFault(); }

#ifdef ARDUINO_CI

  void setRTD(uint16_t newResistance) { thermo.setRTD(newResistance); }
  void setFault(uint8_t newFault) { thermo.setFault(newFault); }

#endif
};

unittest(readRTD_TC_TempProbe) {
  std::cout << std::endl;
  uint16_t expectedRTD = 0;
  TempProbe_TC tempProbe;
  uint16_t testRTD = tempProbe.getResistance();
  assert(testRTD == expectedRTD);
  std::cout << std::endl;
}

unittest(getTemp_TC_TempProbe) {
  std::cout << std::endl;
  float expectedTemp = -242.02;
  TempProbe_TC tempProbe;
  float testTemp = tempProbe.getTemperature();
  assert(testTemp == expectedTemp);
  std::cout << std::endl;
}

unittest(readFault_TC_TempProbe) {
  std::cout << std::endl;
  TempProbe_TC tempProbe;
  uint8_t testFault = tempProbe.readFault();
  assertEqual(0, testFault);
  uint8_t expectedFault = 1;
  tempProbe.setFault(expectedFault);
  testFault = tempProbe.readFault();
  assert(testFault == expectedFault);
  std::cout << std::endl;
}

unittest(clearFault_TC_TempProbe) {
  std::cout << std::endl;
  uint8_t setFault = 1;
  uint8_t expectedFault = 0;
  TempProbe_TC tempProbe;
  tempProbe.setFault(setFault);
  tempProbe.clearFault();
  uint8_t testFault = tempProbe.readFault();
  assert(testFault == expectedFault);
  std::cout << std::endl;
}

unittest_main()
