#include "TSP.h"
#include <cfloat>
#include <iostream>
#include <thread>
#include <chrono>

TSP::TSP(std::vector<Point> pts, TSPVisualizer& vis) : points(std::move(pts)), minDist(DBL_MAX), visualizer(vis) {}

void TSP::tsp_recursive(std::vector<bool>& visited, int current, int count, double cost, std::vector<int>& path) {
    if (count == points.size()) {
        cost += points[current].distance_to(points[0]);
        if (path.size() > 2 && path[1] > path.back()) return;
        visualizer.update_path(path);
        if (cost < minDist) {
            minDist = cost;
            bestPath = path;
            visualizer.update_path(path, true);
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
    visualizer.update_path({});
    std::this_thread::sleep_for(std::chrono::seconds(2));
    tsp_recursive(visited, 0, 1, 0.0, path);
    visualizer.update_path(bestPath, true);
    std::cout << "\nMinimum path cost: " << minDist << std::endl;
    return minDist;
}

const std::vector<int>& TSP::get_best_path() const {
    return bestPath;
}