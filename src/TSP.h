#ifndef TSP_H
#define TSP_H

#include <vector>
#include "Point.h"
#include "TSP_Visualizer.h"

class TSP {
private:
    std::vector<Point> points;
    double minDist;
    std::vector<int> bestPath;
    TSPVisualizer& visualizer;
    void tsp_recursive(std::vector<bool>& visited, int current, int count, double cost, std::vector<int>& path);
public:
    TSP(std::vector<Point> points, TSPVisualizer& visualizer);
    double solve();
    const std::vector<int>& get_best_path() const;
};

#endif