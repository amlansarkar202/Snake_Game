# 🐍 Snake Game in C++ (Console Version)

A simple yet smart **Snake Game implemented in C++**, playable in the console with two modes: **Manual** (keyboard control) and **AI Mode** (auto-solving using BFS pathfinding).

---

## 📌 Features

- ✅ **Manual Control** (WASD keys)
- 🤖 **AI Mode** using **Breadth-First Search (BFS)**
- 🍎 Auto-generating food
- 💥 Game-over detection (self-collision or wall-hit)
- 🔁 **Restart option** in manual mode
- 📈 Score display after game over
- 🧠 Mode toggle (`M` key)
- ❌ Exit anytime (`X` key)
- 🚫 No third-party graphics libraries used – just console and STL

---

## 🛠️ How It Works

### Language & Tools

- **Language:** C++
- **Compiler:** Any C++11-compatible compiler (G++, MSVC, etc.)
- **Platform:** Windows (uses `conio.h` and `windows.h`)
- **Dependencies:** None outside of standard headers

### Algorithms Used

- **BFS (Breadth-First Search):** Used in AI mode to find shortest path from snake head to food
- **Deque:** Used to represent the snake body
- **Random Generation:** Food spawns at random valid positions

---

## 🎮 How to Play

### Controls (Manual Mode)

| Key  | Action          |
|------|------------------|
| W    | Move Up          |
| A    | Move Left        |
| S    | Move Down        |
| D    | Move Right       |
| M    | Toggle AI/Manual |
| X    | Exit Game        |

### Game Loop

1. Game starts in **manual mode**.
2. Press `M` to toggle to AI mode at any time.
3. In **manual mode**, after game over you’ll be asked if you want to play again.
4. In **AI mode**, the game ends automatically upon death.
5. Score is displayed after every game ends.

---

## 🧠 AI Mode Explanation

In AI mode:

- The game uses **Breadth-First Search** (BFS) to find the shortest path to the food.
- If a path exists, the AI moves toward it step by step.
- If no path exists (trapped or enclosed), the game ends.

This implementation avoids overly complex AI logic to ensure readability and educational value.

---

## ✅ Requirements

- Windows OS (due to use of `windows.h` and `conio.h`)
- C++11 or newer compiler
