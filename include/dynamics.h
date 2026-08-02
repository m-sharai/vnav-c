// dynamics.h
// Author: Maksym Sharai
// Date: 27/06/2026
// Declares the flight dynamics structures used by the simulation.

#ifndef DYNAMICS_H
#define DYNAMICS_H

#include "guard.h"
typedef struct {
  double current_angle_deg;
  double target_angle_deg;
} Elevator;

typedef struct {
  double altitude_ft;
  double vertical_speed_fpm;
  double ias_kts;
  double pitch_deg;

  Elevator elevator;
} FlightDynamics;

void dynamics_init(FlightDynamics *self);

void dynamics_update(FlightDynamics *dynamics, FlightGuard *guard,
                     double delta_time_ms);

#endif // DYNAMICS_H