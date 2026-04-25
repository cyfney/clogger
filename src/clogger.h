#pragma once

#ifndef __CLOGGER_H__
#define __CLOGGER_H__

#if defined(ARDUINO_ARCH_ESP32)
#include "clogger_freertos.h"
#elif defined(ARDUINO)
#include "clogger_common.h"
#else
#error "Unsupported platform"
#endif

#endif