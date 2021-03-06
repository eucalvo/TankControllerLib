/**
 * SetTankID.h
 *
 * Change Tank ID
 */
#pragma once
#include "NumberCollectorState.h"

class SetTankID : public NumCollectorState {
public:
  SetTankID(TankControllerLib* tc) : NumCollectorState(tc) {
  }
  String name() {
    return "SetTankID";
  }
  const char* prompt() {
    return "Set Tank ID#    ";
  };
  void setValue(double value);
};
