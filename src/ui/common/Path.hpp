#pragma once
#include <vector>
#include "Segment.hpp"

namespace ui::common {
    struct Path {
        std::string name;
        std::vector<Segment> segments;
    };
};
