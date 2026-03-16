#pragma once

#include <string>

class ESPTelnet {
public:
  void begin(int portNumber);
  void onConnect(void (*callback)(std::string data));
  void onConnectionAttempt(void (*callback)(std::string data));
  void onReconnect(void (*callback)(std::string data));
  void onDisconnect(void (*callback)(std::string data));
  void onInputReceived(void (*callback)(std::string data));

  void print(void *data);
  void print(const char *data);

  void println(void *data);
  void println(const char *data);
  void println();
};