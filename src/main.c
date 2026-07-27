// main.c
// Author: Maksym Sharai
// Date: 26/06/2026
// Starts the terminal UI, input loop, and simulation update cycle.

#include <pthread.h>
#include <stdlib.h>

#include "../include/control.h"
#include "../include/terminal.h"

// Program entry point.
// This only prepares the terminal, starts the input thread, runs the
// simulation loop, and then cleans up shared resources.
int main(void) {
  // Clear the screen once so the panel starts from a clean view.
  clear_console();

  // Raw mode lets the program react to each key press immediately.
  enable_raw_input_mode();

  // Always restore the terminal when the program exits.
  atexit(disable_raw_input_mode);

  // The input thread updates the target altitude while the main thread redraws.
  pthread_t input_thread_id;
  pthread_create(&input_thread_id, NULL, input_listener_thread, NULL);

  // Run the panel until the user asks the program to stop.
  run_simulation(&control_panel);

  // Wait for the input thread to finish before destroying shared state.
  pthread_join(input_thread_id, NULL);
  pthread_mutex_destroy(&control_panel.lock);

  return 0;
}