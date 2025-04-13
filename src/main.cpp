#include <iostream>
#include "Point_Manager.h"
#include "TSP_Visualizer.h"
#include "TSP.h"
using namespace std;

int main() {
    int n;
    cout << "How many points do you want to enter: ";
    cin >> n;
    if (n < 3) {
        cout << "\nError: You need at least 3 points to form a Hamiltonian cycle.\n";
        return 1;
    }
    if (n > 10) {
        char choice;
        cout << "\nWarning: Brute-force TSP is extremely slow for more than 10 points.\n";
        cout << "This could take minutes or hours depending on your machine.\n";
        cout << "Do you want to continue? (Y/n): ";
        cin >> choice;
        if (choice == 'n' || choice == 'N') {
            cout << "Aborted by user.\n";
            return 0;
        }
    }
    auto points = PointManager::get_points_from_user(n);
    TSPVisualizer visualizer(points);
    TSP solver(points, visualizer);
    solver.solve();
    visualizer.loop_until_closed();
    return 0;
}