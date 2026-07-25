#include "../include/control.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/ui.h"

// Shared control state used by both threads.
ControlPanel control_panel = {.target_altitude = 10000.0,
                              .target_speed = 250.0,
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
        double new_alt = strtod(control_panel.input_buffer, &end_ptr);

        // Only accept input that starts with a real number.
        if (end_ptr != control_panel.input_buffer) {
          if (new_alt < 0.0) {
            // Negative values are used as the exit signal.
            control_panel.is_running = 0;
          } else {
            control_panel.target_altitude = new_alt;
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
      // Accept only digits, a decimal point, and a minus sign.
    } else if ((input_char >= '0' && input_char <= '9') || input_char == '.' ||
               input_char == '-') {
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
  while (control_panel->is_running) {
    // Local copies keep the render step short and reduce lock time.
    double new_target_alt = 10000.0;
    char input_buffer[INPUT_BUFFER_SIZE];

    // Copy the shared state while holding the mutex.
    pthread_mutex_lock(&control_panel->lock);
    new_target_alt = control_panel->target_altitude;
    strncpy(input_buffer, control_panel->input_buffer, INPUT_BUFFER_SIZE);
    input_buffer[INPUT_BUFFER_SIZE - 1] = '\0';
    pthread_mutex_unlock(&control_panel->lock);

    // Redraw from the top of the terminal each frame.
    printf("\n\n\n\n\n");
    print_panel(new_target_alt, input_buffer);

    // Sleep for 20 ms to aim for a 50 Hz refresh rate.
    usleep(20000);
  }
}