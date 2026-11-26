VEHICLE MANAGEMENT SYSTEM (C)

Files:
- main.c      : menu and program entry point
- vehicle.h   : Vehicle structure, enum, and function declarations
- vehicle.c   : add, view, update, and remove operations
- file.c      : binary file save/load functions
- vehicles.dat: created automatically when the program saves data

Compile with GCC:
    gcc -std=c99 -Wall -Wextra -pedantic main.c vehicle.c file.c -o vehicle

Run:
    Windows: vehicle.exe
    Linux/macOS: ./vehicle

Notes:
- All source files should be in the same folder when compiling.
- The program creates/updates vehicles.dat in the current working directory.
- Vehicle IDs must be unique.
- New vehicles start with AVAILABLE status.
