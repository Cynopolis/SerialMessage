#ifndef USB_MESSAGE_H_
#define USB_MESSAGE_H_
#include "usb-message.h"
#endif

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