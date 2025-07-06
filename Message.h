/**
 * @file Message.h
 * @brief This file contains the Message base class which is can be inherited to 
 * parse serial messages over any type of protocol
 * @version 1.0.0
 * @author Quinn Henthorne. Contact: quinn.henthorne@gmail.com
*/

#pragma once

#include <cstdint>

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS, uint32_t MAX_CALLBACKS>
class Message{
    public:
        /**
         * @brief Callback function type that can be registered to handle new data. 
         * Return true if you're done processing the command. 
         * If you don't return true you have to manually tell the Message class that you're done.
         */
        using CallbackFunction = bool (*)(const uint32_t *data, uint32_t length);

        /**
         * @brief A structure to hold a callback function and the message it is registered for
         */
        struct Callback {
            uint32_t messageID; // the message that this callback is registered for
            CallbackFunction function; // the function to call when this message is received
        };

        /**
         * @brief Initialize the Message object
         */
        virtual void Init(uint32_t baudRate);

        /**
         * @brief Prints the args array to the serial monitor
         */
        virtual void PrintArgs() = 0;

        /**
         * @brief Update the Message object and parse any data that's available
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
        void ClearNewData();

        /**
         * @brief Return a pointer to the args array
         * @return a pointer to the args array
         */
        int32_t * GetArgs();

        /**
         * @brief Returns the number of args that have been populated for the current message
         * @return the number of args that have been populated for the current message
         */
        uint32_t GetMaxArgs();

        /**
         * @brief Returns the number of args that have been populated for the current message
         * @return the number of args that have been populated for the current message
         */
        uint32_t GetPopulatedArgs();

        /**
         * @brief Register a callback function to be called when new data is received
         */
        void RegisterCallback(const Callback &callback);

    protected:
        enum SerialState : uint8_t{
            IDLE,
            NEW_DATA,
            DATA_RECIEVED,
            RECIEVE_IN_PROGRESS
        };
        Message() = default;
        /**
         * @brief reads the serial data and stores it in the data array
         * @return the next character in the serial buffer
        */
        virtual char getChar() = 0;

        /**
         * @brief returns the number of bytes available in the serial buffer
         * @return the number of bytes available in the serial buffer
         */
        virtual uint32_t dataAvailable() = 0;

        /**
         * @brief Takes in any available serial data and reads it into the buffer if our start character is hit. 
         * Also marks what state the Message object is in
         */
        void readSerial();

        /**
         * @brief Parses the received data and populates the args array
         */
        void parseData();

        /**
         * @brief Call a registered callback function with the received data
         */
        void callCallback();

        SerialState state{IDLE};
        char data[SERIAL_BUFFER_SIZE]; // an array to store the received data
        char temp_data[SERIAL_BUFFER_SIZE]; // an array that will be used with strtok()
        uint32_t ndx{0};
        uint32_t populatedArgs{0}; // the number of args that have been populated for the current message
        std::array<int32_t, MAX_ARGS> args;
        const char startMarker = '!';
        const char endMarker = ';';

        std::array<Callback, MAX_CALLBACKS> callbacks; // array of callbacks to be called when new data is received
        uint32_t numRegisteredCallbacks{0}; // the number of registered callbacks
};

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS, uint32_t MAX_CALLBACKS>
void Init(uint32_t baudRate){
    Serial.println("You called Message::Init! This should NEVER happen!");
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS, uint32_t MAX_CALLBACKS>
void Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::readSerial(){
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

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS, uint32_t MAX_CALLBACKS>
void Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::parseData() {      // split the data into its parts
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

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS, uint32_t MAX_CALLBACKS>
void Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::Update(){
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

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS, uint32_t MAX_CALLBACKS>
bool Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::IsNewData(){
    return this->state == SerialState::NEW_DATA;
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS, uint32_t MAX_CALLBACKS>
void Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::ClearNewData(){
    this->state = SerialState::IDLE;
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS, uint32_t MAX_CALLBACKS>
int32_t * Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::GetArgs(){
    return args;
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS, uint32_t MAX_CALLBACKS>
uint32_t Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::GetMaxArgs(){
    return MAX_ARGS;
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS, uint32_t MAX_CALLBACKS>
uint32_t Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::GetPopulatedArgs(){
    return populatedArgs;
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS, uint32_t MAX_CALLBACKS>
void Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::RegisterCallback(const Callback &callback){
    if (numRegisteredCallbacks < MAX_CALLBACKS) {
        callbacks[numRegisteredCallbacks] = callback;
        numRegisteredCallbacks++;
    } else {
        // Handle the case where the maximum number of callbacks has been reached
        Serial.println("Maximum number of callbacks reached. Cannot register new callback.");
    }
}

template <uint32_t SERIAL_BUFFER_SIZE, uint32_t MAX_ARGS, uint32_t MAX_CALLBACKS>
void Message<SERIAL_BUFFER_SIZE, MAX_ARGS, MAX_CALLBACKS>::callCallback() {
    for (uint32_t i = 0; i < numRegisteredCallbacks; i++) {
        if (callbacks[i].messageID == this->args[0]) { // the first arg is the message ID
            bool dataProcessed = callbacks[i].function(reinterpret_cast<uint32_t *>(this->args.data()), this->GetPopulatedArgs());
            if (dataProcessed) {
                // If the callback function returns true, we can clear the new data flag
                this->ClearNewData();
            }
        }
    }
}