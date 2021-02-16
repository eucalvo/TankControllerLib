#include "Devices/TempProbe_TC.h"

//  class instance variables
/**
 * static variable for singleton
 */
TempProbe_TC* TempProbe_TC::_instance = nullptr;

//  class methods
/**
 * static member function to return singleton
 */
TempProbe_TC* TempProbe_TC::instance() {
  if (!_instance) {
    _instance = new TempProbe_TC();
  }
  return _instance;
}

//  instance methods
/**
 * constructor (private so clients use the singleton)
 */
TempProbe_TC::TempProbe_TC() {
  thermo.begin(MAX31865_3WIRE);  // Start pt100 temperature probe with 3 wire configuration
  // Remove these lines when Adafruit_MAX31865_CI has proper initialization
#ifdef MOCK_PINS_COUNT
  thermo.setRTD(0);
  thermo.setFault(0);
#endif
}
