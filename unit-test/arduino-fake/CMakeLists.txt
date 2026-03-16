# Serial Message Interface
add_library(arduino-fake-intf
    INTERFACE
)

target_include_directories(arduino-fake-intf
    INTERFACE
    .
)

target_link_libraries(arduino-fake-intf
    INTERFACE
)