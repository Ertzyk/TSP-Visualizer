#ifndef TSP_2OPT_H
#define TSP_2OPT_H

#include "Point.h"
#include "VisualizerController.h"
#include <vector>
#include <random>

class TSP_2Opt {
private:
    std::vector<Point> points;
    VisualizerController& visualizer;
    std::vector<int> path;
    std::mt19937 rng;
    struct pt;
    int sgn(double x) const;
    bool inter1(double a, double b, double c, double d) const;
    bool segments_intersect(const Point& A, const Point& B, const Point& C, const Point& D) const;
    void randomize_path();
    bool perform_2opt_swap();

public:
    TSP_2Opt(std::vector<Point> points, VisualizerController& visualizer);
    double solve();
    double tour_length() const;
};

#endif