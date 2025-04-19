#include "Point.h"
#include <cmath>

const std::vector<std::vector<double>>* Point::duration_matrix = nullptr;

Point::Point(double x, double y, int idx) : x(x), y(y), index(idx) {}

double Point::distance_to(const Point& other) const {
    if (duration_matrix && index >= 0 && other.index >= 0) {
        return (*duration_matrix)[index][other.index];
    }
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

void Point::set_duration_matrix(const std::vector<std::vector<double>>& matrix) {
    duration_matrix = &matrix;
}