# The Last Hope – Embedded Game on TM4C123GH6PM
Small embedded game developed in C for the TM4C123GH6PM microcontroller using Keil uVision. The project integrates DAC output, SysTick timer, GPIO inputs, and a Nokia 5110 display to create a fully functional interactive game running on simulated LaunchPad hardware.

---

## Features
  - Game loop implemented with SysTick-based timing.
  - Audio generation using DAC output.
  - Input handling via GPIO switches.
  - UI rendered on Nokia 5110 LCD driver.
  - Tested using TExaS simulation tools (LaunchPad DLL and Sitronix LCD emulator).

---

## Repository Structure
- Docs/                  → Diagrams, project documents, original PPT
- TheLastHope/           → Keil uVision project (sources, headers, startup)
- README.md

---

## Tools & Technologies
  - Languages: C
  - IDE: Keil uVision
  - Hardware: TM4C123GH6PM (Tiva C Series)
  - Simulation: TExaS LaunchPad DLL, Sitronix LCD Emulator

---

## Roles
- Project developed by Víctor Huayapa León and Harif Meza.
- Both collaborated on game logic, hardware configuration, testing and debugging.

---

## How to Run
- Open TheLastHope.uvproj in Keil uVision.
- Ensure the device is set to TM4C123GH6PM.
- Build the project (F7).

Run using:
- TExaS LaunchPadDLL (for GPIO + LED simulation)
- TExaS Sitronix LCD (for display output)

---

## Applications
- Embedded systems education and microcontroller programming practice
- Demonstration of real-time systems using SysTick-based scheduling
- Low-level hardware interaction (GPIO, DAC, LCD drivers)
## License
Academic project – no commercial use.
