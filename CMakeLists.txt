cmake_minimum_required(VERSION 3.28)

if (APPLE)
    project(BezierCurves LANGUAGES OBJCXX CXX C)
elseif (WIN32)
    project(BezierCurves LANGUAGES CXX)
endif ()


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


FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3  # Use the latest stable version
)

FetchContent_MakeAvailable(nlohmann_json)

# Create the executable
add_executable(
        main
        src/main.cpp
        src/App.cpp
        src/core/utils/Mem.hpp
        src/core/utils/Config.hpp
        src/core/utils/Json.hpp
        src/core/utils/Json.cpp
        src/ui/elements/Element.hpp
        src/ui/elements/QuadraticBezier.cpp
        src/core/math/Geometry.hpp
        src/core/math/Geometry.cpp
        src/ui/elements/QuadraticBezier.hpp
        src/ui/elements/Metrics.hpp
        src/ui/elements/Metrics.cpp
        src/ui/regions/Region.hpp
        src/ui/regions/Canvas.cpp
        src/ui/regions/Canvas.hpp
        src/ui/elements/Divider.hpp
        src/ui/elements/Divider.cpp
        src/ui/regions/Debug.hpp
        src/ui/regions/Debug.cpp
        src/ui/utils/ScopedWindowClipping.hpp
        src/ui/elements/LerpBezier.hpp
        src/ui/elements/LerpBezier.cpp
        src/ui/common/Point.hpp
        src/ui/regions/Region.cpp
        src/core/utils/AssetManager.hpp
        src/core/utils/AssetManager.cpp
        src/ui/elements/Logo.hpp
        src/ui/elements/Logo.cpp
        src/ui/common/Segment.hpp
        src/ui/common/Path.hpp
        src/ui/elements/LineTool.hpp
        src/ui/elements/LineTool.cpp
        src/ui/rendering/Bezier.hpp
        src/ui/rendering/Bezier.cpp
        src/ui/common/ControlPoint.hpp
        src/core/events/EventBus.hpp
        src/core/events/IEvent.hpp
        src/ui/events/MousePressedEvent.hpp
        src/core/common/MouseButton.hpp
        src/core/common/Vector2f.hpp
        src/core/mappers/SFMLMapper.hpp
        src/core/mappers/SFMLMapper.cpp
        src/ui/listeners/MouseClickRegionMatcherListener.hpp
        src/ui/listeners/MouseClickRegionMatcherListener.cpp
        src/ui/common/RegionNamesEnum.hpp
        src/core/listeners/IListener.hpp

)

# Fonts
if(WIN32)
    # Windows: Use objcopy from MinGW or create a custom command with xxd/PowerShell
    find_program(OBJCOPY objcopy)
    if(OBJCOPY)
        add_custom_command(
                OUTPUT ${CMAKE_BINARY_DIR}/segoeui_font.o
                COMMAND ${OBJCOPY} -I binary -O elf64-x86-64 -B i386:x86-64
                --rename-section .data=.rodata,alloc,load,readonly,data,contents
                segoeui.ttf ${CMAKE_BINARY_DIR}/segoeui_font.o
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/assets/fonts
                DEPENDS ${CMAKE_SOURCE_DIR}/assets/fonts/segoeui.ttf
                COMMENT "Embedding segoeui.ttf as object file"
        )
        set(FONT_OBJECT ${CMAKE_BINARY_DIR}/segoeui_font.o)
    endif()
elseif(APPLE)
    # MacOS: Embed the font file using ld (this is horrible, but works)
    add_custom_command(
            OUTPUT ${CMAKE_BINARY_DIR}/segoeui_font.o
            COMMAND printf ".section __DATA,__segoeui_ttf\\\\n.globl __binary_segoeui_ttf_start\\\\n__binary_segoeui_ttf_start:\\\\n.incbin \\\\\\\"${CMAKE_SOURCE_DIR}/assets/fonts/segoeui.ttf\\\\\\\"\\\\n.globl __binary_segoeui_ttf_end\\\\n__binary_segoeui_ttf_end:\\\\n" > ${CMAKE_BINARY_DIR}/segoeui_font.s
            COMMAND as -arch arm64 -o ${CMAKE_BINARY_DIR}/segoeui_font.o ${CMAKE_BINARY_DIR}/segoeui_font.s
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            DEPENDS ${CMAKE_SOURCE_DIR}/assets/fonts/segoeui.ttf
            COMMENT "Embedding segoeui.ttf as object file using ld"
    )
    set(FONT_OBJECT ${CMAKE_BINARY_DIR}/segoeui_font.o)
endif()

# Add the embedded font to your target if available
if(FONT_OBJECT)
    target_sources(main PRIVATE ${FONT_OBJECT})
endif()

# Move config.json to the binary directory
add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.json
        $<TARGET_FILE_DIR:main>/config.json)

# Move points.json to the binary directory
add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/points.json
        $<TARGET_FILE_DIR:main>/points.json)

# Add platform-specific source
if (APPLE)
    target_sources(main PRIVATE src/core/utils/Mem.mm)
    target_sources(main PRIVATE src/core/utils/Config.mm)
elseif (WIN32)
    target_sources(main PRIVATE src/core/utils/Mem.cpp src/core/utils/Config.cpp)
endif ()

# Use C++20 and link SFML + TGUI
target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main PRIVATE sfml-graphics nlohmann_json::nlohmann_json)



