#include <iostream>
#include "Point_Manager.h"
#include "TSP_Visualizer.h"
#include "TSP.h"

int main() {
    int n;
    std::cout << "How many points do you want to enter: ";
    std::cin >> n;

    auto points = PointManager::get_points_from_user(n);

    TSPVisualizer visualizer(points);
    TSP solver(points, visualizer);

    solver.solve();
    visualizer.loop_until_closed();

    return 0;
}