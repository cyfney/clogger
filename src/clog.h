#pragma once

#ifndef __CLOG_H__
#define __CLOG_H__

#ifdef ARDUINO_ARCH_ESP32
#include "clog_esp32.h"
#else
#include "clog_avr.h"
#endif

#endif