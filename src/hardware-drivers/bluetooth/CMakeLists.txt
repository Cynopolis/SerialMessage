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

# # serial-message
# add_library(bluetooth-serial-message 
#     STATIC
#     serial-message.cpp
# )

# target_link_libraries(bluetooth-serial-message 
#     PUBLIC
#     message-intf
#     PRIVATE
#     arduino-fake-intf
# )

# set_target_properties(bluetooth-serial-message
#     PROPERTIES
#     LINKER_LANGUAGE CXX
# )