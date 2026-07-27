# Project File Structure

This repository is organized as follows:

```text
vnav-c/
├── .gitignore
├── Makefile
├── README.md
├── bin/
├── include/
│   ├── aircraft.h
│   ├── control.h
│   ├── dynamics.h
│   ├── efcs.h
│   ├── guard.h
│   ├── terminal.h
│   └── ui.h
├── obj/
└── src/
	├── control.c
	├── guard.c
	├── main.c
	├── terminal.c
	└── ui.c
```

## Folder Overview

- `bin/` stores compiled output binaries.
- `include/` stores public header files for the aircraft model, flight guard, EFCS, control, terminal, and UI layers.
- `obj/` stores intermediate object files created during builds.
- `src/` stores the C source files.

## File Overview

- `Makefile` controls the build process.
- `README.md` describes the repository structure.
- `.gitignore` lists files and folders that Git should ignore.
- `include/aircraft.h` declares the aircraft composition used by the simulation model.
- `include/control.h` defines shared control data and thread function declarations.
- `include/dynamics.h` declares the flight dynamics structures used by the simulation.
- `include/efcs.h` declares the flight control system state and update interface.
- `include/guard.h` declares the flight guard limits and clamp helpers.
- `include/terminal.h` declares terminal setup and cleanup functions.
- `include/ui.h` declares the panel drawing function.
- `src/guard.c` implements the guard helpers used to clamp values within safe limits.
- `src/main.c` contains the lightweight program entry point.
- `src/control.c` contains the shared control state and input thread logic.
- `src/terminal.c` contains the terminal raw-mode implementation.
- `src/ui.c` contains the text-based interface rendering.
