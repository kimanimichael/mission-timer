if(PLATFORM STREQUAL "mbed-os")
    add_library(src INTERFACE)

    target_include_directories(src INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/./
            ${CMAKE_CURRENT_SOURCE_DIR}/../services
    )
    target_sources(src INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/../services/timebomb.cpp
    )
else ()
    idf_component_register(
            SRCS
            "main.cpp"
            "../services/timebomb.cpp"
            INCLUDE_DIRS
            "../services/"
            REQUIRES
            mk-hsm
            drivers
    )
endif ()
