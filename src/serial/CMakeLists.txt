# serial-message
add_library(serial-message 
    STATIC
    serial-message.cpp
)

target_link_libraries(serial-message 
    PUBLIC
    serial-message-intf
    PRIVATE
)

set_target_properties(serial-message
    PROPERTIES
    LINKER_LANGUAGE CXX
)