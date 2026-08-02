// aircraft.c
// Author: Maksym Sharai
// Date: 02/08/2026
// Coordinates aircraft initialization and step updates for the simulation.

#include "../include/aircraft.h"

#include <stddef.h>

void aircraft_init(Aircraft *self) {
  // Ignore initialization requests for a null aircraft.
  if (self == NULL) {
    return;
  }

  // Initialize the aircraft's flight dynamics model.
  dynamics_init(&self->flight_dynamics);

  // Initialize the guard subsystem.
  guard_init(&self->guard);

  // Initialize the electronic flight control system.
  efcs_init(&self->efcs);
}

void aircraft_step(Aircraft *self, double delta_time_ms) {
  if (self == NULL || delta_time_ms <= 0) {
    return;
  }

  // Update the electronic flight control system first.
  efcs_update(&self->efcs, &self->flight_dynamics, &self->guard, delta_time_ms);

  // Advance the flight dynamics model.
  dynamics_update(&self->flight_dynamics, &self->guard, delta_time_ms);
}