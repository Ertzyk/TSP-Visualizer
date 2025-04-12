#ifndef POINT_MANAGER_H
#define POINT_MANAGER_H

#include <vector>
#include "Point.h"

class PointManager {
public:
    static std::vector<Point> get_points_from_user(int n);
};

#endif