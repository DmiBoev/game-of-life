# Game of Life (C Implementation) 🦠

A professional implementation of John Conway's **Game of Life**, written in C. This project demonstrates low-level system programming, memory management, and terminal-based UI rendering.

---

### 🕹 Features
*   **Terminal Interface:** High-performance rendering using the `ncurses` library.
*   **Custom Speed:** Real-time simulation speed adjustment.
*   **Pattern Loading:** Support for initializing the board from external text files (located in `zagotovki/`).
*   **Clean Architecture:** Modular code structure with a robust `Makefile` for automation.

---

### 🛠 Tech Stack
*   **Language:** C (C11)
*   **Library:** `ncurses`
*   **Build Tool:** GNU Make

---

### 🚀 Getting Started

#### Prerequisites
Ensure the `ncurses` library is installed:
```bash
# For Debian/Ubuntu
sudo apt-get install libncurses5-dev libncursesw5-dev
```

#### Installation & Build
1. Clone the repository:
   ```bash
   git clone https://github.com
   cd game-of-life
   ```
2. Build the project:
   ```bash
   make
   ```

---

### 🎮 Usage
The project includes a flexible `Makefile` to run different initial patterns easily:

*   **Run Gasper:** `make run_gasper`
*   **Run HWSS:** `make run_HWSS`
*   **Run LongShip:** `make run_LongShip`
*   **Run Spaceship:** `make run_spaseShip`

---

### 📁 Project Structure
*   `playlive.c` / `playlive.h` — Core engine and UI logic.
*   `pattern/` — Pre-defined patterns and initial states.
*   `Makefile` — Automated build system with universal targets.

---
*Developed by [Dmitry Boev](https://github.com)*
