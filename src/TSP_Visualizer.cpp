#include "TSP_Visualizer.h"
#include <thread>
using namespace std;

TSPVisualizer::TSPVisualizer(const std::vector<Point>& pts)
    : window(sf::VideoMode({800, 800}), "TSP Brute Force Visualization"), points(pts) {}

void TSPVisualizer::update_path(const std::vector<int>& path, bool isBest) {
    currentPath = path;
    showBest = isBest;
    if (isBest) bestPath = path;
    render();
    if (!isBest) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void TSPVisualizer::render() {
    window.clear(sf::Color::Black);

    for (const auto& p : points) {
        sf::CircleShape circle(5);
        circle.setFillColor(sf::Color::White);
        circle.setPosition(sf::Vector2f(static_cast<float>(p.x), static_cast<float>(p.y)));
        window.draw(circle);
    }
    const std::vector<int>& path = showBest ? bestPath : currentPath;
    sf::VertexArray lines(sf::PrimitiveType::LineStrip, path.size() + 1);
    for (size_t i = 0; i < path.size(); ++i) {
        lines[i].position = sf::Vector2f(static_cast<float>(points[path[i]].x), static_cast<float>(points[path[i]].y));
        lines[i].color = showBest ? sf::Color::Green : sf::Color::Red;
    }

    if (!path.empty()) {
        lines[path.size()].position = sf::Vector2f(static_cast<float>(points[path[0]].x), static_cast<float>(points[path[0]].y));
        lines[path.size()].color = lines[0].color;
    }

    window.draw(lines);
    window.display();
}

void TSPVisualizer::loop_until_closed() {
    while (window.isOpen()) {
        optional<sf::Event> event = window.pollEvent();
        if (event && event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}