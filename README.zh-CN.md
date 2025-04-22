# CLOG

[![Arduino AVR Build](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml/badge.svg)](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml) [![Arduino AVR Build](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml/badge.svg)](https://github.com/cyfney/clogger/actions/workflows/arduino_avr_build.yml)

## 简介

`clogger`是一个专为 Arduino 项目设计的轻量级日志库，支持 AVR 和 ESP32 架构。提供类似 printf 的接口，支持按日志等级过滤、毫秒级时间戳和元数据（文件、行号、函数名）。

## 特性

* **多日志等级**：Verbose、Debug、Info、Warn、Error、Fatal。

* **低开销**：通过编译时过滤禁用低优先级日志。

* **精确时间戳**：毫秒级时间戳。

* **跨平台**：兼容 AVR (Arduino) 和 ESP32。

## 安装

要在你的 Arduino 项目中使用 clogger 模块，请按照以下步骤操作：

1. 下载库文件：

    从发布页面或源代码仓库下载 clogger 库的 ZIP 文件。

2. 打开 Arduino IDE：

    启动你的 Arduino IDE。

3. 安装库文件：

    * 在 Arduino IDE 菜单中，选择 Sketch -> Include Library -> Add .ZIP Library...。
    * 选择下载的 clogger 库 ZIP 文件，然后点击 Open。
    * Arduino IDE 会自动解压并安装该库。

## 配置

### 设置日志等级

在包含 `clogger.h` ​​之前​​ 定义 `CLOGGER_SEVERITY` 以过滤日志：

```c++
// 可选等级（按优先级升序）：
#define CLOGGER_SEVERITY_VERBOSE  // 允许所有日志
#define CLOGGER_SEVERITY_DEBUG
#define CLOGGER_SEVERITY_INFO     // 未定义时的默认值
#define CLOGGER_SEVERITY_WARN
#define CLOGGER_SEVERITY_ERROR
#define CLOGGER_SEVERITY_FATAL
#define CLOGGER_SEVERITY_NONE     // 禁用所有日志

#define CLOGGER_SEVERITY CLOGGER_SEVERITY_DEBUG  // 示例：启用DEBUG及以上等级
#include "clogger.h"
```

## 使用

### 基础日志

```c++
void setup() {
  Serial.begin(115200);
  CLOGI("Initializing...");  // Log with INFO level
}

void loop() {
  CLOGD("Sensor value: %d", readSensor());  // DEBUG-level log
}
```

### 日志等级宏

```c++
CLOGV("Verbose trace");    // 详细跟踪（最低优先级）
CLOGD("Debug data");       // 调试信息
CLOGI("Status update");    // 常规运行状态
CLOGW("Potential issue");  // 可恢复的异常
CLOGE("Error occurred");   // 需要关注的错误
CLOGF("Critical failure");  // 导致系统终止的错误（最高优先级）
```

## 日志格式

每行日志包含结构化元数据：

`[HH:MM:SS.mmm] [等级] [文件:行号 函数名] 消息`

* **​时间戳​**​：HH:MM:SS.mmm（24小时制，3位毫秒）

​​* **等级**​​：单字母表示（V、D、I、W、E、F）

​​* **文件**​​：源文件名（不含路径）

​​* **行号**​​：日志调用处的行号

​​* **函数名**​​：调用函数名称

​​* **消息**​​：用户提供的格式化字符串

## 完整示例

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

### 输出示例

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

## 许可证

MIT 许可证。详见 LICENSE[LICENSE]
