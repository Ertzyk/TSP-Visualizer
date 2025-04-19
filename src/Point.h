#ifndef POINT_H
#define POINT_H

#include <vector>

class Point {
public:
    double x, y;
    int index = -1;
    Point(double x = 0, double y = 0, int idx = -1);
    double distance_to(const Point& other) const;
    static void set_duration_matrix(const std::vector<std::vector<double>>& matrix);
private:
    static const std::vector<std::vector<double>>* duration_matrix;
};

#endif