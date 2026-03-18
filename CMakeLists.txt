cmake_minimum_required(VERSION 3.16)

# Detect if we're inside ESP-IDF
if(COMMAND idf_component_register)

    # =========================
    # ESP-IDF BUILD
    # =========================
    # Do NOTHING here.
    # ESP-IDF handles everything.
    
else()

    # =========================
    # DESKTOP BUILD
    # =========================

    project(SerialMessage)

    set(CMAKE_CXX_STANDARD 11)

    add_compile_options(-Wall -Wextra -Wpedantic)
    add_compile_options(-fdiagnostics-color=always)
    set(CMAKE_COLOR_DIAGNOSTICS ON)

    add_subdirectory(src)
    add_subdirectory(unit-test)

endif()