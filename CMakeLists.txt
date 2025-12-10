cmake_minimum_required(VERSION 3.16)
project(MidiController)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets DBus)
find_package(PkgConfig REQUIRED)
pkg_check_modules(PULSE REQUIRED libpulse)

# --- RtMidi detection ---
find_path(RTMIDI_INCLUDE_DIR
    NAMES RtMidi.h
    PATH_SUFFIXES rtmidi include/rtmidi
    PATHS /usr/include /usr/local/include /usr/include/rtmidi
)

find_library(RTMIDI_LIBRARY
    NAMES rtmidi librtmidi.so librtmidi.so.6
    PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64
)

if(NOT RTMIDI_INCLUDE_DIR)
    message(FATAL_ERROR "RtMidi headers not found. Install rtmidi-devel or provide -DRTMIDI_INCLUDE_DIR=/path/to/include")
endif()

if(NOT RTMIDI_LIBRARY)
    message(FATAL_ERROR "RtMidi library not found. Install rtmidi or provide -DRTMIDI_LIBRARY=/path/to/librtmidi.so")
endif()

include_directories(
    ${RTMIDI_INCLUDE_DIR}
    ${PULSE_INCLUDE_DIRS}
)

add_executable(MidiController
    main.cpp
    MidiHandler.cpp MidiHandler.h
    AudioHandler.cpp AudioHandler.h
    Overlay.cpp Overlay.h
    WindowUtils.cpp WindowUtils.h
    ButtonHandler.cpp ButtonHandler.h
)

target_link_libraries(MidiController
    Qt6::Core
    Qt6::Widgets
    Qt6::DBus
    ${RTMIDI_LIBRARY}
    ${PULSE_LIBRARIES}
    pthread
)
