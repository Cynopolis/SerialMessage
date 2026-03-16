# Message Interface
add_library(telnet-message-intf
    INTERFACE
)

target_include_directories(telnet-message-intf
    INTERFACE
    .
)

target_link_libraries(telnet-message-intf
    INTERFACE
)

# telnet-message
add_library(telnet-message 
    STATIC
    telnet-message.cpp
)

target_link_libraries(telnet-message 
    PUBLIC
    message-intf
    PRIVATE
    arduino-fake-intf
)

set_target_properties(telnet-message
    PROPERTIES
    LINKER_LANGUAGE CXX
)