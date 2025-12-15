#include "Logo.hpp"

#include "SFML/Graphics/RectangleShape.hpp"
#include "../../core/math/Geometry.hpp"

ui::elements::Logo::Logo(
    common::Path &&path_
) : path(std::move(path_)) {
}

void ui::elements::Logo::draw(sf::RenderWindow &target, sf::Vector2f origin) {
    // iterate path segments
    for (auto &segment: path.segments) {
        if (segment.type == common::SegmentType::LINE) {
            std::vector<sf::RectangleShape> shapes;
            for (auto &point: segment.points) {
                sf::RectangleShape rect(sf::Vector2f(point.size.x, point.size.y));
                rect.setPosition({point.position.x, point.position.y});
                rect.setFillColor(sf::Color::White);

                // point draw
                target.draw(*std::make_unique<sf::RectangleShape>(rect));
                shapes.push_back(rect);
            }

            // initialise an empty vertex and then iterate the shapes object to fill the vertex
            std::vector<sf::Vertex> line;
            for (size_t i = 0; i < shapes.size() - 1; i++) {
                line.push_back(sf::Vertex({shapes[i].getPosition(), sf::Color::White}));
                line.push_back(sf::Vertex({shapes[i + 1].getPosition(), sf::Color::White}));
            }

            target.draw(&line[0], 2, sf::PrimitiveType::Lines);
        }

        // TODO: I'm going to come back to this once I've figured out chained cubic bezier's with
        //  control point candidates computed at the right places per curve segment, then I can
        //  apply it here
        if (segment.type == common::SegmentType::CURVE) {

            sf::Vector2f midPos = (segment.points[0].position + segment.points[1].position) * 0.5f;
            common::Point midPoint = {"mid point", midPos, segment.points[0].size * 0.5f};

            // calculate outbound and inbound control point candidates
            common::Point mpCandidate1 = {
                "cp candidate 1",
                {
                    midPoint.position.x / (10.f/9.f),
                    midPoint.position.y / (10.f/9.f),
                },
                {10, 10}
            };

            common::Point mpCandidate2 = {
                "cp candidate 2",
                {
                    midPoint.position.x * 1.1f,
                    midPoint.position.y * 1.1f
                },
                {10, 10}
            };

            std::vector midPointCtrlPointCandidates = { mpCandidate1, mpCandidate2 };


            std::vector points = {segment.points[0], midPoint, segment.points[1]};

            // Draw points
            std::vector<sf::RectangleShape> shapes;
            for (auto &point: points) {
                sf::RectangleShape rect(sf::Vector2f(point.size.x, point.size.y));
                rect.setPosition({point.position.x, point.position.y});
                rect.setFillColor(sf::Color::White);
                target.draw(*std::make_unique<sf::RectangleShape>(rect));
                shapes.push_back(rect);
            }

            // Draw control point candidates
            std::vector<sf::RectangleShape> midPointShapes;
            for (auto &cpCandidate: midPointCtrlPointCandidates) {
                sf::RectangleShape rect(sf::Vector2f(cpCandidate.size.x, cpCandidate.size.y));
                rect.setPosition({cpCandidate.position.x, cpCandidate.position.y});
                rect.setFillColor(sf::Color::Cyan);
                target.draw(*std::make_unique<sf::RectangleShape>(rect));
                midPointShapes.push_back(rect);
            }

            // Draw connecting line between control point candidates and mid point
            std::vector<sf::Vertex> ctrlPointLines;
            for (auto &cpCandidate: midPointShapes) {
                ctrlPointLines.push_back(sf::Vertex({midPointShapes[0].getPosition(), sf::Color::Cyan}));
                ctrlPointLines.push_back(sf::Vertex({cpCandidate.getPosition(), sf::Color::Cyan}));
            }

            // Draw quadratic curve...
            std::vector<sf::Vertex> bezierLine;
            for (float t = 0; t <= 1.0f; t += 0.01f) {

                // create the vector for each segment
                sf::Vector2f segmentVector = core::math::quadraticBezier(
                    shapes[0].getPosition(),
                    midPointShapes[0].getPosition(),
                    shapes[2].getPosition(),
                    t
                );

                // push segments into another vector for drawing
                bezierLine.push_back(sf::Vertex({segmentVector, sf::Color::White}));
            }

            // draw the bezier line and control point lines
            target.draw(&bezierLine[0], bezierLine.size(), sf::PrimitiveType::LineStrip);
            //target.draw(&ctrlPointLines[0]);
        }
    }
}

void ui::elements::Logo::update(sf::RenderWindow &target, sf::Vector2f origin) {
}

void ui::elements::Logo::handleMouseMove(sf::Vector2f &mousePos) {
}

void ui::elements::Logo::handleMouseButtonPressed(sf::Vector2f &mousePos) {
}

void ui::elements::Logo::handleMouseButtonReleased() {
}
