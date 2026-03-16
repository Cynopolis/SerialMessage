# Message Interface
add_library(serial-message-intf
    INTERFACE
)

target_include_directories(serial-message-intf
    INTERFACE
    .
)

target_link_libraries(serial-message-intf
    INTERFACE
)

# serial-message
add_library(serial-message 
    STATIC
    serial-message.cpp
)

target_link_libraries(serial-message 
    PUBLIC
    message-intf
    PRIVATE
    arduino-fake-intf
)

set_target_properties(serial-message
    PROPERTIES
    LINKER_LANGUAGE CXX
)