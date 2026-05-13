#pragma once

#ifndef __CLOGGER_FREERTOS_H__
#define __CLOGGER_FREERTOS_H__

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <array>
#include <cstdarg>
#include <cstdio>

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
  template <typename T, size_t size>
  static constexpr size_t FileNameOffset(const T (&file_path)[size], size_t i = size) noexcept {
    return (i == 0) ? 0 : (file_path[i - 1] == '/' || file_path[i - 1] == '\\') ? i : FileNameOffset(file_path, i - 1);
  }

  static std::array<char, 13> GetTimeStr() noexcept {
    constexpr uint64_t kHundredHoursMs = 100ULL * 60 * 60 * 1000;

    std::array<char, 13> result{};

    const uint32_t milliseconds_in_100h = static_cast<uint32_t>(pdTICKS_TO_MS(xTaskGetTickCount()) % kHundredHoursMs);

    const uint32_t milliseconds = milliseconds_in_100h % 1000;
    const uint32_t total_seconds = milliseconds_in_100h / 1000;

    const uint32_t seconds = total_seconds % 60;
    const uint32_t total_minutes = total_seconds / 60;

    const uint32_t minutes = total_minutes % 60;
    const uint32_t hours = total_minutes / 60;

    result[0] = '0' + hours / 10;
    result[1] = '0' + hours % 10;
    result[2] = '.';

    result[3] = '0' + minutes / 10;
    result[4] = '0' + minutes % 10;
    result[5] = '.';

    result[6] = '0' + seconds / 10;
    result[7] = '0' + seconds % 10;
    result[8] = '.';

    result[9] = '0' + milliseconds / 100;
    result[10] = '0' + milliseconds / 10 % 10;
    result[11] = '0' + milliseconds % 10;
    result[12] = '\0';

    return result;
  }
};
}  // namespace clogger

#if CLOGGER_SEVERITY <= CLOGGER_SEVERITY_VERBOSE
#define CLOGV(fmt, ...)                                                                                                                      \
  fprintf(stdout, "%.12s V %s:%d %s] " fmt "\n", clogger::Logger::GetTimeStr().data(), __FILE__ + clogger::Logger::FileNameOffset(__FILE__), \
          __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define CLOGV(fmt, ...) (void(0))
#endif

#if CLOGGER_SEVERITY <= CLOGGER_SEVERITY_DEBUG
#define CLOGD(fmt, ...)                                                                                                                      \
  fprintf(stdout, "%.12s D %s:%d %s] " fmt "\n", clogger::Logger::GetTimeStr().data(), __FILE__ + clogger::Logger::FileNameOffset(__FILE__), \
          __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define CLOGD(fmt, ...) (void(0))
#endif

#if CLOGGER_SEVERITY <= CLOGGER_SEVERITY_INFO
#define CLOGI(fmt, ...)                                                                                                                      \
  fprintf(stdout, "%.12s I %s:%d %s] " fmt "\n", clogger::Logger::GetTimeStr().data(), __FILE__ + clogger::Logger::FileNameOffset(__FILE__), \
          __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define CLOGI(fmt, ...) (void(0))
#endif

#if CLOGGER_SEVERITY <= CLOGGER_SEVERITY_WARN
#define CLOGW(fmt, ...)                                                                                                                      \
  fprintf(stdout, "%.12s W %s:%d %s] " fmt "\n", clogger::Logger::GetTimeStr().data(), __FILE__ + clogger::Logger::FileNameOffset(__FILE__), \
          __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define CLOGW(fmt, ...) (void(0))
#endif

#if CLOGGER_SEVERITY <= CLOGGER_SEVERITY_ERROR
#define CLOGE(fmt, ...)                                                                                                                      \
  fprintf(stdout, "%.12s E %s:%d %s] " fmt "\n", clogger::Logger::GetTimeStr().data(), __FILE__ + clogger::Logger::FileNameOffset(__FILE__), \
          __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define CLOGE(fmt, ...) (void(0))
#endif

#endif