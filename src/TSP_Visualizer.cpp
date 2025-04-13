#include "TSP_Visualizer.h"
#include <thread>
#include <cfloat>
#include <cmath>
using namespace std;

TSPVisualizer::TSPVisualizer(const std::vector<Point>& pts) : window(sf::VideoMode({1000, 1000}), "TSP Brute Force Visualization"), points(pts) {
    configure_view();
    int n = static_cast<int>(points.size());
    switch(n){
        case 3: delayMs = 250; break;
        case 4: delayMs = 220; break;
        case 5: delayMs = 150; break;
        case 6: delayMs = 70; break;
        case 7: delayMs = 30; break;
        case 8: delayMs = 1;  break;
        default: delayMs = 0;  break;
    }
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
    view.setViewport({sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f)});
    sf::Vector2f flippedSize = view.getSize();
    flippedSize.y = -std::abs(flippedSize.y);
    view.setSize(flippedSize);
    window.setView(view);
}

void TSPVisualizer::update_path(const std::vector<int>& path, bool isBest, double cost) {
    currentPath = path;
    showBest = isBest;
    if (isBest) bestPath = path;
    render();
    if (!isBest && delayMs > 0) std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
}
void TSPVisualizer::render() {
    window.clear(sf::Color::Black);
    sf::Vertex xAxis[] = {
        {sf::Vector2f(-10000.f, 0.f), sf::Color(100, 100, 100)},
        {sf::Vector2f(10000.f, 0.f), sf::Color(100, 100, 100)}
    };
    sf::Vertex yAxis[] = {
        {sf::Vector2f(0.f, -10000.f), sf::Color(100, 100, 100)},
        {sf::Vector2f(0.f, 10000.f), sf::Color(100, 100, 100)}
    };
    window.draw(xAxis, 2, sf::PrimitiveType::Lines);
    window.draw(yAxis, 2, sf::PrimitiveType::Lines);
    float scale = std::min(view.getSize().x, std::abs(view.getSize().y)) * 0.005f;
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