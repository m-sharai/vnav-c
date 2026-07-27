// efcs.h
// Author: Maksym Sharai
// Date: 27/06/2026
// Declares the flight control system state and update interface.

#ifndef EFCS_H
#define EFCS_H

#include "dynamics.h"
#include "guard.h"

typedef struct {

  double target_altitude_ft;

  double pitch_gain;

  int vnav_active;

} EFCS;

void efcs_init(EFCS *self);
void efcs_update(EFCS *efcs, FlightDynamics *flight_dynamics,
                 FlightGuard *guard, double delta_time_ms);

#endif // EFCS_H