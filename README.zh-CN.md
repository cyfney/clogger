# CLOG

[![Arduino AVR Build](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml/badge.svg)](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml) [![Arduino AVR Build](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml/badge.svg)](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml)

## 简介

`clogger`模块是一个专为 Arduino 项目设计的极为便捷的日志记录工具，适用于 AVR 和 ESP32 架构。其主要目的是为用户提供一种在 Arduino 平台上轻松进行日志记录的方法，使用起来就像使用广为人知的 `printf` 函数一样方便。

在传统的 Arduino 开发中，记录带有详细时间戳、文件名、行号和函数名的信息可能是一个繁琐的过程。然而，使用 `clogger` 模块时，用户只需包含 `clogger.h` 头文件，然后就可以开始使用 `CLOG` 宏，该宏的行为类似于 printf。这意味着用户可以轻松地格式化并打印日志消息，而无需担心添加时间戳、文件信息等底层的复杂性。

无论你是在调试代码、监控 Arduino 项目的状态，还是只是想跟踪重要事件，`clogger` 模块都通过提供一个简单直观的日志记录解决方案来简化这个过程。

## 安装

要在你的 Arduino 项目中使用 clogger 模块，请按照以下步骤操作：

1. 下载库文件：

    从发布页面或源代码仓库下载 clogger 库的 ZIP 文件。

2. 打开 Arduino IDE：

    启动你的 Arduino IDE。

3. 安装库文件：

    - 在 Arduino IDE 菜单中，选择 Sketch -> Include Library -> Add .ZIP Library...。
    - 选择下载的 clogger 库 ZIP 文件，然后点击 Open。
    - Arduino IDE 会自动解压并安装该库。

## 使用方法

1. 初始化

    在你的Arduino的`setup()`函数中，像往常一样初始化串口通信。

    ```c++
    void setup() {
    Serial.begin(115200);
    }
    ```

2. 打印日志消息

    使用 CLOG 宏来打印日志消息。该宏接受一个格式字符串和可选的参数，类似于 printf 函数。

    - 简单的日志消息：

    ```c++
    CLOG("in setup");
    ```

    - 带有变量的日志消息：

    ```c++
    int value = 10;
    CLOG("value: %d", value);
    ```

    - 只打印当前时间、函数、行号等信息：

    ```c++
    CLOG_TRACE();
    ```

## 示例

以下是使用 clogger 模块的完整示例：

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

## 日志输出示例

```log
00:00:00.000 sketch.ino:4 setup] in setup
00:00:00.001 sketch.ino:6 setup] value: 10
00:00:01.002 sketch.ino:11 loop] loop count: 0
00:00:02.003 sketch.ino:11 loop] loop count: 1
00:00:03.004 sketch.ino:11 loop] loop count: 2
...
```

## 日志输出格式说明

日志输出格式由几个部分组成：

- **时间戳**：日志消息的第一部分是时间戳，格式为 HH:MM:SS.mmm，其中 HH 是小时（00 - 99），MM 是分钟（00 - 59），SS 是秒（00 - 59），mmm 是毫秒（000 - 999）。

- **文件名**：时间戳之后，显示打印日志消息的文件名，后面跟着一个冒号。

- **行号**：文件名旁边是调用 CLOG 宏的文件中的行号。

- **函数名**：行号之后，显示调用 CLOG 宏的函数名，后面跟着一个右方括号。

- **日志消息**：最后，打印日志消息本身，如果提供了格式化变量，日志消息中可以包含这些变量。

## 许可证

本模块根据 MIT 许可证 发布。
