#include "Point.h"
#include <cmath>

double Point::distance_to(const Point& other) const {
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}