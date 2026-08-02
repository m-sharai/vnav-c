// ui.h
// Author: Maksym Sharai
// Date: 26/06/2026
// Declares the panel rendering interface for the terminal UI.

#ifndef UI_H
#define UI_H

#include "aircraft.h"

// Draws the text-based control panel and shows the current input buffer.
void print_panel(Aircraft *aircraft, const char *input_buffer);

#endif // UI_H