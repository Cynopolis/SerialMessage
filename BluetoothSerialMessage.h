#pragma once
#include "SerialMessage.h"
#include <BluetoothSerial.h>

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
class BluetoothSerialMessage : public SerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>{
    public:
        /**
         * @brief Construct a new Bluetooth Serial Message object
         */
        BluetoothSerialMessage(BluetoothSerial *serial);
        
        void Init(uint32_t baudRate) override{this->Init();}
        /**
         * @brief Initialize the BluetoothSerialMessage object
         */
        void Init();

        /**
         * @brief prints the args array to the serial monitor
        */
        void PrintArgs() override;
    
    private:
        /**
         * @brief reads the serial data and stores it in the data array
        */
        char getChar() override;
        uint32_t dataAvailable() override;

        BluetoothSerial *serial;
};

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
char BluetoothSerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::getChar(){
    return serial->read();
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
uint32_t BluetoothSerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::dataAvailable(){
    return serial->available();
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
BluetoothSerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::BluetoothSerialMessage(BluetoothSerial *serial){
    this->serial = serial;
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
void BluetoothSerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::Init(){
    serial->begin("MiniBot");
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
void BluetoothSerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::PrintArgs(){
    serial->print("Current number of args: ");
    serial->println(this->populatedArgs);
    for (int i = 0; i < this->populatedArgs; i++) {
        serial->print(this->args[i]);
        serial->print(" ");
    }
    serial->println();
}