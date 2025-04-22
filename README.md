# CLOG

[![Arduino AVR Build](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml/badge.svg)](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml) [![Arduino AVR Build](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml/badge.svg)](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml)

[中文版](README.zh-CN.md)

## Introduction

The `clogger` module is a lightweight logging utility designed for Arduino projects, supporting both AVR and ESP32 architectures. It provides a `printf`-like interface with severity-based filtering, timestamps, and metadata (file, line, function).

## Features

* **Severity Levels**​​: Verbose, Debug, Info, Warn, Error, Fatal.

​* **​Low Overhead**​​: Compile-time filtering of disabled log levels.

​* **Timestamp Precision**​​: Millisecond-resolution timestamps.

​* **Cross-Platform**​​: Works on AVR (Arduino) and ESP32.

## Installation

To use the `clogger` module in your Arduino project, follow these steps:

1. Download the Library:

    Download the clogger library as a ZIP file from the release page or the source repository.

2. Open Arduino IDE:

    Launch your Arduino IDE.

3. Install the Library:

    * Navigate to Sketch -> Include Library -> Add .ZIP Library... in the Arduino IDE menu.
    * Select the downloaded clogger library ZIP file and click Open.
    * The Arduino IDE will automatically extract and install the library.

## Configuration

### Set Log Severity

Define `CLOGGER_SEVERITY` ​​before​​ including `clogger.h` to filter logs by severity:

```c++
// Choose one severity level (ordered by priority):
#define CLOGGER_SEVERITY_VERBOSE  // Allow all logs
#define CLOGGER_SEVERITY_DEBUG
#define CLOGGER_SEVERITY_INFO     // Default if not specified
#define CLOGGER_SEVERITY_WARN
#define CLOGGER_SEVERITY_ERROR
#define CLOGGER_SEVERITY_FATAL
#define CLOGGER_SEVERITY_NONE     // Disable all logs

#define CLOGGER_SEVERITY CLOGGER_SEVERITY_DEBUG  // Example: Enable DEBUG+ logs
#include "clogger.h"
```

## Usage

### Basic Logging

```c++
void setup() {
  Serial.begin(115200);
  CLOGI("Initializing...");  // Log with INFO level
}

void loop() {
  CLOGD("Sensor value: %d", readSensor());  // DEBUG-level log
}
```

### Log Severity Macros

```c++
CLOGV("Verbose trace");    // Detailed tracing (lowest priority)
CLOGD("Debug data");       // Diagnostic information
CLOGI("Status update");    // General operational messages
CLOGW("Potential issue");  // Unexpected but recoverable
CLOGE("Error occurred");   // Runtime errors requiring attention
CLOGF("Critical failure"); // Fatal events (highest priority)
```

## Log Output Format

Each log line includes structured metadata:

`[HH:MM:SS.mmm] [Severity] [File:Line Function] Message`

​* **Timestamp**​​: HH:MM:SS.mmm (24-hour format, 3-digit milliseconds)
​​

* **Severity​​**: Single character (V, D, I, W, E, F)
​​
* **File**​​: Base filename (without path)

​​* **Line**​​: Source code line number
​​

* **Function**​​: Calling function name

​​* **Message**​​: User-provided formatted string

## Full Example

```c++
#define CLOGGER_SEVERITY CLOGGER_SEVERITY_VERBOSE
#include "clogger.h"

void setup() {
  Serial.begin(115200);
  int value = 1234;
  
  CLOGV("Verbose trace: value=%d", value);  // Visible at VERBOSE
  CLOGD("Debug data: value=%d", value);     // DEBUG+
  CLOGI("System status: value=%d", value);  // INFO+
  CLOGW("Low memory: value=%d", value);     // WARN+
  CLOGE("Sensor error: code=%d", value);    // ERROR+
}

void loop() {
  static uint32_t count = 0;
  CLOGI("Cycle count: %u", count++);  // Log every loop iteration
  delay(1000);
}
```

### Output Example

```log
00:00:00.000 V sketch.ino:5 setup] Verbose trace: value=1234
00:00:00.001 D sketch.ino:6 setup] Debug data: value=1234
00:00:00.002 I sketch.ino:7 setup] System status: value=1234
00:00:00.003 W sketch.ino:8 setup] Low memory: value=1234
00:00:00.004 E sketch.ino:9 setup] Sensor error: code=1234
00:00:01.005 I sketch.ino:14 loop] Cycle count: 0
00:00:02.006 I sketch.ino:14 loop] Cycle count: 1
...
```

## License

MIT License. See [LICENSE](LICENSE)
