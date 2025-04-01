# CLOG

[![Arduino AVR Build](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml/badge.svg)](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml) [![Arduino AVR Build](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml/badge.svg)](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml)

[中文版](README.zh-CN.md)

## Introduction

The `clogger` module is a highly convenient logging utility specifically designed for Arduino projects, catering to both AVR and ESP32 architectures. Its primary goal is to provide users with an effortless way to perform logging tasks on Arduino platforms, making it as easy as using the well-known `printf` function.

In traditional Arduino development, logging information with detailed timestamps, file names, line numbers, and function names can be a cumbersome process. However, with the clogger module, users can simply include the `clogger.h` header file and start using the `CLOG` macro, which mimics the behavior of `printf`. This means that users can easily format and print log messages without having to worry about the underlying complexity of adding timestamps, file information, etc.

Whether you are debugging your code, monitoring the state of your Arduino project, or simply want to keep track of important events, the `clogger` module simplifies the process by providing a straightforward and intuitive logging solution.

## Installation

To use the `clogger` module in your Arduino project, follow these steps:

1. Download the Library:

    Download the clogger library as a ZIP file from the release page or the source repository.

2. Open Arduino IDE:

    Launch your Arduino IDE.

3. Install the Library:

    - Navigate to Sketch -> Include Library -> Add .ZIP Library... in the Arduino IDE menu.
    - Select the downloaded clogger library ZIP file and click Open.
    - The Arduino IDE will automatically extract and install the library.

## Usage

1. Initialization

In the `setup()` function of your Arduino sketch, initialize the serial communication as usual.

```c++
void setup() {
  Serial.begin(115200);
}
```

2. Logging Messages

Use the CLOG macro to print log messages. The macro takes a format string and optional arguments, similar to the `printf` function.

- Simple Log Message:

```c++
CLOG("in setup");
```

- Log Message with Variables:

```c++
int value = 10;
CLOG("value: %d", value);
```

- Log only basic metadata (timestamp, function name, line number):

```c++
CLOG_TRACE();
```

## Example

Here is a complete example of using the `clogger` module:

```c++
#include "clogger.h"

void setup() {
  Serial.begin(115200);
  CLOG("in setup");
  int value = 10;
  CLOG("value: %d", value);
}

void loop() {
  static unsigned int count = 0;
  CLOG("loop count: %u", count++);
  delay(1000);
}
```

## Log Output Example

```log
00:00:00.000 sketch.ino:4 setup] in setup
00:00:00.001 sketch.ino:6 setup] value: 10
00:00:01.002 sketch.ino:11 loop] loop count: 0
00:00:02.003 sketch.ino:11 loop] loop count: 1
00:00:03.004 sketch.ino:11 loop] loop count: 2
...
```

### Log Output Format Explanation

The log output format consists of several parts:

- **Timestamp**: The first part of the log message is the timestamp in the format HH:MM:SS.mmm, where HH is the hours (00 - 99), MM is the minutes (00 - 59), SS is the seconds (00 - 59), and mmm is the milliseconds (000 - 999).

- **File Name**: After the timestamp, the file name where the log message is printed is shown, followed by a colon.

- **Line Number**: Next to the file name is the line number in the file where the CLOG macro is called.

- **Function Name**: After the line number, the name of the function where the CLOG macro is called is shown, followed by a closing square bracket.

- **Log Message**: Finally, the log message itself is printed, which can include formatted variables if provided.

## License

This module is released under the MIT License.
