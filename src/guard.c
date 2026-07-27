// guard.c
// Author: Maksym Sharai
// Date: 27/06/2026
// Implements the flight guard helpers used to clamp aircraft values within safe
// limits.

#include "../include/guard.h"

// Initialize a FlightGuard with the default safe operating limits.
void guard_init(FlightGuard *self) {
  // Default altitude limits in feet.
  self->min_alt_ft = 0.0;
  self->max_alt_ft = 41000.0;

  // Default indicated airspeed limits in knots.
  self->min_ias_kts = 145.0;
  self->max_ias_kts = 340.0;

  // Default pitch limits in degrees.
  self->min_pitch_deg = -15.0;
  self->max_pitch_deg = 25.0;

  // Default vertical speed limits in feet per minute.
  self->min_vs_fpm = -7900.0;
  self->max_vs_fpm = 6000.0;

  return;
}

// Clamp a generic value to the provided range.
double guard_clamp(double value, double min, double max) {
  if (value < min) {
    return min;
  }

  if (value > max) {
    return max;
  }

  return value;
}

// Clamp a target altitude to the allowed altitude range.
double guard_clamp_alt(FlightGuard *guard, double target_alt_ft) {
  double min_alt_ft = guard->min_alt_ft;
  double max_alt_ft = guard->max_alt_ft;

  if (target_alt_ft < min_alt_ft) {
    return min_alt_ft;
  }

  if (target_alt_ft > max_alt_ft) {
    return max_alt_ft;
  }

  return target_alt_ft;
}

// Clamp a target vertical speed to the allowed vertical speed range.
double guard_clamp_vs(FlightGuard *guard, double target_vs_fpm) {
  double min_vs_fpm = guard->min_vs_fpm;
  double max_vs_fpm = guard->max_vs_fpm;

  if (target_vs_fpm < min_vs_fpm) {
    return min_vs_fpm;
  }

  if (target_vs_fpm > max_vs_fpm) {
    return max_vs_fpm;
  }

  return target_vs_fpm;
}