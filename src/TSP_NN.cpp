#include "TSP_NN.h"
#include <limits>
#include <iostream>

TSP_NN::TSP_NN(std::vector<Point> pts, VisualizerController& vis) : points(std::move(pts)), visualizer(vis) {}

double TSP_NN::solve() {
    visualizer.sleep(4000);
    int n = static_cast<int>(points.size());
    std::vector<bool> visited(n, false);
    path.clear();
    totalDistance = 0.0;
    int current = 0;
    visited[current] = true;
    path.push_back(current);
    for (int step = 1; step < n; ++step) {
        int next = -1;
        double bestDist = std::numeric_limits<double>::max();
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                double dist = points[current].distance_to(points[i]);
                visualizer.draw_line(current, i, sf::Color::Red);
                visualizer.render();
                visualizer.sleep(300);
                visualizer.clear_line(current, i);
                visualizer.render();
                visualizer.sleep(100);
                if (dist < bestDist) {
                    bestDist = dist;
                    next = i;
                }
            }
        }
        if (next != -1) {
            visited[next] = true;
            totalDistance += bestDist;
            visualizer.draw_line(current, next, sf::Color::Green);
            path.push_back(next);
            current = next;
            visualizer.render();
            visualizer.sleep(300);
        }
    }
    path.push_back(path[0]);
    totalDistance += points[current].distance_to(points[path[0]]);
    visualizer.draw_line(current, path[0], sf::Color::Green);
    visualizer.render();
    return totalDistance;
}