
<div align="center">

```
███████╗██╗██████╗  █████╗ ██████╗ 
██╔════╝██║██╔══██╗██╔══██╗██╔══██╗
███████╗██║██████╔╝███████║██████╔╝
╚════██║██║██╔═══╝ ██╔══██║██╔══██╗
███████║██║██║     ██║  ██║██║  ██║
╚══════╝╚═╝╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝
```

# 🛡️ SIPAR — Defense Command System

**Semi-Intelligent Protection and Response**

*A real-time console-based missile defense simulation built in C++*

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey?style=for-the-badge&logo=windows)
![Semester](https://img.shields.io/badge/Semester-3rd-green?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge)

</div>

---

## 🎮 What is SIPAR?

SIPAR is a **console-based defense simulation game** where you command a missile defense system to protect your base from incoming threats. Enemy missiles and drones are closing in — it's your job to intercept them before they breach your defenses!

```
╔══════════════════════════════════════════════════════╗
║   SIPAR RADAR ENGINE | PULSE: 42                     ║
╠══════════════════════════════════════════════════════╣
║                                                      ║
║   X . . X        <O>          |  [HQ]                ║
║      X     .           X      |                      ║
║                               |                      ║
╠══════════════════════════════════════════════════════╣
║  X=Missile  .=Drone  <O>=Friendly  N=Neutralized     ║
╚══════════════════════════════════════════════════════╝
```

---

## ✨ Features

| Feature | Description |
|--------|-------------|
| 🎯 **Smart Targeting** | Auto-locks onto the highest-priority threat using a BST |
| 🚀 **Missile System** | 15 missiles with a live ammo bar display |
| 🛸 **Enemy Waves** | Missiles (`X`) and Drones (`.`) deployed in waves via a queue |
| 🤝 **Friendly Units** | `<O>` units roam the field — don't shoot them! |
| 💥 **Boom Animation** | Satisfying explosion animation on target destruction |
| 📋 **Mission Log** | Real-time neutralization history displayed on screen |
| 🏆 **End Screen** | Full mission summary with success/failure result |

---

## 🕹️ Controls

```
┌─────────────────────────────────────────┐
│           KEYBOARD CONTROLS             │
├──────────────┬──────────────────────────┤
│  W / S       │  Navigate menu           │
│  SPACE       │  Select / Fire missile   │
│  E           │  Exit mission            │
└──────────────┴──────────────────────────┘
```

---

## 🎯 Targets Guide

| Symbol | Type | Priority |
|--------|------|----------|
| `X` | 🔴 Enemy Missile | **HIGH** — Intercept first! |
| `.` | 🟡 Enemy Drone | **MEDIUM** — Intercept second |
| `<O>` | 🟢 Friendly Unit | **DO NOT SHOOT** |
| `\|` | 🔵 Defense Line | Protect this at all costs |
| `N` | ⚫ Neutralized | Already destroyed |

---

## 🔧 How to Compile & Run

> **Requirements:** Windows OS, C++ compiler (MinGW / MSVC)

**Using g++ (MinGW):**
```bash
g++ sipar.cpp -o sipar.exe
sipar.exe
```

**Using MSVC (Developer Command Prompt):**
```bash
cl sipar.cpp
sipar.exe
```

> ⚠️ This game uses Windows-specific APIs (`windows.h`) and **only runs on Windows**.

---

## 🧠 Technical Implementation

SIPAR was built as a **Data Structures project** showcasing real-world applications of:

```
📦 Data Structures Used:
├── 🌳 BST (Binary Search Tree)  → Priority-based threat management
├── 📋 Queue                     → Wave-based enemy deployment
├── 📊 Vector                    → Dynamic target tracking
└── 🔢 Array                     → Missile ammo bar
```

- **BST** organizes threats by risk score — missiles always get intercepted before drones
- **Queue** manages the wave system, deploying enemies gradually
- **Vectors** store all active targets for smooth rendering
- **Risk Score** = `(isHostile ? 55 : 0) + (120 / distance)`

---

## 📸 Screenshots

```
┌─────────────────────────────────────────────────────────────────────────────┐
│  MAIN MENU                          │  GAMEPLAY                             │
│  ─────────────────────────────────  │  ─────────────────────────────────    │
│  +===================================+  │  SIPAR RADAR ENGINE | PULSE: 12   │
│  |  SIPAR DEFENSE COMMAND SYSTEM   |  │  X . . X        <O>    |  [HQ]     │
│  +===================================+  │  Missiles: 13 [|||||||||||||   ]  │
│                                     │  LOG: Neutralized: 301 | 303 |        │
│  >>> START MISSION <<<              │  >> STATUS: Scanning...               │
│      INSTRUCTIONS                   │                                       │
│      EXIT SYSTEM                    │                                       │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

## 👨‍💻 Team

| Name | Roll Number |
|------|-------------|
| **Muneeb Ur Rehman** | F2024376357 |
| **Hassan Ikram** | F2024376395 |

> 📚 Submitted to: **Muhammad Rizwan**
> 🎓 3rd Semester — Data Structures Project

---

## 🤖 Tools Used

- **DeepSeek** & **Claude AI** — Assisted with console visuals and color rendering
- **C++ STL** — Vectors, Queues, and standard utilities

---

<div align="center">

*Made with ❤️ and a lot of debugging*

**⭐ Star this repo if you liked it!**

</div>
