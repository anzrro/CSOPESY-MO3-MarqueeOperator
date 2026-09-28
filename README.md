# CSOPESY-MO3-MarqueeOperator

## Group Members

- Romero, Aaron Zander
- Tiangson, Ezekiel Martinez
- Vito, Luis Andre
- Laus, Rance Lenard

---

## Project Overview

This project is an Operating System shell emulator developed for **CSOPESY**. It features an interactive Command Line Interface (CLI) that accepts system commands and supports multithreaded background ASCII animation (a marquee banner) running simultaneously without interrupting or distorting user input.

---

## Entry Point

- The entry function `main()` is located in **`main.cpp`**, which initializes and starts the `Console` class.

---

## Build and Run Instructions

### Command Line (GCC / MinGW)

1. Open Command Prompt in the project folder.
2. Compile using `g++`:
   ```bash
   g++ main.cpp console.cpp commands.cpp marquee.cpp -o main.exe
   ```
3. Run "main.exe" directly into the Command Prompt
