// aircraft.h
// Author: Maksym Sharai
// Date: 27/06/2026
// Declares the aircraft composition used by the simulation model.

#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "dynamics.h"
#include "efcs.h"
#include "guard.h"

typedef struct {
  FlightDynamics flight_dynamics;
  FlightGuard guard;
  EFCS efcs;
} Aircraft;

void aircraft_init(Aircraft *self);
void aircraft_step(Aircraft *aircraft, double delta_time_ms);

#endif // AIRCRAFT_H