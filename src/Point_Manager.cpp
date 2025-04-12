#include "Point_Manager.h"
#include <iostream>
using namespace std;

vector<Point> PointManager::get_points_from_user(int n) {
    vector<Point> points;
    for (int i = 0; i < n; ++i) {
        double x, y;
        cout << "Enter X coordinate for point " << i + 1 << ": ";
        cin >> x;
        cout << "Enter Y coordinate for point " << i + 1 << ": ";
        cin >> y;
        points.emplace_back(x, y);
    }
    return points;
}