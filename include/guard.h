// guard.h
// Author: Maksym Sharai
// Date: 27/06/2026
// Declares the flight guard limits used to keep the simulation within safe
// bounds.

#ifndef GUARD_H
#define GUARD_H

typedef struct {
  // Minimum and maximum altitude limits in feet.
  double min_alt_ft;
  double max_alt_ft;

  // Minimum and maximum indicated airspeed limits in knots.
  double min_ias_kts;
  double max_ias_kts;

  // Minimum and maximum pitch limits in degrees.
  double min_pitch_deg;
  double max_pitch_deg;

  // Minimum and maximum vertical speed limits in feet per minute.
  double min_vs_fpm;
  double max_vs_fpm;
} FlightGuard;

// Initialize a FlightGuard with the default operating limits.
void guard_init(FlightGuard *self);

// Clamp a generic value between a minimum and maximum bound.
double guard_clamp(double value, double min, double max);
// Clamp a target altitude to the allowed altitude range.
double guard_clamp_alt(FlightGuard *guard, double target_alt_ft);
// Clamp a target vertical speed to the allowed vertical speed range.
double guard_clamp_vs(FlightGuard *guard, double target_vs_fpm);

#endif // GUARD_H