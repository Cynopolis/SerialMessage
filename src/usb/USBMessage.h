#pragma once
#include "Serialmessage.h"
#include <USBCDC.h>

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
class USBMessage : public Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS> {
public:
  /**
   * @brief Construct a new USB Serial Message object
   */
  USBMessage(USBCDC *serial);
  void Init(uint32_t baudRate) override;
  /**
   * @brief prints the args array to the serial monitor
   */
  void PrintArgs() override;

protected:
  char getChar() override;
  uint32_t dataAvailable() override;

private:
  USBCDC *serial;
};

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
USBMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::USBMessage(
    USBCDC *USBSerial)
    : serial(USBSerial) {}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
char USBMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::getChar() {
  return serial->read();
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
uint32_t
USBMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::dataAvailable() {
  return serial->available();
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void USBMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::Init(
    uint32_t baudRate) {
  serial->begin();
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void USBMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::PrintArgs() {
  serial->print("Current number of args: ");
  serial->println(this->populatedArgs);
  for (int i = 0; i < this->populatedArgs; i++) {
    serial->print(this->args[i]);
    serial->print(" ");
  }
  serial->println();
}