#pragma once

#ifndef __CLOG_ESP32_H__
#define __CLOG_ESP32_H__

#include <Arduino.h>
#include <stdarg.h>

#include <type_traits>

#include "esp_timer.h"

struct Clog {
  template <typename T, size_t size>
  static constexpr size_t FileNameOffset(const T (&file_path)[size], size_t i = size - 1) {
    static_assert(size > 1, "");
    return file_path[i] == '/' || file_path[i] == '\\' ? i + 1 : (i == 0 ? 0 : FileNameOffset(file_path, i - 1));
  }

  static void Print(const char *file_name, const uint32_t line_num, const char *function, const char *fmt, ...) {
    const auto now = esp_timer_get_time() / 1000ULL;
    const uint_fast16_t millis = now % 1000;
    const uint_fast8_t seconds = now / 1000 % 60;
    const uint_fast8_t minutes = now / 60000 % 60;
    const uint_fast8_t hours = now / 3600000 % 100;
    Serial.printf("%02" PRIuFAST8 ":%02" PRIuFAST8 ":%02" PRIuFAST8 ".%03" PRIuFAST8 " %s:%" PRIu32 " %s] ",
                  hours,
                  minutes,
                  seconds,
                  millis,
                  file_name,
                  line_num,
                  function);
    va_list args;
    va_start(args, fmt);
    Serial.vprintf(fmt, args);
    va_end(args);
  }
};

#define CLOG(fmt, ...)                                                                     \
  Clog::Print(&__FILE__[std::integral_constant<size_t, Clog::FileNameOffset(__FILE__)>()], \
              __LINE__,                                                                    \
              __FUNCTION__,                                                                \
              fmt "\n",                                                                    \
              ##__VA_ARGS__)

#endif