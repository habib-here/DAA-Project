@echo off
echo Compiling Social Network Analysis Program...
echo.

g++ -o social_network.exe main.cpp

if %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
    echo.
    echo Run the program with: social_network.exe
    echo.
    pause
) else (
    echo Compilation failed! Please check for errors.
    pause
)
