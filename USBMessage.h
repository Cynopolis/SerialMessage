#pragma once
#include "SerialMessage.h"
#include <Arduino.h>

template <uint16_t byteSize>
class USBMessage : public SerialMessage<byteSize>{
    public:
        /**
         * @brief Construct a new Bluetooth Serial Message object
         */
        USBMessage(USBCDC *serial);
        void Init(uint32_t baudRate = 115200) override;
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

template <uint16_t byteSize>
char USBMessage<byteSize>::getChar(){
    return serial->read();
}

template <uint16_t byteSize>
uint32_t USBMessage<byteSize>::dataAvailable(){
    return serial->available();
}

template <uint16_t byteSize>
USBMessage<byteSize>::USBMessage(USBCDC *serial) : serial(serial){}

template <uint16_t byteSize>
void USBMessage<byteSize>::Init(uint32_t baudRate){
    serial->begin();
}

template <uint16_t byteSize>
void USBMessage<byteSize>::PrintArgs(){
    serial->print("Current number of args: ");
    serial->println(this->populatedArgs);
    for (int i = 0; i < this->populatedArgs; i++) {
        serial->print(this->args[i]);
        serial->print(" ");
    }
    serial->println();
}