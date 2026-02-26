# Serial Message Interface
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
add_library(message 
    STATIC
    message.cpp
)

target_link_libraries(message 
    PUBLIC
    serial-message-intf
    PRIVATE
)

set_target_properties(message
    PROPERTIES
    LINKER_LANGUAGE CXX
)