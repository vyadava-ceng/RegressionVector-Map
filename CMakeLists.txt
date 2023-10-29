cmake_minimum_required(VERSION 3.5)
project(img_stitcher)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

# Specify the paths to the Paho MQTT C and C++ libraries
set(PAHO_MQTT_C_DIR $ENV{HOME}/paho-mqtt/paho.mqtt.c/build/install)      
set(PAHO_MQTT_CPP_DIR $ENV{HOME}/paho-mqtt/paho.mqtt.cpp/build/install)

find_package (Threads)
find_package(PkgConfig REQUIRED)
find_package(OpenCV 4.6 REQUIRED PATHS $ENV{HOME}/opencv_ws/install)

pkg_check_modules(GSTLIBS REQUIRED
        gobject-2.0
        glib-2.0
        gstreamer-webrtc-1.0
        gstreamer-sdp-1.0
        gstreamer-pbutils-1.0
        libsoup-2.4
        json-glib-1.0
        gstreamer-rtsp-server-1.0
        gstreamer-check-1.0)
        
pkg_check_modules(GLib REQUIRED glib-2.0)

find_package(PkgConfig REQUIRED)
pkg_check_modules(gtk3 REQUIRED IMPORTED_TARGET gtk+-3.0)
pkg_search_module(gstreamer REQUIRED IMPORTED_TARGET gstreamer-1.0>=1.4)
pkg_search_module(gstreamer-sdp REQUIRED IMPORTED_TARGET gstreamer-sdp-1.0>=1.4)
pkg_search_module(gstreamer-app REQUIRED IMPORTED_TARGET gstreamer-app-1.0>=1.4)
pkg_search_module(gstreamer-video REQUIRED IMPORTED_TARGET gstreamer-video-1.0>=1.4)

include_directories ( ${GTK_INCLUDE_DIRS} )

include_directories(include)

# Include directories for Paho MQTT C and C++
include_directories(${PAHO_MQTT_C_DIR}/include)
include_directories(${PAHO_MQTT_CPP_DIR}/include)

file(GLOB SRCS main.cpp "src/*.cpp")

#add_library(my_lib ${SRC})
add_executable(npd-us-omniview ${SRCS})

target_link_libraries(npd-us-omniview
    PkgConfig::gtk3
    PkgConfig::gstreamer
    PkgConfig::gstreamer-sdp
    PkgConfig::gstreamer-app
    PkgConfig::gstreamer-video
    #GTest::gtest_main
    #GTest::gmock_main
)

#Target Link Libraries for OpenCV and Threading
target_link_libraries(npd-us-omniview ${OpenCV_LIBS})
target_link_libraries(npd-us-omniview Threads::Threads)
# Link against the Paho MQTT C and C++ libraries
target_link_libraries(npd-us-omniview
  ${PAHO_MQTT_C_DIR}/lib/libpaho-mqtt3as.so  
  ${PAHO_MQTT_CPP_DIR}/lib/libpaho-mqttpp3.so  
  ssl crypto
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

#add_subdirectory(src)
