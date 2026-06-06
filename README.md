# Hans' Paradox (Hansov paradox)

Hans' Paradox is a 2D platformer game featuring a built-in custom level editor. This project was developed in C++ using the SFML library as the practical component of my high school graduation exam (Technické lýceum, school year 2025/2026).

This repository contains the complete source code, fully configured and ready to build using CMake.

---

## 🎮 Game Features & Functionality

The project consists of two core modules that seamlessly integrate with each other:

### 1. The Game
- **Movement & Physics:** Classic platformer physics with gravity, handling walking (A/D) and jumping (W/Space).
- **AI Enemies:** State-machine driven enemy behavior including Idle, Patrol, Chase, and Attack states, complete with player collision detection.
- **Core Mechanics:** Fully functional checkpoints and an in-game pause menu (ESC).

### 2. Level Editor
- **Real-time Editing:** Place and modify platforms, player spawn points, and enemy spawns directly within the engine.
- **Visuals:** Support for multi-layered parallax backgrounds.
- **Data Persistence:** Save and load custom levels to/from files without modifying the source code.

*You can hot-swap between the game and the editor at any time by pressing **F5**.*

---

## 🛠️ Development & Compilation Guide

This project is built upon a plug-and-play SFML CMake template. You do not need to pre-install SFML on your operating system; the `thirdparty` folder contains the source code of necessary libraries for this project.

### Prerequisites
- **IDE/Environment:** Visual Studio (with CMake support enabled) or any C++ IDE that supports CMake and C++17/20.

### Setup Instructions (Visual Studio):
1. Clone this repository.
2. Open the project root folder in Visual Studio (`File -> Open -> Folder`).
3. Visual Studio will automatically generate the CMake cache. If it doesn't, simply save (`Ctrl + S`) the `CMakeLists.txt` file.
4. Select `mygame.exe` from the target dropdown menu in the top toolbar.
5. Press `Ctrl + F5` to compile and run the project (running without the debugger is significantly faster).

### Managing Source Files
- Add new `.cpp` files into the `src/` directory and `.h` files into the `include/` directory.
- The CMake script automatically tracks files via wildcards. If you add a new file, just save the `CMakeLists.txt` file to refresh the solution. If Visual Studio asks to manage files for you, always choose **NO**.

---

## 📦 Production & Distribution

To compile a shippable standalone build for regular players (which hides the console window and forces relative asset paths using the `RESOURCES_PATH` macro):

1. Open `CMakeLists.txt` and flip the production flag:
```cmake
set(PRODUCTION_BUILD ON)
```
2. It is highly recommended to delete the out/ (or build/) folder to force a clean build.
3. Build the project again. The resulting executable can be distributed along with your asset folders.

## ⚠️ Known Limitations & Debug Status

- Some ImGui debug windows remain active within the build for testing purposes.
- The file dialog library used for loading levels might display instability when dealing with specific folder structures.
- The player combat system (attacking) is not yet implemented; the project currently ships with 1 demo level.
