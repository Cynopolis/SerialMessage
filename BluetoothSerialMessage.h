#pragma once
#include "SerialMessage.h"
#include <BluetoothSerial.h>

template <uint16_t byteSize>
class BluetoothSerialMessage : public SerialMessage<byteSize>{
    public:
        /**
         * @brief Construct a new Bluetooth Serial Message object
         */
        BluetoothSerialMessage(BluetoothSerial *serial);

        /**
         * @brief Initialize the BluetoothSerialMessage object
         */
        void Init(uint32_t baudRate = 115200) override;

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

template <uint16_t byteSize>
char BluetoothSerialMessage<byteSize>::getChar(){
    return serial->read();
}

template <uint16_t byteSize>
uint32_t BluetoothSerialMessage<byteSize>::dataAvailable(){
    return serial->available();
}

template <uint16_t byteSize>
BluetoothSerialMessage<byteSize>::BluetoothSerialMessage(BluetoothSerial *serial){
    this->serial = serial;
}

template <uint16_t byteSize>
void BluetoothSerialMessage<byteSize>::Init(uint32_t baudRate){
    serial->begin("MiniBot");
}

template <uint16_t byteSize>
void BluetoothSerialMessage<byteSize>::PrintArgs(){
    serial->print("Current number of args: ");
    serial->println(this->populatedArgs);
    for (int i = 0; i < this->populatedArgs; i++) {
        serial->print(this->args[i]);
        serial->print(" ");
    }
    serial->println();
}