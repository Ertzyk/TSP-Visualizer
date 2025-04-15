// TSP_NN.h (Updated to use VisualizerController)
#ifndef TSP_NN_H
#define TSP_NN_H

#include <vector>
#include "Point.h"
#include "VisualizerController.h"

class TSP_NN {
private:
    std::vector<Point> points;
    std::vector<int> path;
    double totalDistance = 0.0;
    VisualizerController& visualizer;

public:
    TSP_NN(std::vector<Point> points, VisualizerController& visualizer);
    double solve();
};

#endif