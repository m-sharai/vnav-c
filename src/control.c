// control.c
// Author: Maksym Sharai
// Date: 26/06/2026
// Handles keyboard input and altitude target updates for the simulation.

#include "../include/control.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/aircraft.h"
#include "../include/ui.h"

// Shared control state used by both threads.
ControlPanel control_panel = {.target_altitude = 10000.0,
                              .target_speed = 250.0, // ! WARNING: Placeholder
                              .is_running = 1,
                              .input_buffer = "",
                              .input_length = 0,
                              .lock = PTHREAD_MUTEX_INITIALIZER};

// Reads one character at a time and updates the shared control panel state.
// Numbers are collected into a small text buffer until Enter is pressed.
void *input_listener_thread(void *arg) {
  (void)arg;

  while (control_panel.is_running) {
    // getchar() blocks until the user presses a key.
    int input_char = getchar();

    // Stop the simulation cleanly if the input stream is closed.
    if (input_char == EOF) {
      pthread_mutex_lock(&control_panel.lock);
      control_panel.is_running = 0;
      pthread_mutex_unlock(&control_panel.lock);
      break;
    }

    // Lock the shared state before changing anything.
    pthread_mutex_lock(&control_panel.lock);

    // Enter submits the current altitude value.
    if (input_char == '\n' || input_char == '\r') {
      control_panel.input_buffer[control_panel.input_length] = '\0';

      if (control_panel.input_length > 0) {
        char *end_ptr = NULL;

        // A single minus sign is treated as the shutdown command.
        if (strcmp(control_panel.input_buffer, "-") == 0) {
          control_panel.is_running = 0;
        } else {
          // Parse the altitude as a whole number of feet.
          long new_alt = strtol(control_panel.input_buffer, &end_ptr, 10);

          // Only accept whole-foot integer values.
          if (end_ptr != control_panel.input_buffer && *end_ptr == '\0') {
            if (new_alt < 0) {
              // Negative values are used as the exit signal.
              control_panel.is_running = 0;
            } else {
              // Store the accepted altitude for the simulation.
              control_panel.target_altitude = (double)new_alt;
            }
          }
        }
      }

      // Clear the buffer after a submission so the next input starts fresh.
      control_panel.input_length = 0;
      control_panel.input_buffer[0] = '\0';

      // Backspace removes the last typed character.
    } else if (input_char == 127 || input_char == '\b') {
      if (control_panel.input_length > 0) {
        control_panel.input_length--;
        control_panel.input_buffer[control_panel.input_length] = '\0';
      }

      // Accept only digits and an optional leading minus sign.
    } else if ((input_char >= '0' && input_char <= '9') || input_char == '-') {
      if (control_panel.input_length < INPUT_BUFFER_SIZE - 1) {
        control_panel.input_buffer[control_panel.input_length++] =
            (char)input_char;
        control_panel.input_buffer[control_panel.input_length] = '\0';
      }
    }

    // Release the shared state so the renderer can read it.
    pthread_mutex_unlock(&control_panel.lock);
  }

  // Move the shell prompt to the next line after the thread stops.
  printf("\n");
  fflush(stdout);

  return NULL;
}

// Reads the latest shared state and redraws the panel about 50 times per
// second.
void run_simulation(ControlPanel *control_panel) {
  if (control_panel == NULL) {
    return;
  }

  // Initialize the complete Boeing 738 aircraft system
  Aircraft b738;
  aircraft_init(&b738);

  // 50 Hz tick rate (20 ms)
  const double delta_time_ms = 20.0;

  while (control_panel->is_running) {
    // Local copies keep the render step short and reduce lock time.
    double new_target_alt = 10000.0;
    char input_buffer[INPUT_BUFFER_SIZE];

    // 1. Copy the shared state while holding the mutex.
    pthread_mutex_lock(&control_panel->lock);
    new_target_alt = control_panel->target_altitude;
    strncpy(input_buffer, control_panel->input_buffer, INPUT_BUFFER_SIZE);
    input_buffer[INPUT_BUFFER_SIZE - 1] = '\0';
    pthread_mutex_unlock(&control_panel->lock);

    // 2. Feed pilot target altitude to EFCS
    b738.efcs.target_altitude_ft = new_target_alt;

    // 3. Advance aircraft control and physics pipeline by 1 tick
    aircraft_step(&b738, delta_time_ms);

    // Redraw from the top of the terminal each frame.
    printf("\n\n\n\n\n");
    print_panel(&b738, input_buffer);

    // Sleep for 20 ms to aim for a 50 Hz refresh rate.
    usleep(20000);
  }
}