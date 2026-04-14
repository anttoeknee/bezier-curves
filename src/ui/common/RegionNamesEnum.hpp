#pragma once
#include <string>

namespace ui::common {
    enum class RegionNamesEnum {
        Lerp,
        Quad,
        PenTool,
        Logo,
        Debug
    };

    inline std::string toString(RegionNamesEnum type) {
        switch (type) {
            case RegionNamesEnum::Lerp: return "Linear Interpolation";
            case RegionNamesEnum::Quad: return "Quadratic";
            case RegionNamesEnum::PenTool: return "Primitive Pen Tool";
            case RegionNamesEnum::Logo: return "Logo";
            case RegionNamesEnum::Debug: return "Debug";
            default: return "Unknown";
        }
    }
}
