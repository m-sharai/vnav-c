#include "../include/ui.h"

#include <stdio.h>

// Draws the current telemetry values and the partially typed input.
// The escape codes move the cursor back to the top so the same screen area
// gets reused for every frame.
void print_panel(double target_alt, const char *input_buffer) {
  // Hide the cursor so the screen looks cleaner while the panel updates.
  printf("\e[?25l");
  // Move back to the top-left corner before redrawing the whole panel.
  printf("\e[H");

  // These lines are placeholders for the aircraft state.
  printf("TARGET ALT: %6.0f ft\n", target_alt);
  printf("ALT: 10000 ft  |  VS: 2100 fpm\n");
  printf("IAS: 250   kts |  PITCH: 7 deg\n");

  // Print the prompt and keep the current buffer visible.
  printf("\nEnter new TARGET ALT: %s\033[K", input_buffer);

  // Flush right away so the user sees the new frame without delay.
  fflush(stdout);
}