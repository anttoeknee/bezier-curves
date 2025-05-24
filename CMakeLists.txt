cmake_minimum_required(VERSION 3.28)
project(BezierCurves LANGUAGES CXX OBJCXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

# SFML setup (this overrides any system installation)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Create the executable
add_executable(main src/main.cpp src/App.cpp
        includes/utils/Mem.h
        includes/utils/Config.h
        src/utils/Config.mm
)

# Add platform-specific source
if(APPLE)
    target_sources(main PRIVATE src/utils/Mem.mm)
elseif(WIN32)
    target_sources(main PRIVATE src/utils/Mem.cpp)
endif()

# Use C++17 and link SFML
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)



