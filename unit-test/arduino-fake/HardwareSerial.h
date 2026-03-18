#pragma once

#include <cstdint>

class HardwareSerial {
public:
  void begin(uint32_t baudRate);
  char read();
  bool available();
  void print(void *data);
  void print(const char *data);
  void println(void *data);
  void println(const char *data);
  void println();
};