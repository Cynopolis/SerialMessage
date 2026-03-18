if(COMMAND idf_component_register)
    # =========================
    # ESP-IDF BUILD
    # =========================

    file(GLOB_RECURSE SRCS "*.cpp")

    idf_component_register(
        SRCS ${SRCS}
        INCLUDE_DIRS .
    )

else()
    # =========================
    # DESKTOP BUILD
    # =========================

    add_subdirectory(hardware-drivers)

    # Message Interface
    add_library(message-intf INTERFACE)

    target_include_directories(message-intf
        INTERFACE
        .
    )

    # message
    add_library(message STATIC message.cpp)

    target_link_libraries(message
        PUBLIC
        message-intf
    )

    set_target_properties(message
        PROPERTIES
        LINKER_LANGUAGE CXX
    )

endif()