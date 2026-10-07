# Interactive Fiction Game: Detroit: Become Human

## Description
This project is an interactive fiction game for the DTEK-V board that recreates the first mission from "Detroit: Become Human". It features a decision-based narrative with multiple possible endings, where choices, collected items, and Quick Time Events (QTEs) impact the outcome. The game is programmed in C and uses ANSI sequences to render ASCII art alongside text directly in the terminal, creating a retro visual experience.

## Prerequisites
To build and run this project, you need the following tools:
* RISC-V Toolchain
* USB-Blaster drivers
* JTAG-Software
* DTEK-V Board Tools

**Note:** The easiest way to meet these requirements is to use the official IS1200 Debian Virtual Machine, which has all necessary tools preinstalled.

## How to Run
1. Open your terminal and navigate to the project directory:
   ```bash
   cd <path_to_your_project_folder>
   ```
2. Start the JTAG daemon:
   ```bash
   jtagd --user-start
   ```
3. Compile the project:
   ```bash
   make
   ```
4. Flash and run the binary on the DTEK-V board:
   ```bash
   dtekv-run main.bin
   ```
**Note:** Don't forget to reset the board before running the program.
