#pragma once

#include <cstdint>

class HardwareSerial {
  void begin(uint32_t baudRate);
  char read();
  bool available();
  void print(void *data);
  void println(void *data);
};