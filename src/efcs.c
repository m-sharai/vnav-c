#include "../include/efcs.h"

#include <stddef.h>

void efcs_init(EFCS *self) {
  if (self == NULL) {
    return;
  }

  // Default target matches dynamics initial altitude (10,000 ft)
  self->target_altitude_ft = 10000.0; // ! PLACEHOLDER

  // Proportional Gain (Kp) for pitch guidance:
  // Determines how aggressively elevator responds to altitude error.
  // 0.001 deg of elevator per 1 foot of error (e.g., 1000 ft error = 1.0 deg
  // command)
  self->pitch_gain = 0.001;

  // VNAV engaged by default
  self->vnav_active = 1;
}

void efcs_update(EFCS *self, FlightDynamics *dynamics, const FlightGuard *guard,
                 double delta_time_ms) {
  if (self == NULL || dynamics == NULL || guard == NULL || delta_time_ms <= 0) {
    return;
  }

  // Do nothing if VNAV is disengaged
  if (!self->vnav_active) {
    return;
  }

  // 1. Sanitize Pilot Target Input against B738 Envelope Limits
  double safe_target_alt = guard_clamp_alt(guard, self->target_altitude_ft);

  // 2. Compute Altitude Error (Target - Current)
  double alt_error = safe_target_alt - dynamics->altitude_ft;

  // 3. Proportional Control Law (Altitude Capture Logic)
  // Desired Elevator Angle = Error * Proportional Gain
  double commanded_elevator = alt_error * self->pitch_gain;

  // 4. Command Elevator Deflection within Mechanical Limits (-20 to +10 deg)
  // The dynamics module will smoothly move the actual surface toward this
  // target
  // ! Change implementation (no hardcoded limits)
  dynamics->elevator.target_angle_deg =
      guard_clamp(commanded_elevator, -20.0, 10.0);
}