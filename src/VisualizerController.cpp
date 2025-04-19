#include "VisualizerController.h"
#include <thread>
#include <chrono>
#include <cmath>
#include <stdexcept>
#include <SFML/Graphics/Sprite.hpp>

VisualizerController::VisualizerController(const std::vector<Point>& pts, const std::string& title)
    : points(pts), window(sf::VideoMode({1000u, 1000u}), title), hasBackground(false) {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int centerX = static_cast<int>((desktop.size.x - 1000)/2);
    window.setPosition(sf::Vector2i(centerX, 0));
    if (title.find("(Cities)") != std::string::npos) {
        if (!backgroundTexture.loadFromFile("assets/poland_map.png")) {
            throw std::runtime_error("Failed to load background image");
        }
        backgroundSprite.emplace(backgroundTexture);
        hasBackground = true;
    }
    configure_view();
    window.setView(view);
    [[maybe_unused]] bool active = window.setActive();
    window.requestFocus();
}

void VisualizerController::configure_view() {
    if (points.empty()) return;
    if (hasBackground) {
        view = sf::View(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(1000.f, 1000.f)));
        view.setViewport({sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f)});
        return;
    }
    float minX = points[0].x, maxX = points[0].x;
    float minY = points[0].y, maxY = points[0].y;
    for (const auto& p : points) {
        minX = std::min(minX, (float)p.x);
        maxX = std::max(maxX, (float)p.x);
        minY = std::min(minY, (float)p.y);
        maxY = std::max(maxY, (float)p.y);
    }
    float width = maxX - minX;
    float height = maxY - minY;
    float marginX = width * 0.2f;
    float marginY = height * 0.2f;
    sf::FloatRect bounds(sf::Vector2f(minX - marginX, minY - marginY), sf::Vector2f(width + 2 * marginX, height + 2 * marginY));
    view = sf::View(bounds);
    view.setViewport({sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f)});
    if (!hasBackground) {
        sf::Vector2f flippedSize = view.getSize();
        flippedSize.y = -std::abs(flippedSize.y);
        view.setSize(flippedSize);
    }
}

void VisualizerController::draw_line(int from, int to, sf::Color color) {
    lineMap[{std::min(from, to), std::max(from, to)}] = color;
}

void VisualizerController::clear_line(int from, int to) {
    lineMap.erase({std::min(from, to), std::max(from, to)});
}

void VisualizerController::clear_all_lines() {
    lineMap.clear();
}

void VisualizerController::set_point_color(int index, sf::Color color) {
    pointColors[index] = color;
}

void VisualizerController::draw_points() {
    float scale = std::min(view.getSize().x, std::abs(view.getSize().y)) * 0.005f;
    for (size_t i = 0; i < points.size(); ++i) {
        sf::CircleShape circle(scale);
        circle.setOrigin(sf::Vector2f(scale, scale));
        circle.setPosition(sf::Vector2f(static_cast<float>(points[i].x), static_cast<float>(points[i].y)));
        circle.setFillColor(pointColors.count(i) ? pointColors[i] : sf::Color::White);
        window.draw(circle);
    }
}

void VisualizerController::draw_lines() {
    for (const auto& [edge, color] : lineMap) {
        int i = edge.first, j = edge.second;
        sf::Vertex line[] = {
            {sf::Vector2f((float)points[i].x, (float)points[i].y), color},
            {sf::Vector2f((float)points[j].x, (float)points[j].y), color}
        };
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
}

void VisualizerController::render() {
    window.clear(sf::Color::Black);
    if (hasBackground && backgroundSprite.has_value()) {
        window.draw(*backgroundSprite);
    }
    if (!hasBackground) {
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
    }
    draw_points();
    draw_lines();
    window.display();
}

void VisualizerController::sleep(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void VisualizerController::loop_until_closed() {
    while (window.isOpen()) {
        if (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }
    }
}