#include <Arduino.h>
#include <ArduinoUnitTests.h>
#include "Devices/PID_TC.h"
#include "Devices/Serial_TC.h"
#include <PID_v1.h>

unittest(singleton) {
  PID_TC *singleton1 = PID_TC::instance();
  PID_TC *singleton2 = PID_TC::instance();
  assertEqual(singleton1, singleton2);
}

unittest(constructor) {
  PID_TC *singleton = PID_TC::instance();
  PID *pPID = singleton->getPID();
  assertEqual(255.0, pPID->GetKp());
  assertEqual(255.0, pPID->GetKi());
  assertEqual(255.0, pPID->GetKd());
  assertEqual(AUTOMATIC, pPID->GetMode());
}

unittest(logToSerial) {
  GodmodeState* state = GODMODE();
  PID_TC *singleton = PID_TC::instance();
  singleton->logToSerial();
  assertEqual("Kp:255.0 Ki:255.0 Kd:255.0\r\nPID output (s): 0.0\r\n", state->serialPort[0].dataOut);
}

unittest_main()