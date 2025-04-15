#include "TSP.h"
#include <cfloat>
#include <iostream>
#include <thread>
#include <chrono>

TSP::TSP(std::vector<Point> pts, VisualizerController& vis)
    : points(std::move(pts)), minDist(DBL_MAX), visualizer(vis) {}

void TSP::tsp_recursive(std::vector<bool>& visited, int current, int count, double cost, std::vector<int>& path) {
    if (count == points.size()) {
        cost += points[current].distance_to(points[0]);
        if (path.size() > 2 && path[1] > path.back()) return;
        for (size_t i = 1; i < path.size(); ++i) {
            visualizer.draw_line(path[i - 1], path[i], sf::Color::Red);
        }
        visualizer.draw_line(path.back(), path[0], sf::Color::Red);
        visualizer.render();
        visualizer.sleep(delayMs);
        for (size_t i = 1; i < path.size(); ++i) {
            visualizer.clear_line(path[i - 1], path[i]);
        }
        visualizer.clear_line(path.back(), path[0]);
        if (cost < minDist) {
            minDist = cost;
            bestPath = path;
        }
        return;
    }

    for (size_t i = 0; i < points.size(); ++i) {
        if (!visited[i]) {
            visited[i] = true;
            path.push_back(i);
            tsp_recursive(visited, i, count + 1, cost + points[current].distance_to(points[i]), path);
            path.pop_back();
            visited[i] = false;
        }
    }
}

double TSP::solve() {
    std::vector<bool> visited(points.size(), false);
    std::vector<int> path = {0};
    visited[0] = true;
    int n = static_cast<int>(points.size());
    switch(n){
        case 3: delayMs = 250; break;
        case 4: delayMs = 220; break;
        case 5: delayMs = 150; break;
        case 6: delayMs = 70; break;
        case 7: delayMs = 30; break;
        case 8: delayMs = 1; break;
        default: delayMs = 0; break;
    }
    visualizer.clear_all_lines();
    visualizer.render();
    visualizer.sleep(1000);
    auto start = std::chrono::high_resolution_clock::now();
    tsp_recursive(visited, 0, 1, 0.0, path);
    auto end = std::chrono::high_resolution_clock::now();
    for (size_t i = 1; i < bestPath.size(); ++i) {
        visualizer.draw_line(bestPath[i - 1], bestPath[i], sf::Color::Green);
    }
    visualizer.draw_line(bestPath.back(), bestPath[0], sf::Color::Green);
    visualizer.render();
    std::chrono::duration<double> duration = end - start;
    std::cout << "\nMinimum path cost: " << minDist << std::endl;
    std::cout << "Execution time (no delay): " << duration.count() << " seconds\n";
    return minDist;
}

const std::vector<int>& TSP::get_best_path() const {
    return bestPath;
}