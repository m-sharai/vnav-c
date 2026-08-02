// efcs.h
// Author: Maksym Sharai
// Date: 27/06/2026
// Declares the flight control system state and update interface.

#ifndef EFCS_H
#define EFCS_H

#include "dynamics.h"
#include "guard.h"

typedef struct {

  // Target altitude in feet for vertical navigation.
  double target_altitude_ft;

  // Gain used to convert altitude error into a pitch command.
  double pitch_gain;

  // Non-zero when the vertical navigation controller is active.
  int vnav_active;

} EFCS;

// Initialize the EFCS state to default values.
void efcs_init(EFCS *self);

// Update the flight control system using dynamics, guard state, and time step.
void efcs_update(EFCS *efcs, FlightDynamics *flight_dynamics,
                 const FlightGuard *guard, double delta_time_ms);

#endif // EFCS_H