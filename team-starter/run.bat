@echo off
cd /d "%~dp0"
gcc -Wall -Wextra src/main.c src/utils.c src/vehicle.c src/booking.c src/rental.c src/billing.c -o vrs.exe
if errorlevel 1 (
    echo Build failed. Read the error above.
    pause
    exit /b 1
)
vrs.exe
pause
