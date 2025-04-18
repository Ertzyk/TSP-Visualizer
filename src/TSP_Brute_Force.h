#ifndef TSP_BRUTE_FORCE_H
#define TSP_BRUTE_FORCE_H

#include <vector>
#include "Point.h"
#include "VisualizerController.h"

class TSP_Brute_Force{
private:
    std::vector<Point> points;
    double minDist;
    std::vector<int> bestPath;
    VisualizerController& visualizer;
    void tsp_recursive(std::vector<bool>& visited, int current, int count, double cost, std::vector<int>& path);
    int delayMs = 0;
public:
    TSP_Brute_Force(std::vector<Point> points, VisualizerController& visualizer);
    double solve();
    const std::vector<int>& get_best_path() const;
};

#endif