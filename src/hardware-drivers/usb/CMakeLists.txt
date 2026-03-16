# Message Interface
add_library(usb-message-intf
    INTERFACE
)

target_include_directories(usb-message-intf
    INTERFACE
    .
)

target_link_libraries(usb-message-intf
    INTERFACE
)

# usb-message
add_library(usb-message 
    STATIC
    usb-message.cpp
)

target_link_libraries(usb-message 
    PUBLIC
    message-intf
    PRIVATE
    arduino-fake-intf
)

set_target_properties(usb-message
    PROPERTIES
    LINKER_LANGUAGE CXX
)