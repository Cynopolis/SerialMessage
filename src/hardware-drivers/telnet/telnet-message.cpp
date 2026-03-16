#ifndef TELNET_MESSAGE_H_
#define TELNET_MESSAGE_H_
#include "telnet-message.h"
#endif

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS,
                   MAX_CALLBACKS>::onConnectCallback(std::string ip) {
  //   GlobalPrint::Print("- Telnet: ");
  //   GlobalPrint::Print(ip);
  //   GlobalPrint::Println(" connected");
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS,
                   MAX_CALLBACKS>::onConnectionAttemptCallback(std::string ip) {
  //   GlobalPrint::Print("- Telnet: ");
  //   GlobalPrint::Print(ip);
  //   GlobalPrint::Println(" failed to connect");
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS,
                   MAX_CALLBACKS>::onReconnectCallback(std::string ip) {
  //   GlobalPrint::Print("- Telnet: ");
  //   GlobalPrint::Print(ip);
  //   GlobalPrint::Println(" reconnected");
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS,
                   MAX_CALLBACKS>::onDisconnectCallback(std::string ip) {
  //   GlobalPrint::Print("- Telnet: ");
  //   GlobalPrint::Print(ip);
  //   GlobalPrint::Println(" disconnected");
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::
    SetOnInputRecieved(void (*callback)(std::string data)) {
  this->telnet->onInputReceived(callback);
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
char TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::getChar() {
  // Stop us from reading any more data if there's nothing more to read
  if (this->incomingData == nullptr || this->incomingDataLength == 0) {
    return this->endMarker;
  }

  char output = this->incomingData[this->incomingDataCharIndex];
  this->incomingDataCharIndex++;
  // GlobalPrint::Println("Char Idx:" + std::string(this->incomingDataCharIndex)
  // + ", Data Length:" + std::string(this->incomingDataLength) + ", Char:" +
  // output);
  return output;
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::SetString(
    const char *data) {
  this->incomingDataLength = strlen(data);
  this->incomingDataCharIndex = 0;
  this->incomingData = data;
  this->Update();
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
uint32_t
TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::dataAvailable() {
  if (this->incomingData == nullptr) {
    return 0;
  }
  return this->incomingDataLength - this->incomingDataCharIndex;
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::Init(
    void (*callback)(std::string data)) {
  telnet->begin(23);
  // set all of our callbacks
  telnet->onConnect(TelnetMessage::onConnectCallback);
  telnet->onConnectionAttempt(TelnetMessage::onConnectionAttemptCallback);
  telnet->onReconnect(TelnetMessage::onReconnectCallback);
  telnet->onDisconnect(TelnetMessage::onDisconnectCallback);

  this->SetOnInputRecieved(callback);
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS,
          uint32_t MAX_CALLBACKS>
void TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::PrintArgs() {
  telnet->print("Current number of args: ");
  telnet->println(this->populatedArgs);
  for (int i = 0; i < this->populatedArgs; i++) {
    telnet->print(this->args[i]);
    telnet->print(" ");
  }
  telnet->println();
}
