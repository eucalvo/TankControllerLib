#include <PID_v1.h>
#include <Arduino.h>


class PID_TC {
public:
  // declare singleton
  static PID_TC* instance();
  // declare constructor
  PID_TC();
  //instance functions
  void logToSerial();
  PID *getPID() { return pPID; }
private:
  // class
  static PID_TC* _instance;

  // declare necessary private variables
  double input = 0.0;
  double output = 0.0;
  double set_point = 0.0;
  const int WINDOW_SIZE = 10000;
  PID *pPID; 

};
