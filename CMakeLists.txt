cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(MinecraftifyCustomPanoramasAddon VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
    # Add any extra C++ source files here
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

include(cmake/CPM.cmake)

# Add curl with system-installed dependencies
CPMAddPackage("gh:curl/curl#master")
target_link_libraries(${PROJECT_NAME} CURL)

# Add zlib via CPM
CPMAddPackage("gh:madler/zlib#develop")
target_link_libraries(${PROJECT_NAME} zlib)

# Add nlohmann/json via CPM
CPMAddPackage("gh:nlohmann/json#master")
target_link_libraries(${PROJECT_NAME} nlohmann_json)

# Use system-installed Brotli, Zstd, NGHTTP2, and Libpsl
find_package(Brotli REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${BROTLI_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${BROTLI_LIBRARIES})

find_package(Zstd REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${ZSTD_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${ZSTD_LIBRARY})

find_package(NGHTTP2 REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${NGHTTP2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${NGHTTP2_LIBRARY})

find_package(Libpsl REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${LIBPSL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${LIBPSL_LIBRARY})

# Add Geode SDK
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Setup Geode Mod
setup_geode_mod(${PROJECT_NAME})