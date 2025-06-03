#ifndef VISUALIZER_CONTROLLER_H
#define VISUALIZER_CONTROLLER_H

#include "HashUtils.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include "Point.h"
#include <optional>

class VisualizerController {
private:
    sf::RenderWindow window;
    sf::View view;
    std::vector<Point> points;
    std::unordered_map<std::pair<int, int>, sf::Color> lineMap;
    std::unordered_map<int, sf::Color> pointColors;
    int delayMs = 0;
    sf::Texture backgroundTexture;
    std::optional<sf::Sprite> backgroundSprite;
    bool hasBackground = false;
    void configure_view();
    void draw_points();
    void draw_lines();
public:
    VisualizerController(const std::vector<Point>& pts, const std::string& title);
    void draw_line(int from, int to, sf::Color color);
    void clear_line(int from, int to);
    void clear_all_lines();
    void set_point_color(int index, sf::Color color);
    void render();
    void sleep(int ms);
    void loop_until_closed();
    void update_path(const std::vector<int>& path, bool final = false);
};

#endif