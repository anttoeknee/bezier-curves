#include "Json.hpp"
#include "SFML/System/Vector2.hpp"

namespace core::utils::json {
    ui::common::Point parsePoint(const json& j) {
        return {
            j["name"].get<std::string>(),
            sf::Vector2f{j["position"]["x"].get<float>(), j["position"]["y"].get<float>()},
            sf::Vector2f{j["size"]["x"].get<float>(), j["size"]["y"].get<float>()}
        };
    }

    ui::common::Segment parseSegment(const json& j) {
        ui::common::SegmentType type = j["type"] == "LINE" ? ui::common::SegmentType::LINE : ui::common::SegmentType::CURVE;
        std::vector<ui::common::Point> points;
        for (const auto& pointJson : j["points"]) {
            points.push_back(parsePoint(pointJson));
        }
        return {type, points};
    }

    ui::common::Path parsePath(const json& j) {
        ui::common::Path path{j["name"].get<std::string>()};
        for (const auto& segmentJson : j["segments"]) {
            path.segments.push_back(parseSegment(segmentJson));
        }
        return path;
    }

    std::vector<ui::common::Point> parsePointArray(const json& j) {
        std::vector<ui::common::Point> points;
        for (const auto& pointJson : j) {
            points.push_back(parsePoint(pointJson));
        }
        return points;
    }
}
