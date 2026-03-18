#ifndef BLUETOOTH_MESSAGE_H_
#define BLUETOOTH_MESSAGE_H_
#include "bluetooth-message.h"
#endif

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void BluetoothSerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::Init(
    const char *bluetoothName) {
  serial->begin(bluetoothName);
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
char BluetoothSerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS,
                            MAX_CALLBACKS>::getChar() {
  return serial->read();
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
uint32_t BluetoothSerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS,
                                MAX_CALLBACKS>::dataAvailable() {
  return serial->available();
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
BluetoothSerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::
    BluetoothSerialMessage(BluetoothSerial *serial) {
  this->serial = serial;
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void BluetoothSerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS,
                            MAX_CALLBACKS>::PrintArgs() {
  serial->print("Current number of args: ");
  serial->println(this->populatedArgs);
  for (int i = 0; i < this->populatedArgs; i++) {
    serial->print(this->args[i]);
    serial->print(" ");
  }
  serial->println();
}