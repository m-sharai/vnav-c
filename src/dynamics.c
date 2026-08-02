// dynamics.c
// Author: Maksym Sharai
// Date: 01/08/2026
// Implements the basic flight dynamics update used by the simulation.

#include "../include/dynamics.h"
#include "../include/guard.h"

#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // M_PI

void dynamics_init(FlightDynamics *self) {
  if (self == NULL) {
    return;
  }

  self->altitude_ft = 10000.0;
  self->vertical_speed_fpm = 0.0;
  self->ias_kts = 250.0;
  self->pitch_deg = 0.0;

  self->elevator.current_angle_deg = 0.0;
  self->elevator.target_angle_deg = 0.0;
}

void dynamics_update(FlightDynamics *self, FlightGuard *guard,
                     double delta_time_ms) {
  if (self == NULL || guard == NULL || delta_time_ms <= 0) {
    return;
  }

  // Convert delta time to seconds for standard rate calculation
  double dt_sec = delta_time_ms / 1000.0;

  // 1. Actuator Dynamics (Elevator Lag)
  double elevator_error =
      self->elevator.target_angle_deg - self->elevator.current_angle_deg;
  double actuator_speed = 5.0; // Filter coefficient for smooth movement.

  double new_elevator_angle_deg = self->elevator.current_angle_deg +
                                  elevator_error * actuator_speed * dt_sec;

  // Hard airframe limits: Clamp target_elevator_angle_deg to safe limit.
  // ! COMPLETE GUARD TO CONTAIN ELEVATOR LIMITS
  new_elevator_angle_deg = guard_clamp(new_elevator_angle_deg, -20.0, 10.0);
  self->elevator.current_angle_deg = new_elevator_angle_deg;

  // 2. Pitch dynamics
  double pitch_rate_deg_per_sec = self->elevator.current_angle_deg * 0.8;
  double new_pitch_deg = self->pitch_deg + pitch_rate_deg_per_sec * dt_sec;

  // Hard airframe limits: Clamp new_pitch_deg to safe limit
  new_pitch_deg = guard_clamp_pitch(guard, new_pitch_deg);
  self->pitch_deg = new_pitch_deg;

  // 3. Trigonometric Vertical Speed (VS) calculation
  double pitch_rad = self->pitch_deg * (M_PI / 180.0);
  double ias_fpm = self->ias_kts * 101.268; // 1 knot = 101.268 fpm
  self->vertical_speed_fpm = ias_fpm * sin(pitch_rad);

  // 4. Altitude integration
  // Convert feet per minute (fpm) to feet gained during this tick.
  double ft_per_sec = self->vertical_speed_fpm / 60.0;
  self->altitude_ft += ft_per_sec * dt_sec;
}