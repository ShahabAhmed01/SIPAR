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

**A console-based missile defense simulation game built in C++**

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=cplusplus)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows)

</div>

---

## 🎮 About

SIPAR is a real-time defense game. Enemy missiles (`X`) and drones (`.`) are heading toward your base — intercept them before they breach your defenses. Friendly units (`<O>`) are also on the field, so watch your fire!

```
X  .  X        <O>          |  [HQ]
     X     .           X    |
                              |
```

---

## 🕹️ Controls

| Key | Action |
|-----|--------|
| **W / S** | Navigate menu |
| **SPACE** | Select / Fire missile |
| **E** | Exit mission |

## 🎯 Targets

| Icon | Type |
|------|------|
| `X` | Enemy Missile |
| `.` | Enemy Drone |
| `<O>` | Friendly Unit |
| `N` | Neutralized |

---

## ⚙️ Build & Run

```
g++ sipar.cpp -o sipar.exe
sipar.exe
```

> ⚠️ Windows only (uses `windows.h`)

---

## 🧠 Structure

- **BST** → Priority targeting (missiles before drones)
- **Queue** → Enemy wave deployment
- **Vector** → Dynamic target tracking
- **Array** → Missile ammo bar

---

<div align="center">

⭐ **Star this repo if you like it!**

</div>