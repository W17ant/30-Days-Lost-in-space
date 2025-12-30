# 30 Days Lost in Space

**Welcome, Explorer!**
You've crash-landed on an alien planet—your systems are fried, your ship's lights are out, and worst of all... your entertainment system is offline. But worry not. You've got tools, a trusty AI companion named **Astrid**, and exactly **30 days** to fix it all and return to the mothership.

This repository contains code, circuit schematics, and mission details for the **30 Days Lost in Space** course—an immersive adventure in **Arduino coding** and **circuit building** for beginners and aspiring space engineers.

![Ender 3 v2](https://inventr.io/wp-content/uploads/2023/03/30-Days-Lost-in-Space-Open-Box.png)

## Table of Contents

- [What You'll Learn](#what-youll-learn)
- [Kit Contents](#kit-contents)
- [Repository Structure](#repository-structure)
- [Code Examples](#code-examples)
- [Circuit Schematics](#circuit-schematics)
- [Mission Schedule](#mission-schedule)
- [Getting Started](#getting-started)
- [Useful Links](#useful-links)

## What You'll Learn

By completing this course, you'll master:

- **Arduino IDE Setup**: Write and upload code to the HERO board (Arduino Uno-compatible microcontroller)
- **Circuit Basics**: Understand breadboards, resistors, LEDs, and the glorious flow of electrons
- **Programming Concepts**: Learn C++ fundamentals, including variables, conditionals, loops, functions, and debugging
- **Sensor Integration**: Use photoresistors, DIP switches, buzzers, and OLED displays to bring your systems back online
- **Creative Problem Solving**: Apply your skills in mini-projects that simulate real-world spacecraft repairs

## Kit Contents

| Component | Quantity |
|-----------|----------|
| HERO Microcontroller (UNO R3 Compatible) | 1 |
| Breadboard | 1 |
| Rotary Encoder | 1 |
| Photoresistor | 1 |
| LEDs (Various Colors) | 10 |
| RGB LED | 1 |
| Resistors (100k, 10k, 1k, 220 Ohm) | Assorted |
| 128×64 OLED Display | 1 |
| 7-Segment Display | 1 |
| Passive Buzzer | 1 |
| DIP Switch | 1 |
| 16 Button Keypad | 1 |
| USB Cable + Wire Bundles | 1 set |

## Repository Structure

```
30-Days-Lost-in-Space/
├── code/                    # Arduino sketch files (.ino)
│   ├── Day05_EasterEgg.ino
│   ├── Day08_DiscoLight.ino
│   └── Day09_GradientGauge.ino
├── schematics/              # Circuit diagrams (Fritzing exports)
│   ├── Day01_Circuit.png
│   ├── Day02_Circuit.png
│   └── ...
└── README.md
```

## Code Examples

| Day | File | Description |
|-----|------|-------------|
| 5 | [Day05_EasterEgg.ino](code/Day05_EasterEgg.ino) | Multi-zone light control with buzzer jingles and Rick Roll easter egg |
| 8 | [Day08_DiscoLight.ino](code/Day08_DiscoLight.ino) | RGB LED disco party mode with rapid color cycling |
| 9 | [Day09_GradientGauge.ino](code/Day09_GradientGauge.ino) | Battery simulation with photoresistor and gradient LED gauge |

## Circuit Schematics

Fritzing circuit diagrams for each day's mission:

| Day | Schematic | Day | Schematic |
|-----|-----------|-----|-----------|
| 1 | [Day01_Circuit.png](schematics/Day01_Circuit.png) | 16 | [Day16_Circuit.png](schematics/Day16_Circuit.png) |
| 2 | [Day02_Circuit.png](schematics/Day02_Circuit.png) | 17 | [Day17_Circuit.png](schematics/Day17_Circuit.png) |
| 3 | [Day03_Circuit.png](schematics/Day03_Circuit.png) | 18 | [Day18_Circuit.png](schematics/Day18_Circuit.png) |
| 4 | [Day04_Circuit.png](schematics/Day04_Circuit.png) | 19 | [Day19_Circuit.png](schematics/Day19_Circuit.png) |
| 6 | [Day06_Circuit.png](schematics/Day06_Circuit.png) | 21 | [Day21_Circuit.png](schematics/Day21_Circuit.png) |
| 7 | [Day07_Circuit.png](schematics/Day07_Circuit.png) | 22 | [Day22_Circuit.png](schematics/Day22_Circuit.png) |
| 8 | [Day08_Circuit.png](schematics/Day08_Circuit.png) | 23 | [Day23_Circuit.png](schematics/Day23_Circuit.png) |
| 9 | [Day09_Circuit.png](schematics/Day09_Circuit.png) | 24 | [Day24_Circuit.png](schematics/Day24_Circuit.png) |
| 11 | [Day11_Circuit.png](schematics/Day11_Circuit.png) | 26 | [Day26_Circuit.png](schematics/Day26_Circuit.png) |
| 12 | [Day12_Circuit.png](schematics/Day12_Circuit.png) | 27 | [Day27_Circuit.png](schematics/Day27_Circuit.png) |
| 13 | [Day13_Circuit.png](schematics/Day13_Circuit.png) | 28 | [Day28_Circuit.png](schematics/Day28_Circuit.png) |
| 14 | [Day14_Circuit.png](schematics/Day14_Circuit.png) | 29 | [Day29_Circuit.png](schematics/Day29_Circuit.png) |

## Mission Schedule

| Day | Mission Objective |
|-----|-------------------|
| 1 | Power Up: Blink an LED and connect the HERO board |
| 2 | Cabin Lights: Wire up your first circuit |
| 3 | Switch It: Control LEDs with DIP switches |
| 4 | Light Show: Add multiple LEDs and advanced control |
| 5 | Easter Egg: Multi-zone lights with buzzer jingles |
| 6-7 | Solar Panels: Photoresistor integration |
| 8 | RGB LED: Color mixing and disco mode |
| 9 | Battery Gauge: Gradient LED indicator |
| 10+ | Advanced missions: OLED, keypad, security systems |

## Getting Started

1. **Download Arduino IDE**: [arduino.cc/en/software](https://www.arduino.cc/en/software)
2. **Download Fritzing** (optional): [fritzing.org/download](https://fritzing.org/download)
3. **Access Course Material**: [inventr.io](https://inventr.io/collections/30-days-lost-in-space)
4. **Clone this repo**: `git clone https://github.com/W17ant/30-Days-Lost-in-space.git`
5. **Open sketches**: Open `.ino` files in Arduino IDE
6. **Upload to HERO board**: Connect via USB and upload

## Useful Links

- [Arduino IDE Download](https://www.arduino.cc/en/software)
- [Fritzing Download](https://fritzing.org/download)
- [Inventr.io Course](https://inventr.io/collections/30-days-lost-in-space)
- [Arduino Language Reference](https://www.arduino.cc/reference/en/)
