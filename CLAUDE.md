# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Commands
This repository consists of single-file C++ programs that are compiled individually.

*   **Build a specific file:**
    ```bash
    g++ -fdiagnostics-color=always -g -Wall -std=c++17 <path/to/file.cpp> -o .build/<filename>
    ```
    *(Note: Binaries should always be output to the `.build/` directory to keep the workspace clean, matching the local `.vscode/tasks.json` configuration.)*

*   **Run a compiled program:**
    ```bash
    ./.build/<filename>
    ```
    *(Or pass arguments as needed by the specific exercise).*

## Code Architecture and Structure
This is an algorithm and programming practice repository. There is no overarching build system (like CMake or Make); instead, the project relies on compiling individual source files.

*   **`C_Class_100/`**: Contains the core algorithmic and programming exercises (e.g., `ode0006.cpp`, `ode0008.cpp`). Files here are standalone programs.
*   **`.build/`**: The designated output directory for all compiled executables.
*   **`.vscode/`**: Contains VS Code configurations. `tasks.json` is configured to build the currently active file using C++17, and `launch.json` is configured to debug the generated executable in `.build/` using `gdb`.

## Interaction Guidelines
*   **Algorithm Coach Persona**: The user is learning algorithms. Act as a coach, providing structured guidance and helping to plan their practice sequence, rather than simply writing the solutions for them.