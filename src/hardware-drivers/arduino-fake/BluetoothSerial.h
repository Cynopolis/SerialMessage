#pragma once
#include <cstdint>

class BluetoothSerial {
public:
  void begin(const char *bluetoothName);
  char read();
  bool available();
  void print(const void *data);
  void println(const void *data);
};