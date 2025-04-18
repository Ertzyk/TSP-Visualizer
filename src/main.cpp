#include <iostream>
#include "Point_Manager.h"
#include "VisualizerController.h"
#include "TSP_Brute_Force.h"
#include "TSP_NN.h"
#include "TSP_Greedy.h"
using namespace std;

enum class AlgorithmType {
    BRUTE_FORCE,
    NEAREST_NEIGHBOR,
    GREEDY
};

AlgorithmType get_algorithm_choice() {
    char choice;
    cout << "\nWhich algorithm do you want to use?\n";
    cout << "[1] Brute-force O(n!)\n[2] Nearest Neighbor O(n^2)\n[3] Greedy O(n^2 * log n)\nEnter 1, 2 or 3: ";
    cin >> choice;
    if (choice == '1') return AlgorithmType::BRUTE_FORCE;
    if (choice == '2') return AlgorithmType::NEAREST_NEIGHBOR;
    if (choice == '3') return AlgorithmType::GREEDY;
    throw std::runtime_error("Invalid algorithm choice.");
}

int get_point_count() {
    int n;
    cout << "\nHow many points do you want to enter: ";
    cin >> n;
    if (n < 3) throw std::runtime_error("You need at least 3 points to form a Hamiltonian cycle.");
    return n;
}

int main() {
    try {
        AlgorithmType algo = get_algorithm_choice();
        int n = get_point_count();
        if (algo == AlgorithmType::BRUTE_FORCE && n > 10) {
            char confirm;
            cout << "\nWarning: Brute-force TSP is extremely slow for more than 10 points.\n";
            cout << "Do you want to continue with brute-force? (Y/n): ";
            cin >> confirm;
            if (confirm == 'n' || confirm == 'N') return 0;
        }
        auto points = PointManager::get_points_from_user(n);
        VisualizerController visualizer(points,
            algo == AlgorithmType::BRUTE_FORCE ? "TSP Brute Force Visualization" :
            algo == AlgorithmType::NEAREST_NEIGHBOR ? "TSP Nearest Neighbor Visualization" :
            "TSP Greedy Visualization");

        switch (algo) {
            case AlgorithmType::BRUTE_FORCE: {
                TSP_Brute_Force solver(points, visualizer);
                solver.solve();
                break;
            }
            case AlgorithmType::NEAREST_NEIGHBOR: {
                TSP_NN solver(points, visualizer);
                solver.solve();
                break;
            }
            case AlgorithmType::GREEDY: {
                TSP_Greedy solver(points, visualizer);
                solver.solve();
                break;
            }
        }
        visualizer.loop_until_closed();
    } catch (const std::exception& e) {
        cerr << "\nError: " << e.what() << endl;
        return 1;
    }
    return 0;
}