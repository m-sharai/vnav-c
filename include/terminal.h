// terminal.h
// Author: Maksym Sharai
// Date: 26/06/2026
// Declares the terminal helpers used to manage console input and display.

#ifndef TERMINAL_H
#define TERMINAL_H

// Clears the console before the program starts drawing the panel.
void clear_console(void);

// Switches the terminal into raw mode so key presses are read one by one.
void enable_raw_input_mode(void);

// Restores the terminal settings back to normal text mode.
void disable_raw_input_mode(void);

#endif // TERMINAL_H