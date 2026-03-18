#pragma once
#include "message.h"
#include <BluetoothSerial.h>
#include <cstdint>

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
class BluetoothSerialMessage
    : public Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS> {
public:
  /**
   * @brief Construct a new Bluetooth Serial Message object
   */
  BluetoothSerialMessage(BluetoothSerial *serial);

  void Init(uint32_t baudRate) override { this->Init("BluetoothMessage"); }
  /**
   * @brief Initialize the BluetoothSerialMessage object
   */
  void Init(const char *bluetoothName);

  /**
   * @brief prints the args array to the serial monitor
   */
  void PrintArgs() override;

private:
  /**
   * @brief reads the serial data and stores it in the data array
   */
  char getChar() override;
  uint32_t dataAvailable() override;

  BluetoothSerial *serial;
};

#ifndef BLUETOOTH_MESSAGE_H_
#define BLUETOOTH_MESSAGE_H_
#include "bluetooth-message.cpp"
#endif