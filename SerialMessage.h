/**
 * @file SerialMessage.h
 * @brief This file contains the SerialMessage class
 * @details This file contains the SerialMessage class which is used to parse serial messages
 * @version 1.0.0
 * @author Quinn Henthorne. Contact: quinn.henthorne@gmail.com
*/

#pragma once

#include <Arduino.h>

#include "Message.h"

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
class SerialMessage : public Message<SERIAL_BUFFER_SIZE, MAX_ARGS>{
    public:
        /**
         * @brief Construct a new Serial Message object
         */
        SerialMessage(HardwareSerial *serial);

        /**
         * @brief Initialize the SerialMessage object
         */
        void Init(uint32_t baudRate) override;

        /**
         * @brief Prints the args array to the serial monitor
         */
        void PrintArgs() override;

    protected:
        /**
         * @brief reads the serial data and stores it in the data array
         * @return the next character in the serial buffer
        */
        char getChar() override;

        /**
         * @brief returns the number of bytes available in the serial buffer
         * @return the number of bytes available in the serial buffer
         */
        uint32_t dataAvailable() override;
    
    private:
        HardwareSerial *serial{nullptr};
};

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
char SerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::getChar(){
    return this->serial->read();
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
uint32_t SerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::dataAvailable(){
    return this->serial->available();
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
SerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::SerialMessage(HardwareSerial *serial) :
    serial(serial){}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
void SerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::Init(uint32_t baudRate){
    this->serial->begin(baudRate);
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS>
void SerialMessage<SERIAL_BUFFER_SIZE, MAX_ARGS>::PrintArgs(){
    return;
    this->serial->print("Current number of args: ");
    this->serial->println(this->populatedArgs);
    for (int i = 0; i < this->populatedArgs; i++) {
        this->serial->print(this->args[i]);
        this->serial->print(" ");
    }
    this->serial->println();
}