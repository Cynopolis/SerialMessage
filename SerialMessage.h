/**
 * @file SerialMessage.h
 * @brief This file contains the SerialMessage class
 * @details This file contains the SerialMessage class which is used to parse serial messages
 * @version 1.0.0
 * @author Quinn Henthorne. Contact: quinn.henthorne@gmail.com
*/

#ifndef SERIALMESSAGE_H
#define SERIALMESSAGE_H

#include "Arduino.h"

template <uint16_t byteSize>
class SerialMessage{
    public:
        // @warning Never use this to construct a SerialMessage object
        SerialMessage() = delete;
        /**
         * @brief Construct a new Serial Message object
         */
        SerialMessage(HardwareSerial *serial);

        /**
         * @brief Initialize the SerialMessage object
         */
        virtual void Init(unsigned int baud_rate = 115200);

        /**
         * @brief Update the SerialMessage object and parse any data that's available
         */
        void Update();

        /**
         * @brief Returns true if there is new data available
         * @return true if there is new data available
         */
        bool IsNewData();

        /**
         * @brief Clears the new data flag
         */
        virtual void ClearNewData();

        /**
         * @brief Return a pointer to the args array
         * @return a pointer to the args array
         */
        int32_t * GetArgs();

        /**
         * @brief Returns the number of args that have been populated for the current message
         * @return the number of args that have been populated for the current message
         */
        uint32_t GetArgsLength();

        /**
         * @brief Returns the number of args that have been populated for the current message
         * @return the number of args that have been populated for the current message
         */
        uint32_t GetPopulatedArgs();

        /**
         * @brief Prints the args array to the serial monitor
         */
        virtual void PrintArgs();

    protected:
        enum SerialState : uint8_t{
            IDLE,
            NEW_DATA,
            DATA_RECIEVED,
            RECIEVE_IN_PROGRESS
        };
        virtual void readSerial();
        virtual void parseData();
        /**
         * @brief reads the serial data and stores it in the data array
         * @return the next character in the serial buffer
        */
        virtual char getChar();

        /**
         * @brief returns the number of bytes available in the serial buffer
         * @return the number of bytes available in the serial buffer
         */
        virtual uint32_t dataAvailable();

        SerialState state{IDLE};
        char data[byteSize]; // an array to store the received data
        char temp_data[byteSize]; // an array that will be used with strtok()
        uint32_t ndx{0};
        static constexpr uint16_t args_length{30};
        uint32_t populatedArgs{0}; // the number of args that have been populated for the current message
        int32_t args[args_length];
        const char startMarker = '!';
        const char endMarker = ';';
    
    private:
        HardwareSerial *serial{nullptr};
};

template <uint16_t byteSize>
char SerialMessage<byteSize>::getChar(){
    return this->serial->read();
}

template <uint16_t byteSize>
uint32_t SerialMessage<byteSize>::dataAvailable(){
    return this->serial->available();
}

template <uint16_t byteSize>
SerialMessage<byteSize>::SerialMessage(HardwareSerial *serial) :
    serial(serial){}

template <uint16_t byteSize>
void SerialMessage<byteSize>::Init(unsigned int baud_rate){
    this->serial->begin(baud_rate);
}

template <uint16_t byteSize>
void SerialMessage<byteSize>::readSerial(){
    char c;

    // read the incoming serial data:
    while (this->dataAvailable() > 0 && this->state != SerialState::DATA_RECIEVED) {
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
                if (ndx >= byteSize) {
                    ndx = byteSize - 1;
                }
            }
        }
        // if the incoming character is the startMarker, set the recvInProgress flag
        else if (c == startMarker) {
            this->state = SerialState::RECIEVE_IN_PROGRESS;
        }
    }
}

template <uint16_t byteSize>
void SerialMessage<byteSize>::parseData() {      // split the data into its parts
    this->populatedArgs = 0; // reset the populated args counter
    char * indx; // this is used by strtok() as an index
    int i = 0;
    indx = strtok(temp_data, ",");      // get the first part - the string
    while(indx != NULL){
        this->args[i] = atoi(indx);
        populatedArgs++;
        i++;
        indx = strtok(NULL, ","); // this continues where the previous call left off
    }
}

template <uint16_t byteSize>
void SerialMessage<byteSize>::Update(){
    readSerial();
    if (this->state == SerialState::DATA_RECIEVED) {
        // for debug only:
        // Serial.print("Received:");
        // Serial.print(data);
        // Serial.println(":End");
        strcpy(temp_data, data);
        // this temporary copy is necessary to protect the original data
        //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        //PrintArgs();
        this->state = SerialState::NEW_DATA;
    }
}

template <uint16_t byteSize>
bool SerialMessage<byteSize>::IsNewData(){
    return this->state == SerialState::NEW_DATA;
}

template <uint16_t byteSize>
void SerialMessage<byteSize>::ClearNewData(){
    this->state = SerialState::IDLE;
}

template <uint16_t byteSize>
int32_t * SerialMessage<byteSize>::GetArgs(){
    return args;
}

template <uint16_t byteSize>
uint32_t SerialMessage<byteSize>::GetArgsLength(){
    return args_length;
}

template <uint16_t byteSize>
uint32_t SerialMessage<byteSize>::GetPopulatedArgs(){
    return populatedArgs;
}

template <uint16_t byteSize>
void SerialMessage<byteSize>::PrintArgs(){
    return;
    this->serial->print("Current number of args: ");
    this->serial->println(this->populatedArgs);
    for (int i = 0; i < populatedArgs; i++) {
        this->serial->print(args[i]);
        this->serial->print(" ");
    }
    this->serial->println();
}

#endif