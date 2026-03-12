/**
 * @file message.h
 * @brief This file contains the Message base class which is can be inherited to
 * parse serial messages over any type of protocol
 * @version 1.0.0
 * @author Quinn Henthorne. Contact: quinn.henthorne@gmail.com
 */

#pragma once

#include "message-callback.h"
#include <array>
#include <cstdint>

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
class Message {
public:
  /**
   * @brief Initialize the Message object
   */
  virtual void Init(uint32_t baudRate) = 0;

  /**
   * @brief Prints the args array to the serial monitor
   */
  virtual void PrintArgs() = 0;

  /**
   * @brief Update the Message object and parse any data that's available
   */
  void Update();

  /**
   * @brief Returns true if there is new data available
   * @return true if there is new data available
   */
  bool IsNewData();

  /**
   * @brief Clears the new data flag
   */
  void ClearNewData();

  /**
   * @brief Return a pointer to the args array
   * @return a pointer to the args array
   */
  int32_t *GetArgs();

  /**
   * @brief Returns the number of args that have been populated for the current
   * message
   * @return the number of args that have been populated for the current message
   */
  uint32_t GetMaxArgs();

  /**
   * @brief Returns the number of args that have been populated for the current
   * message
   * @return the number of args that have been populated for the current message
   */
  uint32_t GetPopulatedArgs();

  /**
   * @brief Register a callback function to be called when new data is received
   */
  bool RegisterCallback(const callback_intf::Callback &callback);

protected:
  enum SerialState : uint8_t {
    IDLE,
    NEW_DATA,
    DATA_RECIEVED,
    RECIEVE_IN_PROGRESS
  };
  Message() = default;
  /**
   * @brief reads the serial data and stores it in the data array
   * @return the next character in the serial buffer
   */
  virtual char getChar() = 0;

  /**
   * @brief returns the number of bytes available in the serial buffer
   * @return the number of bytes available in the serial buffer
   */
  virtual uint32_t dataAvailable() = 0;

  /**
   * @brief Takes in any available serial data and reads it into the buffer if
   * our start character is hit. Also marks what state the Message object is in
   */
  void readSerial();

  /**
   * @brief Parses the received data and populates the args array
   */
  void parseData();

  /**
   * @brief Call a registered callback function with the received data
   */
  void callCallback();

  SerialState state{IDLE};
  char data[SERIAL_BUFFER_SIZE]; // an array to store the received data
  char
      temp_data[SERIAL_BUFFER_SIZE]; // an array that will be used with strtok()
  uint32_t ndx{0};
  uint32_t populatedArgs{
      0}; // the number of args that have been populated for the current message
  std::array<int32_t, MAX_ARGS> args;
  const char startMarker = '!';
  const char endMarker = ';';

  std::array<callback_intf::Callback, MAX_CALLBACKS>
      callbacks; // array of callbacks to be called when new data is received
  uint32_t numRegisteredCallbacks{0}; // the number of registered callbacks
};

#ifndef MESSAGE_H_
#define MESSAGE_H_
#include "message.cpp"
#endif
