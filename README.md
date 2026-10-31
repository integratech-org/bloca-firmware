<a id="readme-top"></a>

<!-- PROJECT SHIELDS -->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/integratech-org/bloca-firmware">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">BLOCA Firmware</h3>

  <p align="center">
    ESP32 Firmware for BLOCA Sensor & Actuator Node
    <br />
    Real-time Telemetry Collection • Actuator Control • MQTT Communication
    <br />
    <a href="https://github.com/integratech-org/bloca-firmware"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/integratech-org/bloca-firmware/issues/new?labels=bug&template=bug-report---.md">Report Bug</a>
    &middot;
    <a href="https://github.com/integratech-org/bloca-firmware/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#features">Features</a></li>
    <li><a href="#related-projects">Related Projects</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![BLOCA Firmware Banner][product-banner]](https://github.com/integratech-org/bloca-firmware)

**BLOCA Firmware** is the embedded software running on the ESP32 microcontroller that serves as the sensor and actuator node for the BLOCA machine. Written in MicroPython, it reads data from temperature sensors, pressure transducers, and current monitors during each compaction cycle, and controls heating elements, hydraulic actuators, and pneumatic solenoids through GPIO pins and relays.

The firmware publishes telemetry to a local MQTT broker (running on the Raspberry Pi via BLOCA Edge) and subscribes to control topics for receiving remote commands. It implements batch lifecycle state management, ensuring orderly transitions from material dosing to heating, compression, cooling, and block ejection. Safety interlocks prevent hazardous operations, and watchdog timers ensure reliable recovery from faults.

Example scripts for camera integration and sensor calibration are included in the `example_camera/` and `example_sensors/` directories.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

* [![MicroPython][MicroPython.org]][MicroPython-url]
* [![ESP32][ESP32.com]][ESP32-url]
* [![MQTT][MQTT.org]][MQTT-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

This firmware is designed to run on ESP32-based development boards. You'll need hardware tools to flash the firmware and test it with connected sensors and actuators.

### Prerequisites

* **Hardware:**
  - ESP32 development board (ESP32-WROOM-32, ESP32-DevKitC, or similar)
  - USB cable for flashing and serial communication
  - Sensors: Temperature sensors (DS18B20 or similar), pressure transducers, current monitors
  - Actuators: Relays for heating elements, solenoids, and hydraulic pumps
  - Power supply appropriate for your actuators

* **Software:**
  - Python 3.14 or higher
  - [uv](https://docs.astral.sh/uv/) package manager
  - esptool for flashing MicroPython firmware
  - ampy or rshell for file transfer to ESP32
  - Serial terminal (screen, minicom, or PuTTY)

### Installation

1. Clone the repository
   ```sh
   git clone https://github.com/integratech-org/bloca-firmware.git
   cd bloca-firmware
   ```

2. Install dependencies (includes esptool and ampy)
   ```sh
   make setup
   ```

3. Download MicroPython firmware for ESP32
   ```sh
   # Visit https://micropython.org/download/ESP32_GENERIC/
   # Download the latest stable .bin file
   ```

4. Flash MicroPython to your ESP32
   ```sh
   # Replace /dev/ttyUSB0 with your ESP32's serial port
   esptool.py --chip esp32 --port /dev/ttyUSB0 erase_flash
   esptool.py --chip esp32 --port /dev/ttyUSB0 write_flash -z 0x1000 esp32-*.bin
   ```

5. Create firmware configuration
   ```sh
   cp config.py.example config.py
   # Edit config.py with your specific settings:
   # - WiFi SSID and password
   # - MQTT broker address (usually the Raspberry Pi IP)
   # - GPIO pin assignments for sensors and actuators
   # - Safety thresholds (max temperature, max pressure, etc.)
   ```

6. Upload firmware files to ESP32
   ```sh
   # Using ampy (replace /dev/ttyUSB0 with your port)
   ampy --port /dev/ttyUSB0 put boot.py
   ampy --port /dev/ttyUSB0 put main.py
   ampy --port /dev/ttyUSB0 put config.py
   ampy --port /dev/ttyUSB0 put src/
   ```

7. Install pre-commit hooks (for development)
   ```sh
   make pre-commit-install
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

### Connect to ESP32 Serial Console

Monitor the firmware's serial output:

```sh
# Using screen
screen /dev/ttyUSB0 115200

# Using minicom
minicom -D /dev/ttyUSB0 -b 115200
```

The firmware will:
1. **Initialize WiFi** and connect to the configured network
2. **Connect to MQTT broker** (BLOCA Edge's Mosquitto instance)
3. **Calibrate sensors** and perform self-checks
4. **Enter idle state** and wait for batch start command
5. **Publish telemetry** at configured intervals during active batches
6. **Execute batch phases** (dosing, heating, compression, cooling, ejection) based on state machine logic
7. **Listen for remote commands** on MQTT control topics (start, stop, emergency_stop, reset)

### MQTT Topics

The firmware uses the following MQTT topic structure:

**Published Topics** (telemetry):
```
bloca/telemetry/temperature
bloca/telemetry/pressure
bloca/telemetry/current
bloca/telemetry/batch_state
```

**Subscribed Topics** (control):
```
bloca/control/start_batch
bloca/control/stop_batch
bloca/control/emergency_stop
bloca/control/reset
```

### Example Scripts

Test camera integration:
```sh
cd example_camera
python test_camera.py
```

Calibrate sensors:
```sh
cd example_sensors
python calibrate_sensors.py
```

### Development

Update firmware on ESP32 after code changes:
```sh
make upload
```

Run pre-commit checks:
```sh
make pre-commit-all
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- FEATURES -->
## Features

### Sensor Data Collection
- **Temperature Monitoring**: DS18B20 or similar digital temperature sensors for heating element and block temperature
- **Pressure Measurement**: Analog pressure transducers for hydraulic compaction pressure
- **Current Monitoring**: ACS712 or similar current sensors for power consumption tracking
- **Compressed Height**: Ultrasonic or laser distance sensors for measuring block height during compression

### Actuator Control
- **Heating Element Control**: PWM or relay-based control of heating elements with temperature feedback
- **Hydraulic Pump**: On/off control for compression actuator
- **Pneumatic Solenoids**: Block ejection and material dosing control
- **Emergency Stop**: Hardware-level safety cutoff for all actuators

### Communication & Networking
- **WiFi Connectivity**: IEEE 802.11 b/g/n connection to local network
- **MQTT Client**: Publish/subscribe messaging with automatic reconnection
- **JSON Telemetry**: Structured data format for easy parsing by BLOCA Edge
- **QoS Support**: Configurable Quality of Service levels for critical messages

### State Machine & Safety
- **Batch Lifecycle Management**: State machine implementation for orderly phase transitions
- **Safety Interlocks**: Prevent hazardous operations (e.g., compression before heating, ejection during compression)
- **Watchdog Timer**: Automatic reset on firmware hangs or crashes
- **Temperature Limits**: Automatic heater cutoff if temperature exceeds safe threshold
- **Pressure Limits**: Emergency stop if pressure exceeds maximum safe value

### Configuration & Diagnostics
- **Runtime Configuration**: Update settings via MQTT without re-flashing firmware
- **Diagnostic Mode**: Verbose logging and sensor test routines for troubleshooting
- **Calibration Routines**: Built-in sensor calibration with offset and scale factor storage
- **Firmware Version Reporting**: Publish firmware version on startup for inventory management

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- RELATED PROJECTS -->
## Related Projects

BLOCA Firmware is part of the **BLOCA (Batch-Level Optimization through Compaction Analytics)** ecosystem:

* **[bloca-edge](https://github.com/integratech-org/bloca-edge)** - Raspberry Pi edge hub that receives telemetry from this firmware via MQTT
* **[bloca-api](https://github.com/integratech-org/bloca-api)** - Cloud REST API backend for storing batch data collected by this firmware
* **[bloca-ml](https://github.com/integratech-org/bloca-ml)** - Machine learning service that uses telemetry data for compressive strength prediction
* **[bloca-mobile](https://github.com/integratech-org/bloca-mobile)** - Mobile application for operators to start batches and monitor firmware-collected data
* **[bloca-admin](https://github.com/integratech-org/bloca-admin)** - Web admin dashboard displaying historical data from this firmware
* **[IntegraTech Organization](https://github.com/integratech-org)** - View all BLOCA projects and documentation

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

IntegraTech - [Facebook](https://www.facebook.com/profile.php?id=61592806334500) - integratech1@outlook.com

Project Link: [https://github.com/integratech-org/bloca-firmware](https://github.com/integratech-org/bloca-firmware)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
[contributors-shield]: https://img.shields.io/github/contributors/integratech-org/bloca-firmware.svg?style=for-the-badge
[contributors-url]: https://github.com/integratech-org/bloca-firmware/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/integratech-org/bloca-firmware.svg?style=for-the-badge
[forks-url]: https://github.com/integratech-org/bloca-firmware/network/members
[stars-shield]: https://img.shields.io/github/stars/integratech-org/bloca-firmware.svg?style=for-the-badge
[stars-url]: https://github.com/integratech-org/bloca-firmware/stargazers
[issues-shield]: https://img.shields.io/github/issues/integratech-org/bloca-firmware.svg?style=for-the-badge
[issues-url]: https://github.com/integratech-org/bloca-firmware/issues
[product-banner]: images/banner.png

<!-- Technology Badges -->
[MicroPython.org]: https://img.shields.io/badge/MicroPython-2B2728?style=for-the-badge&logo=micropython&logoColor=white
[MicroPython-url]: https://micropython.org/
[ESP32.com]: https://img.shields.io/badge/ESP32-000000?style=for-the-badge&logo=espressif&logoColor=white
[ESP32-url]: https://www.espressif.com/en/products/socs/esp32
[MQTT.org]: https://img.shields.io/badge/MQTT-660066?style=for-the-badge&logo=mqtt&logoColor=white
[MQTT-url]: https://mqtt.org/
