cmake_minimum_required(VERSION 3.28)
project(BezierCurves LANGUAGES CXX OBJCXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

#set(SFML_BUILD_GRAPHICS ON CACHE INTERNAL "")

# SFML setup (this overrides any system installation)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)
#
#

# Set TGUI backend before fetching TGUI
#set(TGUI_BUILD_FRAMEWORK OFF CACHE BOOL "" FORCE)
#set(TGUI_BACKEND SFML_GRAPHICS CACHE STRING "" FORCE)
#
#
## Point to the correct SFML_DIR
#set(SFML_DIR "${CMAKE_BINARY_DIR}/_deps/sfml-build" CACHE PATH "" FORCE)
#
## Fetch TGUI
#FetchContent_Declare(tgui
#        GIT_REPOSITORY https://github.com/texus/TGUI.git
#        GIT_TAG v1.9.0
#        GIT_SHALLOW ON
#)
#
#FetchContent_MakeAvailable(tgui)

# Create the executable
add_executable(main src/main.cpp src/App.cpp
        src/core/utils/Mem.hpp
        src/core/utils/Config.hpp
        src/core/utils/Config.mm
        src/elements/Element.hpp
        src/elements/QuadraticBezier.cpp
        src/core/math/Geometry.hpp
        src/core/math/Geometry.cpp
        src/elements/QuadraticBezier.hpp
        src/elements/Debug.hpp
        src/elements/Debug.cpp
        src/scenes/Scene.hpp
        src/scenes/Bezier.cpp
        src/scenes/Bezier.hpp
)

# Add platform-specific source
if (APPLE)
    target_sources(main PRIVATE src/core/utils/Mem.mm)
elseif (WIN32)
    target_sources(main PRIVATE src/core/utils/Mem.cpp)
endif ()

# Use C++17 and link SFML + TGUI
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE sfml-graphics)



