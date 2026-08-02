# Project File Structure

This repository is organized as follows:

```text
vnav-c/
├── .gitignore
├── Makefile
├── README.md
├── include/
│   ├── aircraft.h
│   ├── control.h
│   ├── dynamics.h
│   ├── efcs.h
│   ├── guard.h
│   ├── terminal.h
│   └── ui.h
└── src/
	├── control.c
	├── dynamics.c
	├── guard.c
	├── main.c
	├── terminal.c
	└── ui.c
```

## Folder Overview

- `include/` stores public header files for the aircraft model, flight guard, EFCS, control, terminal, and UI layers.
- `src/` stores the C source files for the simulation and UI.
- `bin/` and `obj/` are created by the build (`make`) and contain the compiled binary and intermediate object files; these are build artifacts and not checked into source control.

## File Overview

- `Makefile` controls the build process and produces `bin/vnav_efcs` when built.
- `README.md` describes the repository structure and development status.
- `.gitignore` lists files and folders that Git should ignore (build artifacts, etc.).
- `include/aircraft.h` declares the `Aircraft` composition used by the simulation model.
- `include/control.h` defines shared control data and thread function declarations used by the input thread and main loop.
- `include/dynamics.h` declares the flight dynamics structures and update interface used by the physics step.
- `include/efcs.h` declares the EFCS (autopilot/VNAV) state interface.
- `include/guard.h` declares the flight guard limits and clamp helpers that keep the simulation within safe bounds.
- `include/terminal.h` declares terminal setup/restore functions used to enable raw input mode.
- `include/ui.h` declares the panel drawing function used by the text UI.
- `src/control.c` contains the shared control state, input parsing, and input thread logic.
- `src/dynamics.c` implements the core flight dynamics update (altitude, pitch, elevator actuation and vertical speed).
- `src/guard.c` implements the guard helper functions (clamping limits).
- `src/main.c` contains the lightweight program entry point and simulation loop.
- `src/terminal.c` contains terminal raw-mode helpers.
- `src/ui.c` contains the text-based interface rendering.
