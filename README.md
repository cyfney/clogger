# Clogger

[![Arduino AVR Build](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml/badge.svg)](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml) [![Arduino ESP32 Build](https://github.com/cyfney/clogger/actions/workflows/arduino_esp32_build.yml/badge.svg)](https://github.com/cyfney/clogger/actions/workflows/arduino_esp32_build.yml)

[中文版](README.zh-CN.md)

## Introduction

`clogger` is a lightweight logging library designed for Arduino and ESP32 platforms. It provides structured log output with timestamps, file names, line numbers, and function names, making debugging easier.

## Features

- **Structured Output**: Each log includes timestamp, severity, file, line, and function information

- **Compile-time Filtering**: Disabled log levels are completely removed at compile time

- **Millisecond Timestamps**: Precise timing information

- **Cross-platform**: Works on Arduino AVR and ESP32 platforms

- **printf-like Formatting**: Familiar printf-style formatting for log messages

## Installation

1. Download the library as a ZIP file from the GitHub repository

2. In Arduino IDE, go to Sketch → Include Library → Add .ZIP Library...

3. Select the downloaded ZIP file

4. The library will be installed and ready to use

## Quick Start

Here's the simplest way to use Clogger:

```c++
#include "clogger.h"

void setup() {
  Serial.begin(115200);
  CLOGI("System starting up");
}

void loop() {
  static int s_value = 0;
  CLOGI("Current value: %d", s_value++);
  delay(1000);
}
```

**Output example**:

```log
00:00:00.001 I sketch.ino:5 setup] System starting up
00:00:00.002 I sketch.ino:10 loop] Current value: 0
00:00:01.003 I sketch.ino:10 loop] Current value: 1
```

The log format is: `HH:MM:SS.mmm Severity File:Line Function] Message`

- **HH:MM:SS.mmm**: Timestamp with millisecond precision
- **Severity**: Single character (I=INFO, D=DEBUG, etc.)
- **File:Line**: Source file and line number
- **Function**: Function name where the log was called
- **Message**: Your formatted log message

## Basic Usage

### Simple Logging

Clogger works like the standard printf function:

```c++
#include "clogger.h"

void setup() {
  Serial.begin(115200);
  
  int sensorValue = 512;
  float temperature = 25.5f;
  const char* name = "Sensor1";
  
  CLOGI("Reading from %s", name);
  CLOGI("Raw value: %d, Temperature: %.1f°C", sensorValue, temperature);
  
  if (sensorValue > 1000) {
    CLOGW("High sensor reading: %d", sensorValue);
  }
}
```

### Multiple Logging Macros

Clogger provides different macros for different purposes:

```c++
void ProcessData() {
  CLOGV("Entering data processing");  // Verbose - for detailed tracing
  CLOGD("Processing chunk %d of %d", current, total);  // Debug - for development
  CLOGI("Data processed successfully");  // Info - normal operation messages
  CLOGW("Memory usage high: %d%%", usage);  // Warning - potential issues
  CLOGE("Failed to write to SD card");  // Error - something went wrong
}
```

## Log Severity Levels

Clogger has 5 severity levels. By default, only INFO, WARN, and ERROR levels are enabled.

| level | Macro | Description | Default |
| :--- | :--- | :--- | :--- |
| VERBOSE | CLOGV() | Most detailed tracing information | Disabled |
| DEBUG | CLOGD() | Diagnostic information for debugging | Disabled |
| INFO | CLOGI() | General operational information| Enabled |
| WARN | CLOGW() | Potentially harmful situations | Enabled |
| ERROR | CLOGE() | Error events | Enabled |

Example of all levels:

```c++
CLOGV("Low-level variable tracing: x=%d, y=%d", x, y);  // VERBOSE
CLOGD("Debug info: buffer size = %d bytes", size);      // DEBUG
CLOGI("System initialized, free RAM: %d bytes", free);  // INFO
CLOGW("Warning: Connection unstable");                  // WARN
CLOGE("Error: File not found: %s", filename);           // ERROR
```

### Configuration

#### Filtering Logs

You can control which log levels are included in your compiled code by defining `CLOGGER_SEVERITY` before including the header:

```c++
// Enable DEBUG and higher levels (DEBUG, INFO, WARN, ERROR)
#define CLOGGER_SEVERITY CLOGGER_SEVERITY_DEBUG
#include "clogger.h"
```

#### Available severity settings

| Setting | Enabled Logs |
| :--- | :--- |
| `CLOGGER_SEVERITY_VERBOSE` | All logs (VERBOSE, DEBUG, INFO, WARN, ERROR) |
| `CLOGGER_SEVERITY_DEBUG` | EBUG, INFO, WARN, ERROR |
| `CLOGGER_SEVERITY_INFO` | INFO, WARN, ERROR (default) |
| `CLOGGER_SEVERITY_WARN` | WARN, ERROR |
| `CLOGGER_SEVERITY_ERROR` | ERROR only |
| `CLOGGER_SEVERITY_NONE` | No logs |

**Examples**:

```c++
// For production - only show errors
#define CLOGGER_SEVERITY CLOGGER_SEVERITY_ERROR
#include "clogger.h"

// For development - show debug and above
#define CLOGGER_SEVERITY CLOGGER_SEVERITY_DEBUG
#include "clogger.h"

// For deep debugging - show everything
#define CLOGGER_SEVERITY CLOGGER_SEVERITY_VERBOSE
#include "clogger.h"
```

> Note: The **CLOGGER_SEVERITY** macro must be defined before including `clogger.h`. Logs below the set threshold are completely removed at compile time, resulting in zero runtime overhead.

**Complete Examples**:

```c++
// Enable all log levels for debugging
#define CLOGGER_SEVERITY CLOGGER_SEVERITY_VERBOSE
#include "clogger.h"

const int LED_PIN = 13;
int counter = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  CLOGV("Entering setup()");
  CLOGD("Configured LED pin: %d", LED_PIN);
  CLOGI("System initialized");
}

void loop() {
  CLOGV("Loop iteration %d", counter);
  
  digitalWrite(LED_PIN, HIGH);
  CLOGD("LED ON");
  delay(500);
  
  digitalWrite(LED_PIN, LOW);
  CLOGD("LED OFF");
  delay(500);
  
  counter++;
  
  if (counter % 10 == 0) {
    CLOGI("Completed %d cycles", counter);
  }
  
  if (counter > 100) {
    CLOGW("High cycle count: %d", counter);
  }
}
```

**Expected output**:

```log
00:00:00.000 V example.ino:8 setup] Entering setup()
00:00:00.001 D example.ino:9 setup] Configured LED pin: 13
00:00:00.002 I example.ino:10 setup] System initialized
00:00:00.003 V example.ino:13 loop] Loop iteration 0
00:00:00.004 D example.ino:16 loop] LED ON
00:00:00.505 D example.ino:19 loop] LED OFF
00:00:01.006 V example.ino:13 loop] Loop iteration 1
00:00:01.007 D example.ino:16 loop] LED ON
00:00:01.508 D example.ino:19 loop] LED OFF
00:00:05.020 I example.ino:25 loop] Completed 10 cycles
00:00:50.100 W example.ino:29 loop] High cycle count: 101
```

## License

MIT License. See [LICENSE](LICENSE)
