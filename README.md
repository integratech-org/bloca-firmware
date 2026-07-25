# Bloca IoT Firmware (`bloca-firmware`)

Part of the **BLOCA** ecosystem — an IoT-monitored plastic-to-brick compactor with machine learning-based grading.

`bloca-firmware` contains the embedded C/C++ firmware sources for microcontrollers (such as ESP32) deployed inside plastic-to-brick compactors. It manages motor controls, sensor readings (load cells, pressure transducers, temperature sensors), and camera monitoring units.

## Features

- **Sensor Telemetry Collection:** Real-time data acquisition from compaction pressure, temperature, and load sensors.
- **Actuator & Compaction Control:** Automated cycle management for plastic shredding, heating, and pressing into construction-ready bricks.
- **Camera Integration:** Visual capture modules for ML-based quality grading.
- **Modular Examples:** Pre-configured PlatformIO projects for sensors (`example_sensors`) and camera streaming (`example_camera`).

## Tech Stack

- **Languages:** C/C++ (embedded), Python (tooling & setup)
- **Build System:** PlatformIO
- **Environment Management:** `uv` & pre-commit hooks

## Project Structure

```text
bloca-firmware/
├── example_camera/    # Camera module integration example (PlatformIO)
├── example_sensors/   # Sensor telemetry acquisition example (PlatformIO)
├── scripts/
│   └── setup.sh       # Firmware environment setup script
├── .clang-format      # Code formatting rules
├── pyproject.toml
└── uv.lock
```

## Related Repositories

- [`bloca-api`](https://github.com/integratech-org/bloca-api) - Backend API receiving telemetry
- [`bloca-ml`](https://github.com/integratech-org/bloca-ml) - Machine learning grading service
