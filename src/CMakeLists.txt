cmake_minimum_required(VERSION 3.21)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_sources(redirect PUBLIC
    redirect.cpp
    overlay.cpp
)

if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
    target_sources(redirect PRIVATE
        decoder_amd.cpp
    )
endif()