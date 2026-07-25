# Setup Guide — Bloca IoT Firmware (`bloca-firmware`)

Follow these instructions to set up the development environment, build, and flash firmware for Bloca hardware modules.

## Prerequisites

- **Python**: Version 3.14 or higher
- **Package Manager**: `uv`
- **PlatformIO CLI** or VS Code with the **PlatformIO IDE** extension installed.
- **Make**: (optional) For running Makefile shortcuts

## Environment Setup & Pre-commit

1. Navigate to the firmware directory:
   ```bash
   cd bloca-firmware
   ```

2. Run the automated setup script to configure dependencies, virtual environments, and pre-commit hooks:
   ```bash
   make setup
   # or run the script directly:
   ./scripts/setup.sh
   ```

3. **Pre-commit Hooks Management (via Makefile):**
   - Install pre-commit hooks manually:
     ```bash
     make pre-commit-install
     ```
   - Run pre-commit checks on all files:
     ```bash
     make pre-commit-all
     ```
   - Update pre-commit hooks to their latest versions:
     ```bash
     make pre-commit-update
     ```

## Building and Flashing

### Example: Sensor Module (`example_sensors`)

1. Navigate to the target module directory:
   ```bash
   cd example_sensors
   ```

2. Build the firmware:
   ```bash
   platformio run
   ```

3. Flash the firmware to your connected microcontroller:
   ```bash
   platformio run --target upload
   ```

4. Monitor serial output:
   ```bash
   platformio device monitor
   ```

### Example: Camera Module (`example_camera`)

Repeat the same steps inside the `example_camera` directory:
```bash
cd ../example_camera
platformio run --target upload
```
