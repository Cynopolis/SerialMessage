#pragma once
#include "message.h"
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

#ifndef USB_MESSAGE_H_
#define USB_MESSAGE_H_
#include "usb-message.cpp"
#endif