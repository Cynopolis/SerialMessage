# Message Interface
add_library(bluetooth-message-intf
    INTERFACE
)

target_include_directories(bluetooth-message-intf
    INTERFACE
    .
)

target_link_libraries(bluetooth-message-intf
    INTERFACE
)

# serial-message
add_library(bluetooth-message 
    STATIC
    bluetooth-message.cpp
)

target_link_libraries(bluetooth-message 
    PUBLIC
    bluetooth-message-intf
    message-intf
    PRIVATE
    arduino-fake-intf
)

set_target_properties(bluetooth-message
    PROPERTIES
    LINKER_LANGUAGE CXX
)