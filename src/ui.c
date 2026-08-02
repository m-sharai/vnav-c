// ui.c
// Author: Maksym Sharai
// Date: 26/06/2026
// Renders the text-based control panel and displays the current input state.

#include "../include/ui.h"

#include <stdio.h>

// Draws the current telemetry values and the partially typed input.
// The escape codes move the cursor back to the top so the same screen area
// gets reused for every frame.
void print_panel(Aircraft *aircraft, const char *input_buffer) {
  // Hide the cursor so the screen looks cleaner while the panel updates.
  printf("\e[?25l");
  // Move back to the top-left corner before redrawing the whole panel.
  printf("\e[H");

  // Target altitude in feet
  const double TARG_ALT_FT = aircraft->efcs.target_altitude_ft;
  // Current altitude in feet
  const double CUR_ALT_FT = aircraft->flight_dynamics.altitude_ft;
  // Current vertical speed in feet per minute
  const double CUR_VS_FPM = aircraft->flight_dynamics.vertical_speed_fpm;
  // Current indicated airspeed in knots
  const double CUR_IAS_KTS = aircraft->flight_dynamics.ias_kts;
  // Current pitch angle in degrees
  const double CUR_PITCH_DEG = aircraft->flight_dynamics.pitch_deg;

  // These lines are placeholders for the aircraft state.
  printf("TARGET ALT: %6.0f ft\n", TARG_ALT_FT);
  printf("ALT: %6.0f ft  |  VS: %4.0f fpm\n", CUR_ALT_FT, CUR_VS_FPM);
  printf("IAS: %3.0f   kts |  PITCH: %2.0f deg\n", CUR_IAS_KTS, CUR_PITCH_DEG);

  // Print the prompt and keep the current buffer visible.
  printf("\nEnter new TARGET ALT: %s\033[K", input_buffer);

  // Flush right away so the user sees the new frame without delay.
  fflush(stdout);
}