#include "Devices/PID_TC.h"
#include "Devices/Serial_TC.h"
#include "Devices/EEPROM_TC.h"

// class variable
PID_TC* PID_TC::_instance = nullptr;

// implement singleton
PID_TC* PID_TC::instance() {
  if (!_instance) {
    _instance = new PID_TC();
  }
  return _instance;
}
//implement constructor
PID_TC::PID_TC() {
  double Kp, Ki, Kd;
  EEPROM_TC* eeprom = EEPROM_TC::instance();
  Kp = eeprom->getKP();
  Ki = eeprom->getKI();
  Kd = eeprom->getKD();
  if (isnan(Kp)) {
    Kp = 100000;
  }
  if (isnan(Ki)) {
    Ki = 0;
  }
  if (isnan(Kd)) {
    Kd = 0;
  }
//   std::cout << "------------------------------" << Kp << "-----------------------" << std::endl;
  pPID = new PID(&input, &output, &set_point, Kp, Ki, Kd, DIRECT);  // Starting the PID, Specify the links and initial tuning parameters
  pPID->SetMode(AUTOMATIC);
  pPID->SetSampleTime(1000);
  pPID->SetOutputLimits(0, WINDOW_SIZE);
}

// instance functions
void PID_TC::logToSerial() {
  Serial_TC::instance()->print_PID(pPID->GetKp(), pPID->GetKi(), pPID->GetKd(), output);
}