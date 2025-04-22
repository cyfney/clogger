#define CLOGGER_SEVERITY CLOGGER_SEVERITY_VERBOSE
#include "clogger.h"

void setup() {
  Serial.begin(115200);

  int value = 1234;

  CLOGV("value: %d", value);
  CLOGI("value: %d", value);
  CLOGD("value: %d", value);
  CLOGW("value: %d", value);
  CLOGE("value: %d", value);
}

void loop() {
  static unsigned int count = 0;
  CLOGI("loop count: %u", count++);
  delay(1000);
}