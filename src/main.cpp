#include <iostream>
#include <vector>
#include <string>
#include "Point_Manager.h"
#include "VisualizerController.h"
#include "TSP_Brute_Force.h"
#include "TSP_NN.h"
#include "TSP_Greedy.h"
#include "ConfigLoader.h"
#include "CityTSPRunner.h"
#include "AlgorithmType.h"

using namespace std;

enum class ModeType {
    COORDINATE_INPUT,
    CITY_INPUT
};

ModeType get_input_mode() {
    char choice;
    cout << "\nChoose input mode:\n";
    cout << "[1] Coordinate Points\n";
    cout << "[2] Real-Life Cities (Poland)\n";
    cout << "Enter 1 or 2: ";
    cin >> choice;
    if (choice == '1') return ModeType::COORDINATE_INPUT;
    if (choice == '2') return ModeType::CITY_INPUT;
    throw std::runtime_error("Invalid input mode.");
}

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
        ModeType mode = get_input_mode();
        AlgorithmType algo = get_algorithm_choice();
        if (mode == ModeType::COORDINATE_INPUT) {
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
                    double result = solver.solve();
                    std::cout << "\nMinimum path cost: " << result << std::endl;
                    break;
                }
                case AlgorithmType::NEAREST_NEIGHBOR: {
                    TSP_NN solver(points, visualizer);
                    double result = solver.solve();
                    std::cout << "\nMinimum path cost: " << result << std::endl;
                    break;
                }
                case AlgorithmType::GREEDY: {
                    TSP_Greedy solver(points, visualizer);
                    double result = solver.solve();
                    std::cout << "\nMinimum path cost: " << result << std::endl;
                    break;
                }
            }
            visualizer.loop_until_closed();
        } else if (mode == ModeType::CITY_INPUT) {
            std::string apiKey = ConfigLoader::load_api_key("config.json");
            int cityCount;
            cout << "\nHow many cities do you want to enter (max 50): ";
            cin >> cityCount;
            if (cityCount < 3 || cityCount > 50)
                throw std::runtime_error("City count must be between 3 and 50.");
            std::vector<std::string> cityNames;
            cout << "\nEnter city names (e.g., Warsaw, Krakow):\n";
            cin.ignore();
            for (int i = 0; i < cityCount; ++i) {
                std::string city;
                std::getline(cin, city);
                cityNames.push_back(city);
            }
            CityTSPRunner runner(apiKey, cityNames, algo);
            runner.run();
        }
    } catch (const std::exception& e) {
        cerr << "\nError: " << e.what() << endl;
        return 1;
    }
    return 0;
}