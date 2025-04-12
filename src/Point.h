#ifndef POINT_H
#define POINT_H

class Point {
public:
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    double distance_to(const Point& other) const;
};

#endif