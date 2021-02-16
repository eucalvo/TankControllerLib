#include <Arduino.h>
#include <ArduinoUnitTests.h>

#include "TankControllerLib.h"

/**
 * year has to be range: 2000-2099
 * following command only runs this test
 * bundle exec arduino_ci.rb --skip-examples-compilation
 * --testfile-select=DateTime.cpp
 */

unittest(constructor) {
  DateTime_TC dt(2021, 2, 15, 1, 48, 24);
  assertEqual(2021, dt.year());
  assertEqual(2, dt.month());
  assertEqual(15, dt.day());
  assertEqual(1, dt.hour());
  assertEqual(48, dt.minute());
  assertEqual(24, dt.second());
}

unittest(now) {
  DateTime_TC now = DateTime_TC::now();
  assertTrue(now.year() >= 2020);
  assertTrue(now.month() >= 1);
  assertTrue(now.day() >= 1);
  assertTrue(now.hour() >= 0);
  assertTrue(now.minute() >= 0);
  assertTrue(now.second() >= 0);
}

//  void printToSerial();   // DigitalClockDisplay.ino
unittest(printToSerial) {
  GodmodeState *state = GODMODE();
  state->reset();
  assertEqual("", state->serialPort[0].dataOut);
  DateTime_TC dateTime = DateTime_TC(2020, 11, 26, 18, 55, 15);
  dateTime.printToSerial();
  assertEqual("2020-11-26 18:55:15\r\n", state->serialPort[0].dataOut);
}

// DoDirectoryMaintenance.ino
unittest(yearMonthAsPath) {
  DateTime_TC date = DateTime_TC(2020, 9, 26);
  char buffer[9];
  date.yearMonthAsPath(buffer, sizeof(buffer));
  assertEqual("/2020/09", buffer);
}

unittest(setAsCurrent) {
  DateTime_TC jan(2021, 1, 15, 1, 48, 24);
  DateTime_TC dob(2001, 2, 20, 3, 50, 10);
  dob.setAsCurrent();

  DateTime_TC now1 = DateTime_TC::now();
  assertEqual(2001, now1.year());
  assertEqual(2, now1.month());
  assertEqual(20, now1.day());
  assertEqual(3, now1.hour());
  assertEqual(50, now1.minute());
  assertEqual(10, now1.second());
}
unittest_main()
