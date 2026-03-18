/**
 * @file Serialmessage.h
 * @brief This file contains the SerialMessage class
 * @details This file contains the SerialMessage class which is used to parse
 * serial messages
 * @version 1.0.0
 * @author Quinn Henthorne. Contact: quinn.henthorne@gmail.com
 */

#pragma once

#include <Arduino.h>
#include <cstdint>

#include "message.h"

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
class SerialMessage
    : public Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS> {
public:
  /**
   * @brief Construct a new Serial Message object
   */
  SerialMessage(HardwareSerial *serial);

  /**
   * @brief Initialize the SerialMessage object
   */
  void Init(uint32_t baudRate) override;

  /**
   * @brief Prints the args array to the serial monitor
   */
  void PrintArgs() override;

protected:
  /**
   * @brief reads the serial data and stores it in the data array
   * @return the next character in the serial buffer
   */
  char getChar() override;

  /**
   * @brief returns the number of bytes available in the serial buffer
   * @return the number of bytes available in the serial buffer
   */
  uint32_t dataAvailable() override;

private:
  HardwareSerial *serial{nullptr};
};

#ifndef SERIAL_MESSAGE_H_
#define SERIAL_MESSAGE_H_
#include "serial-message.cpp"
#endif // SERIAL_MESSAGE_H_