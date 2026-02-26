/**
 * @file SerialMessage.h
 * @brief This file contains the SerialMessage class
 * @details This file contains the SerialMessage class which is used to parse
 * serial messages
 * @version 1.0.0
 * @author Quinn Henthorne. Contact: quinn.henthorne@gmail.com
 */

#pragma once

#include <Arduino.h>

#include "Message.h"

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
char SerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::getChar() {
  return this->serial->read();
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
uint32_t
SerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::dataAvailable() {
  return this->serial->available();
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
SerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::SerialMessage(
    HardwareSerial *serial)
    : serial(serial) {}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void SerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::Init(
    uint32_t baudRate) {
  this->serial->begin(baudRate);
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void SerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::PrintArgs() {
  return;
  this->serial->print("Current number of args: ");
  this->serial->println(this->populatedArgs);
  for (int i = 0; i < this->populatedArgs; i++) {
    this->serial->print(this->args[i]);
    this->serial->print(" ");
  }
  this->serial->println();
}