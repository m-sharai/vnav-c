// terminal.c
// Author: Maksym Sharai
// Date: 26/06/2026
// Provides terminal setup and screen-control helpers for the UI.

#include "../include/terminal.h"

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// Saved terminal settings so raw mode can be turned off later.
static struct termios original_terminal_settings;
// Tracks whether the original settings were stored successfully.
static int terminal_settings_saved = 0;

// Clears the screen in a portable way.
void clear_console(void) {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Turns off line buffering and terminal echo so each key is handled directly.
void enable_raw_input_mode(void) {
  if (tcgetattr(STDIN_FILENO, &original_terminal_settings) == 0) {
    struct termios raw_terminal_settings = original_terminal_settings;

    // ICANON makes input wait for Enter, and ECHO prints typed keys.
    raw_terminal_settings.c_lflag &= (tcflag_t) ~(ICANON | ECHO);
    // Read one character at a time without waiting.
    raw_terminal_settings.c_cc[VMIN] = 1;
    raw_terminal_settings.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw_terminal_settings) == 0) {
      terminal_settings_saved = 1;
    }
  }
}

// Restores the normal terminal behavior so the shell works normally again.
void disable_raw_input_mode(void) {
  if (terminal_settings_saved) {
    tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal_settings);
    terminal_settings_saved = 0;
  }
}