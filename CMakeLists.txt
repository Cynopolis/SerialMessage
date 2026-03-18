# components/SerialMessage/CMakeLists.txt

if(COMMAND idf_component_register)

    # Grab all cpp sources in src (ignore unit-test)
    file(GLOB_RECURSE SRCS "src/*.cpp")

    # Only include driver folders
    file(GLOB DRIVER_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/hardware-drivers/*")
    set(DRIVER_INCLUDE_DIRS "")
    foreach(DIR ${DRIVER_DIRS})
        if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${DIR}")
            list(APPEND DRIVER_INCLUDE_DIRS "${DIR}")
        endif()
    endforeach()

    # Explicitly add Arduino fake headers for unit testing
    set(ARDUINO_FAKE_DIR "unit-test/arduino-fake")

    # Register component
    idf_component_register(
        SRCS ${SRCS}
        INCLUDE_DIRS
            src
            src/hardware-drivers
            ${DRIVER_INCLUDE_DIRS}
            ${ARDUINO_FAKE_DIR}
    )

else()

    # =========================
    # DESKTOP BUILD
    # =========================

    add_subdirectory(src/hardware-drivers)

    # Message Interface
    add_library(message-intf INTERFACE)
    target_include_directories(message-intf INTERFACE src)

    # Message implementation
    add_library(message STATIC src/message.cpp)
    target_link_libraries(message PUBLIC message-intf)
    set_target_properties(message PROPERTIES LINKER_LANGUAGE CXX)

endif()