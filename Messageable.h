#pragma once

#include "MESSAGE-INTF.h"
#include <cstdint>

class Messageable {
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
  virtual void Update() = 0;

  /**
   * @brief Returns true if there is new data available
   * @return true if there is new data available
   */
  virtual bool IsNewData() = 0;

  /**
   * @brief Clears the new data flag
   */
  virtual void ClearNewData() = 0;

  /**
   * @brief Return a pointer to the args array
   * @return a pointer to the args array
   */
  virtual int32_t *GetArgs() = 0;

  /**
   * @brief Returns the number of args that have been populated for the current
   * message
   * @return the number of args that have been populated for the current message
   */
  virtual uint32_t GetMaxArgs() = 0;

  /**
   * @brief Returns the number of args that have been populated for the current
   * message
   * @return the number of args that have been populated for the current message
   */
  virtual uint32_t GetPopulatedArgs() = 0;

  /**
   * @brief Register a callback function to be called when new data is received
   */
  virtual void RegisterCallback(const MESSAGE_INTF::Callback &callback) = 0;

private:
};