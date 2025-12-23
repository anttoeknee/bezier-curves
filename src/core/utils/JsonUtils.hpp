#pragma once

#include <vector>
#include <nlohmann/json.hpp>
#include "../../ui/common/Point.hpp"
#include "../../ui/common/Segment.hpp"
#include "../../ui/common/Path.hpp"

namespace core::utils {
    using json = nlohmann::json;

    ui::common::Point parsePoint(const json& j);
    ui::common::Segment parseSegment(const json& j);
    ui::common::Path parsePath(const json& j);
    std::vector<ui::common::Point> parsePointArray(const json& j);
}
