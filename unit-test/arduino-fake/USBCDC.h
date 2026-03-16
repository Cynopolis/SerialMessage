#pragma once

class USBCDC {
public:
  char read();
  bool available();
  void begin();
  void print(void *data);
  void print(const char *data);
  void println(void *data);
  void println(const char *data);
  void println();
};