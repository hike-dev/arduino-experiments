#pragma once

#include <Arduino.h>

class IntervalTimer {
 public:
  explicit IntervalTimer(unsigned long intervalMs)
      : interval(intervalMs), last(millis()) {}

  bool ready() {
    const unsigned long now = millis();
    if (now - last >= interval) {
      last = now;
      return true;
    }
    return false;
  }

  void reset() { last = millis(); }

 private:
  unsigned long interval;
  unsigned long last;
};
