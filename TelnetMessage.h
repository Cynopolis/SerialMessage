#pragma once

#include <ESPTelnet.h>

#include "SerialMessage.h"
#include "WiFi.h"
#include "GlobalPrint.h"

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
class TelnetMessage : public Message<SERIAL_BUFFER_SIZE, MAX_ARGS>{
    public:
        /**
         * @brief Construct a new Bluetooth Serial Message object
         */
        TelnetMessage(ESPTelnet *telnet) : 
        telnet(telnet){}

        void Init(uint32_t baudRate) override{Serial.println("Never call this without a parameter, this will not function properly without a callback function");}
        /**
         * @brief Initialize the TelnetMessage object
         * @pre The WiFi object must have a state of WL_CONNECTED
         */
        void Init(void (*callback)(String data));

        /**
         * @brief prints the args array to the telnet monitor
        */
        void PrintArgs() override;

        void SetString(const char * data);    

        void SetOnInputRecieved(void (*callback)(String data));
    private:
        /**
         * @brief reads the telnet data and stores it in the data array
        */
        char getChar() override;

        /**
         * @brief returns the amount of data available
         */
        uint32_t dataAvailable() override;

        static void onConnectCallback(String ip);
        static void onConnectionAttemptCallback(String ip);
        static void onReconnectCallback(String ip);
        static void onDisconnectCallback(String ip);

        ESPTelnet *telnet;

        const char * incomingData = nullptr;
        uint32_t incomingDataLength{0};
        uint32_t incomingDataCharIndex{0};
};

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
void TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::onConnectCallback(String ip) {
  GlobalPrint::Print("- Telnet: ");
  GlobalPrint::Print(ip);
  GlobalPrint::Println(" connected");
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
void TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::onConnectionAttemptCallback(String ip) {
  GlobalPrint::Print("- Telnet: ");
  GlobalPrint::Print(ip);
  GlobalPrint::Println(" failed to connect");
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
void TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::onReconnectCallback(String ip) {
  GlobalPrint::Print("- Telnet: ");
  GlobalPrint::Print(ip);
  GlobalPrint::Println(" reconnected");
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
void TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::onDisconnectCallback(String ip) {
  GlobalPrint::Print("- Telnet: ");
  GlobalPrint::Print(ip);
  GlobalPrint::Println(" disconnected");
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
void TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::SetOnInputRecieved(void (*callback)(String data)){
    this->telnet->onInputReceived(callback);
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
char TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::getChar(){
    // Stop us from reading any more data if there's nothing more to read
    if(this->incomingData == nullptr || this->incomingDataLength == 0){
        return this->endMarker;
    }

    char output = this->incomingData[this->incomingDataCharIndex];
    this->incomingDataCharIndex++;
    // GlobalPrint::Println("Char Idx:" + String(this->incomingDataCharIndex) + ", Data Length:" + String(this->incomingDataLength) + ", Char:" + output);
    return output;
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
void TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::SetString(const char * data){
    this->incomingDataLength = strlen(data);
    this->incomingDataCharIndex = 0;
    this->incomingData = data;
    this->Update();
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
uint32_t TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::dataAvailable(){
    if(this->incomingData == nullptr){
        return 0;
    }
    return this->incomingDataLength - this->incomingDataCharIndex;
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
void TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::Init(void (*callback)(String data)){
    telnet->begin(23);
    // set all of our callbacks
    telnet->onConnect(TelnetMessage::onConnectCallback);
    telnet->onConnectionAttempt(TelnetMessage::onConnectionAttemptCallback);
    telnet->onReconnect(TelnetMessage::onReconnectCallback);
    telnet->onDisconnect(TelnetMessage::onDisconnectCallback);

    this->SetOnInputRecieved(callback);
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
void TelnetMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::PrintArgs(){
    telnet->print("Current number of args: ");
    telnet->println(this->populatedArgs);
    for (int i = 0; i < this->populatedArgs; i++) {
        telnet->print(this->args[i]);
        telnet->print(" ");
    }
    telnet->println();
}

