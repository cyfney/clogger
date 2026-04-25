#define CLOGGER_SEVERITY CLOGGER_SEVERITY_VERBOSE
#include "clogger.h"

void setup() {
  Serial.begin(115200);

  const int value = 1024;

  CLOGV("value: %d", value);
  CLOGI("value: %d", value);
  CLOGD("value: %d", value);
  CLOGW("value: %d", value);
  CLOGE("value: %d", value);
}

void loop() {
  static int s_count = 0;
  CLOGI("loop count: %d", s_count++);
  delay(1000);
}