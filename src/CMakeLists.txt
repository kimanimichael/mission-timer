if(PLATFORM STREQUAL "mbed-os")
    add_library(src INTERFACE)

    target_include_directories(src INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/./
    )
    target_sources(src INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    )
else ()
    idf_component_register(
            SRCS
            "main.cpp"
            "../services/timebomb.cpp"
            INCLUDE_DIRS
            "../services/"
            REQUIRES
            hsm
            drivers
    )
endif ()
