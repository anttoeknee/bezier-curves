#pragma once

#include <vector>
#include "Point.hpp"

namespace ui::common {
    enum class SegmentType {
        LINE,
        CURVE
    };

    struct Segment {
        SegmentType type;
        std::vector<Point> points;
    };
};
