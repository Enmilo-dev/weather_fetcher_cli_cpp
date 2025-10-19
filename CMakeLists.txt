cmake_minimum_required(VERSION 3.30)

# Add vcpkg toolchain BEFORE project()
set(CMAKE_TOOLCHAIN_FILE "C:/Users/Raihan/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "x64-mingw-dynamic")

project(WeatherCLI)

set(CMAKE_CXX_STANDARD 20)

# Find CURL package
find_package(CURL REQUIRED)

# Find nlohmann_json package
find_package(nlohmann_json CONFIG REQUIRED)

# Add your source files
add_executable(WeatherCLI
        main.cpp
        src/HttpClient.cpp
        src/Utils.cpp
        src/WeatherService.cpp
        src/cliUi.cpp
)

# Include directory for headers
target_include_directories(WeatherCLI PRIVATE include)

# Link CURL and JSON libraries
target_link_libraries(WeatherCLI PRIVATE
        CURL::libcurl
        nlohmann_json::nlohmann_json
)