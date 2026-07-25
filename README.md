# Project File Structure

This repository is organized as follows:

```text
vnav-c/
├── .gitignore
├── Makefile
├── README.md
├── bin/
├── include/
│   ├── control.h
│   ├── terminal.h
│   └── ui.h
├── obj/
└── src/
	├── control.c
	├── main.c
	├── terminal.c
	└── ui.c
```

## Folder Overview

- `bin/` stores compiled output binaries.
- `include/` stores public header files.
- `obj/` stores intermediate object files created during builds.
- `src/` stores the C source files.

## File Overview

- `Makefile` controls the build process.
- `README.md` describes the repository structure.
- `.gitignore` lists files and folders that Git should ignore.
- `include/control.h` defines shared control data and thread function declarations.
- `include/terminal.h` declares terminal setup and cleanup functions.
- `include/ui.h` declares the panel drawing function.
- `src/main.c` contains the lightweight program entry point.
- `src/control.c` contains the shared control state and input thread logic.
- `src/terminal.c` contains the terminal raw-mode implementation.
- `src/ui.c` contains the text-based interface rendering.
