# Vent Servo Controller (XIAO ESP32C3 + SG90)

**Ultra‑short:** ESP32‑C3 (Seeed XIAO) drives an SG90 damper servo. One pushbutton toggles OPEN/CLOSED. Two LEDs show state. Powered from HLK‑5M05 (5 V).

> ⚠️ HLK‑5M05 is a mains module (100–240 VAC). Use an isolated enclosure, fuse/TVS/MOV as required, and follow electrical safety practices.

## Hardware
- Seeed **XIAO ESP32C3**
- **SG90** servo (PWM, 5 V) + decoupling **1000 µF + 0.1 µF** near the servo
- **Pushbutton** (tactile, 4‑pin; used as D1 → GND, `INPUT_PULLUP`)
- **LED OPEN** (green) + **LED CLOSED** (red), each with **1 kΩ** series resistor
- **HLK‑5M05** 5 V/1 A AC‑DC module

## Wiring (at a glance)
