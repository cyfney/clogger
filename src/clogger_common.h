#pragma once

#ifndef __CLOGGER_COMMON_H__
#define __CLOGGER_COMMON_H__

#include <Arduino.h>
#include <WString.h>
#include <stdarg.h>
#include <stdio.h>

#define CLOGGER_SEVERITY_VERBOSE (1)
#define CLOGGER_SEVERITY_DEBUG (2)
#define CLOGGER_SEVERITY_INFO (3)
#define CLOGGER_SEVERITY_WARN (4)
#define CLOGGER_SEVERITY_ERROR (5)
#define CLOGGER_SEVERITY_NONE (6)

#ifndef CLOGGER_SEVERITY
#define CLOGGER_SEVERITY CLOGGER_SEVERITY_INFO
#endif

namespace clogger {
class Logger final {
 public:
  static constexpr int kTimeStrLength = 12;

  template <typename T, size_t size>
  static constexpr size_t FileNameOffset(const T (&file_path)[size], size_t i = size - 1) {
    static_assert(size > 1, "");
    return file_path[i] == '/' || file_path[i] == '\\' ? i + 1 : (i == 0 ? 0 : FileNameOffset(file_path, i - 1));
  }

  static void Log(int severity, const __FlashStringHelper *file_name, const size_t file_name_begin, const size_t line_num, const char *function,
                  const __FlashStringHelper *fmt, ...) {
    char prefix[kTimeStrLength + 3];
    GetTimeStr(prefix);
    prefix[kTimeStrLength] = ' ';
    prefix[kTimeStrLength + 1] = SeverityToChar(severity);
    prefix[kTimeStrLength + 2] = ' ';
    Serial.write(prefix, sizeof(prefix));

    Serial.print(reinterpret_cast<const __FlashStringHelper *>(reinterpret_cast<PGM_P>(file_name) + file_name_begin));
    Serial.print(':');
    Serial.print(line_num);
    Serial.print(' ');
    Serial.print(function);
    Serial.print(F("] "));

    va_list args;
    va_start(args, fmt);
    const auto length = vsnprintf_P(nullptr, 0, reinterpret_cast<const char *>(fmt), args);
    va_end(args);

    char *buffer = new char[length + 1];
    if (buffer == nullptr) {
      abort();
    }

    va_start(args, fmt);
    vsnprintf_P(buffer, length + 1, reinterpret_cast<const char *>(fmt), args);
    va_end(args);
    Serial.write(buffer, length);
    delete[] buffer;
  }

 private:
  static char SeverityToChar(const int severity) {
    switch (severity) {
      case CLOGGER_SEVERITY_VERBOSE: {
        return 'V';
      }
      case CLOGGER_SEVERITY_DEBUG: {
        return 'D';
      }
      case CLOGGER_SEVERITY_INFO: {
        return 'I';
      }
      case CLOGGER_SEVERITY_WARN: {
        return 'W';
      }
      case CLOGGER_SEVERITY_ERROR: {
        return 'E';
      }
      default: {
        return 'X';
      }
    }
  }

  static void GetTimeStr(char *const time_str) {
    const auto total_ms = millis();

    const int hours = total_ms / 3600000 % 100;
    const int minutes = total_ms / 60000 % 60;
    const int seconds = total_ms / 1000 % 60;
    const int milliseconds = total_ms % 1000;

    time_str[0] = '0' + hours / 10;
    time_str[1] = '0' + hours % 10;
    time_str[2] = '.';

    time_str[3] = '0' + minutes / 10;
    time_str[4] = '0' + minutes % 10;
    time_str[5] = '.';

    time_str[6] = '0' + seconds / 10;
    time_str[7] = '0' + seconds % 10;
    time_str[8] = '.';

    time_str[9] = '0' + milliseconds / 100;
    time_str[10] = '0' + milliseconds / 10 % 10;
    time_str[11] = '0' + milliseconds % 10;
  }
};
}  // namespace clogger

#if CLOGGER_SEVERITY <= CLOGGER_SEVERITY_VERBOSE
#define CLOGV(fmt, ...)                                                                                                                          \
  clogger::Logger::Log(CLOGGER_SEVERITY_VERBOSE, F(__FILE__), clogger::Logger::FileNameOffset(__FILE__), __LINE__, __FUNCTION__, F("" fmt "\n"), \
                       ##__VA_ARGS__)
#else
#define CLOGV(fmt, ...) (void(0))
#endif

#if CLOGGER_SEVERITY <= CLOGGER_SEVERITY_DEBUG
#define CLOGD(fmt, ...)                                                                                                                        \
  clogger::Logger::Log(CLOGGER_SEVERITY_DEBUG, F(__FILE__), clogger::Logger::FileNameOffset(__FILE__), __LINE__, __FUNCTION__, F("" fmt "\n"), \
                       ##__VA_ARGS__)
#else
#define CLOGD(fmt, ...) (void(0))
#endif

#if CLOGGER_SEVERITY <= CLOGGER_SEVERITY_INFO
#define CLOGI(fmt, ...)                                                                                                                       \
  clogger::Logger::Log(CLOGGER_SEVERITY_INFO, F(__FILE__), clogger::Logger::FileNameOffset(__FILE__), __LINE__, __FUNCTION__, F("" fmt "\n"), \
                       ##__VA_ARGS__)
#else
#define CLOGI(fmt, ...) (void(0))
#endif

#if CLOGGER_SEVERITY <= CLOGGER_SEVERITY_WARN
#define CLOGW(fmt, ...)                                                                                                                       \
  clogger::Logger::Log(CLOGGER_SEVERITY_WARN, F(__FILE__), clogger::Logger::FileNameOffset(__FILE__), __LINE__, __FUNCTION__, F("" fmt "\n"), \
                       ##__VA_ARGS__)
#else
#define CLOGW(fmt, ...) (void(0))
#endif

#if CLOGGER_SEVERITY <= CLOGGER_SEVERITY_ERROR
#define CLOGE(fmt, ...)                                                                                                                        \
  clogger::Logger::Log(CLOGGER_SEVERITY_ERROR, F(__FILE__), clogger::Logger::FileNameOffset(__FILE__), __LINE__, __FUNCTION__, F("" fmt "\n"), \
                       ##__VA_ARGS__)
#else
#define CLOGE(fmt, ...) (void(0))
#endif

#endif