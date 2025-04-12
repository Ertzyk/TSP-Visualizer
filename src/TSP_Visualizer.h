#ifndef TSP_VISUALIZER_H
#define TSP_VISUALIZER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Point.h"

class TSPVisualizer {
private:
    sf::RenderWindow window;
    std::vector<Point> points;
    std::vector<int> currentPath;
    std::vector<int> bestPath;
    bool showBest = false;
public:
    TSPVisualizer(const std::vector<Point>& points);
    void update_path(const std::vector<int>& path, bool isBest = false);
    void render();
    void loop_until_closed();
};

#endif