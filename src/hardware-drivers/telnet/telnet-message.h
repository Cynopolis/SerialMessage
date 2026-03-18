#pragma once

#include <Arduino.h>
#include <ESPTelnet.h>
#include <cassert>
#include <stdexcept>

#include "message.h"

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
class TelnetMessage
    : public Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS> {
public:
  /**
   * @brief Construct a new Bluetooth Serial Message object
   */
  TelnetMessage(ESPTelnet *telnet) : telnet(telnet) {}

  void Init(uint32_t baudRate) override {
    throw std::runtime_error(
        "Never call this without a parameter, this will not function properly "
        "without a callback function"); // Throws an exception
  }
  /**
   * @brief Initialize the TelnetMessage object
   * @pre The WiFi object must have a state of WL_CONNECTED
   */
  void Init(void (*callback)(std::string data));

  /**
   * @brief prints the args array to the telnet monitor
   */
  void PrintArgs() override;

  void SetString(const char *data);

  void SetOnInputRecieved(void (*callback)(std::string data));

private:
  /**
   * @brief reads the telnet data and stores it in the data array
   */
  char getChar() override;

  /**
   * @brief returns the amount of data available
   */
  uint32_t dataAvailable() override;

  static void onConnectCallback(std::string ip);
  static void onConnectionAttemptCallback(std::string ip);
  static void onReconnectCallback(std::string ip);
  static void onDisconnectCallback(std::string ip);

  ESPTelnet *telnet;

  const char *incomingData = nullptr;
  uint32_t incomingDataLength{0};
  uint32_t incomingDataCharIndex{0};
};

#ifndef TELNET_MESSAGE_H_
#define TELNET_MESSAGE_H_
#include "telnet-message.cpp"
#endif