#ifndef MESSAGE_H_
#define MESSAGE_H_
#include "message.h"
#endif

#include <cstdlib>
#include <cstring>

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::readSerial() {
  char c;

  // read the incoming serial data:
  while (this->dataAvailable() > 0 &&
         this->state != SerialState::DATA_RECIEVED) {
    // get the neext character in the serial buffer
    c = this->getChar();
    // only execute this if the startMarker has been received
    // if the incoming character is the endMarker clean up and set the flags
    if (this->state == SerialState::RECIEVE_IN_PROGRESS) {
      if (c == endMarker) {
        data[ndx] = '\0'; // terminate the string
        ndx = 0;
        this->state = SerialState::DATA_RECIEVED;
      }
      // if the incoming character is not the endMarker
      else {
        // add it to the data array
        data[ndx] = c;
        ndx++; // increment the data array index
        // if the index is greater than the maximum data array size,
        // keep overwriting the last element until the endMarker is received.
        if (ndx >= SERIAL_BUFFER_SIZE) {
          ndx = SERIAL_BUFFER_SIZE - 1;
        }
      }
    }
    // if the incoming character is the startMarker, set the recvInProgress flag
    else if (c == startMarker) {
      this->state = SerialState::RECIEVE_IN_PROGRESS;
    }
  }
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void Message<SERIAL_BUFFER_SIZE, MAX_ARGS,
             MAX_CALLBACKS>::parseData() { // split the data into its parts
  this->populatedArgs = 0;                 // reset the populated args counter
  char *indx; // this is used by strtok() as an index
  int i = 0;
  indx = strtok(temp_data, ","); // get the first part - the string
  while (indx != nullptr) {
    this->args[i] = atoi(indx);
    populatedArgs++;
    i++;
    indx =
        strtok(nullptr, ","); // this continues where the previous call left off
  }
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::Update() {
  readSerial();
  if (this->state == SerialState::DATA_RECIEVED) {
    strcpy(temp_data, data);
    // this temporary copy is necessary to protect the original data
    //   because strtok() used in parseData() replaces the commas with \0
    parseData();
    this->state = SerialState::NEW_DATA;
    callCallback();
  }
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
bool Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::IsNewData() {
  return this->state == SerialState::NEW_DATA;
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::ClearNewData() {
  this->state = SerialState::IDLE;
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
int32_t *Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::GetArgs() {
  return args;
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
uint32_t Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::GetMaxArgs() {
  return MAX_ARGS;
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
uint32_t
Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::GetPopulatedArgs() {
  return populatedArgs;
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
bool Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::RegisterCallback(
    const message_intf::Callback &callback) {
  if (numRegisteredCallbacks < MAX_CALLBACKS) {
    callbacks[numRegisteredCallbacks] = callback;
    numRegisteredCallbacks++;
    return true;
  } else {
    return false;
  }
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::callCallback() {
  for (uint32_t i = 0; i < numRegisteredCallbacks; i++) {
    if (callbacks[i].messageID ==
        this->args[0]) { // the first arg is the message ID
      bool dataProcessed =
          callbacks[i].function(reinterpret_cast<uint32_t *>(this->args.data()),
                                this->GetPopulatedArgs());
      if (dataProcessed) {
        // If the callback function returns true, we can clear the new data flag
        this->ClearNewData();
      }
    }
  }
}