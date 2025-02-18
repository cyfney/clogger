#include "clog.h"

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