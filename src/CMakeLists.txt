add_subdirectory(bluetooth)
add_subdirectory(serial)
add_subdirectory(telnet)
add_subdirectory(usb)

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