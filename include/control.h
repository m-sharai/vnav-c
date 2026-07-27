// control.h
// Author: Maksym Sharai
// Date: 26/06/2026
// Declares the shared control panel state and input handling interface.

#ifndef CONTROL_H
#define CONTROL_H

#include <pthread.h>
#include <stddef.h>

#define INPUT_BUFFER_SIZE 32

typedef struct {
  // The altitude that the user wants the simulation to fly to.
  double target_altitude;

  // Placeholder for airspeed data used by the panel.
  double target_speed;

  // Set to zero when the program should stop running.
  int is_running;

  // Text typed by the user before pressing Enter.
  char input_buffer[INPUT_BUFFER_SIZE];

  // How many characters are currently stored in the input buffer.
  size_t input_length;

  // Protects shared data between the input thread and the render loop.
  pthread_mutex_t lock;
} ControlPanel;

// Shared state used by both the input thread and the simulation loop.
extern ControlPanel control_panel;

// Reads typed characters and updates the shared control state.
// Pressing Enter submits a new target altitude.
void *input_listener_thread(void *arg);

// Main update loop that reads the shared state and redraws the panel.
void run_simulation(ControlPanel *control_panel);

#endif // CONTROL_H