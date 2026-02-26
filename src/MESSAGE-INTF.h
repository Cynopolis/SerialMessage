#pragma once
#include <cstdint>

namespace MESSAGE_INTF
{
    /**
     * @brief Callback function type that can be registered to handle new data.
     * Return true if you're done processing the command.
     * If you don't return true you have to manually tell the Message class that you're done.
     */
    using CallbackFunction = bool (*)(const uint32_t *data, uint32_t length);

    /**
     * @brief A structure to hold a callback function and the message it is registered for
     */
    struct Callback
    {
        uint32_t messageID;        // the message that this callback is registered for
        CallbackFunction function; // the function to call when this message is received
    };
}