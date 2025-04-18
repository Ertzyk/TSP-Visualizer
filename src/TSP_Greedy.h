#ifndef TSP_GREEDY_H
#define TSP_GREEDY_H

#include <vector>
#include "Point.h"
#include "VisualizerController.h"

class TSP_Greedy {
private:
    std::vector<Point> points;
    VisualizerController& visualizer;
    double totalDistance = 0.0;
public:
    TSP_Greedy(std::vector<Point> points, VisualizerController& visualizer);
    double solve();
};

#endif