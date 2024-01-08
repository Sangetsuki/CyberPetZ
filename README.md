# CyberPetZ

A simple Tamagotchi clone created with C++ for practicing.

## Install

These build instructions are intended for Linux users, specifically Arch Linux. For different distributions, find the appropriate packages for your package manager.

**Dependencies:**
- C++ compiler
- CMake
- [Raylib library](https://www.raylib.com/)

**Installation Steps:**

1. Install necessary dependencies:
   - For Arch Linux:
     ```
     sudo pacman -S base-devel cmake raylib
     ```
   - For Debian/Ubuntu-based systems:
     ```
     sudo apt-get install build-essential cmake libraylib-dev
     ```

Feel free to add or modify the distribution-specific installation commands as needed.

2. Clone the repository: `git clone https://github.com/Sangetsuki/CyberPetZ.git`

3. Navigate to the project directory: `cd CyberPetZ`

4. Compile the code: 
  ```bash
  ./build.sh
  ```
  Run the executable: `build/CyberPetZ`

**build.sh**
[build.sh](./build.sh) contains some flags for different targets and objectives:
- `-x` Removes the `build` directory
- `-c` Generates `compile_commands.json` for Lsp (in my setup I use clangd)
- `-d` Generates a executable with debugging symbols
