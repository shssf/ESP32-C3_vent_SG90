# Vent Servo Controller (XIAO ESP32C3 + SG90)

Firmware project for a ventilation damper controller based on the Seeed XIAO ESP32C3. The board drives an SG90 servo, reports state with two LEDs, exposes a local Web UI, supports OTA updates, and provides first-time Wi-Fi setup through SoftAP provisioning.

## Circuit

![Circuit diagram](data/circuit_image.png)

## Hardware

- Seeed **XIAO ESP32C3**
- **SG90** servo on GPIO4/D2, powered from 5 V
- **Pushbutton** on GPIO3/D1 to GND, configured as `INPUT_PULLUP`
- **Green LED** on GPIO5/D3 through a **1 kOhm** resistor
- **Red LED** on GPIO6/D4 through a **1 kOhm** resistor
- **HLK-5M05** 5 V / 1 A AC-DC module
- Recommended servo power decoupling: **1000 uF + 0.1 uF** placed close to the SG90

## Pin Map

| GPIO | Pin | Function | Notes |
|------|-----|----------|-------|
| 3 | D1 | Pushbutton | Active-low, internal pull-up |
| 4 | D2 | SG90 PWM | 100 Ohm series resistor in the signal line |
| 5 | D3 | Green LED | OPEN indication |
| 6 | D4 | Red LED | CLOSED indication |

## Servo Logic

The firmware uses three preset damper positions:

- `CLOSED` -> `0`
- `MIDDLE` -> `6`
- `OPEN` -> `12`

The physical button toggles only between `CLOSED` and `OPEN`.

## Firmware Features

- Web UI on port `80`
- Main page at `/` with device diagnostics
- Dedicated damper control page at `/control`
- JSON status endpoint at `/status`
- Preset servo control via HTTP POST routes
- OTA update flow via `/ota` and `/update`
- mDNS access through `<hostname>.local`
- First-time Wi-Fi setup through SoftAP provisioning
- Automatic web server startup after the station interface gets an IP address

## Wi-Fi Provisioning

If the device has not been provisioned yet, it starts a SoftAP for Wi-Fi setup:

- SSID: `vent_1_setup`
- Password / PoP: `12345678`

After Wi-Fi credentials are saved, they are stored in NVS. On the next boot the device starts the STA interface, obtains an IP address, and then launches mDNS and the HTTP server.

Default hostname:

- `vent_1`

## Web API

| Method | Path | Description |
|--------|------|-------------|
| GET | `/` | Main page with hardware diagnostics |
| GET | `/control` | Control page with servo action buttons |
| GET | `/status` | JSON: `{"servo_angle":<int>,"vent_open":<bool>}` |
| POST | `/servo/close` | Move servo to closed position |
| POST | `/servo/middle` | Move servo to middle position |
| POST | `/servo/open` | Move servo to open position |
| GET | `/hw_details` | Extended hardware diagnostics JSON |
| GET | `/ota` | OTA upload page |
| POST | `/update` | Upload firmware image to inactive OTA partition |

Examples:

```bash
curl http://vent_1.local/status
curl -X POST http://vent_1.local/servo/open
curl -X POST http://vent_1.local/servo/close
```

## Build and Flash

```bash
pio run
pio run -t upload
pio device monitor
```

Build settings are defined in `platformio.ini`:

- framework: `espidf`
- board: `seeed_xiao_esp32c3`
- partition table: `partitions_4mb_ota.csv`
- embedded web assets: `data/main_page.html`, `data/control_page.html`, `data/ota_page.html`, `data/style.css`

## Flash Layout

| Partition | Offset | Size |
|-----------|--------|------|
| nvs | `0x9000` | 20 KB |
| otadata | `0xE000` | 8 KB |
| ota_0 | `0x10000` | 1984 KB |
| ota_1 | `0x200000` | 1984 KB |
