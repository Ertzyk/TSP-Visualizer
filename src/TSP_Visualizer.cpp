#include "TSP_Visualizer.h"
#include <thread>
#include <cfloat>
using namespace std;

TSPVisualizer::TSPVisualizer(const std::vector<Point>& pts) : window(sf::VideoMode({1000, 1000}), "TSP Brute Force Visualization"), points(pts) {
    configure_view();
}

void TSPVisualizer::configure_view() {
    if (points.empty()) return;
    float minX = points[0].x, maxX = points[0].x;
    float minY = points[0].y, maxY = points[0].y;
    for (const auto& p : points) {
        if (p.x < minX) minX = p.x;
        if (p.x > maxX) maxX = p.x;
        if (p.y < minY) minY = p.y;
        if (p.y > maxY) maxY = p.y;
    }
    float width = maxX - minX;
    float height = maxY - minY;
    float marginX = width * 0.2f;
    float marginY = height * 0.2f;
    sf::FloatRect bounds(
        sf::Vector2f(minX - marginX, minY - marginY),
        sf::Vector2f(width + 2 * marginX, height + 2 * marginY)
    );
    view = sf::View(bounds);
    window.setView(view);
}

void TSPVisualizer::update_path(const std::vector<int>& path, bool isBest, double cost) {
    currentPath = path;
    showBest = isBest;
    if (isBest) bestPath = path;
    render();
    if (!isBest) std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

void TSPVisualizer::render() {
    window.clear(sf::Color::Black);
    float scale = std::min(view.getSize().x, view.getSize().y) * 0.005f;
    for (const auto& p : points) {
        sf::CircleShape circle(scale);
        circle.setFillColor(sf::Color::White);
        circle.setOrigin(sf::Vector2f(scale, scale));
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
        if (event && event->is<sf::Event::Closed>()) window.close();
    }
}