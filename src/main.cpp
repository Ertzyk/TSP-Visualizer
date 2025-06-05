#include <iostream>
#include <vector>
#include <string>
#include "Point_Manager.h"
#include "VisualizerController.h"
#include "TSP_Brute_Force.h"
#include "TSP_NN.h"
#include "TSP_Greedy.h"
#include "TSP_2Opt.h"
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
    cout << "\nChoose input mode:\n[1] Coordinate Points\n[2] Real-Life Cities (Poland)\nEnter 1 or 2: ";
    cin >> choice;
    if (choice == '1') return ModeType::COORDINATE_INPUT;
    if (choice == '2') return ModeType::CITY_INPUT;
    throw runtime_error("Invalid input mode.");
}

AlgorithmType get_algorithm_choice(ModeType mode) {
    char choice;
    cout << "\nWhich algorithm do you want to use?\n[1] Brute-force  O(n!)\n[2] Nearest-Neighbor  O(n^2)\n[3] Greedy  O(n^2 log n)"; 
    if (mode == ModeType::COORDINATE_INPUT) cout << "\n[4] 2-opt  Worst case: O(2^n*n^2), Average case: proved O(n^(6 + 1/3)), empirical O(n^3)";
    cout << "\nEnter choice: ";
    cin >> choice;
    switch (choice) {
        case '1': return AlgorithmType::BRUTE_FORCE;
        case '2': return AlgorithmType::NEAREST_NEIGHBOR;
        case '3': return AlgorithmType::GREEDY;
        case '4': if (mode == ModeType::COORDINATE_INPUT) return AlgorithmType::TWO_OPT;
    }
    throw runtime_error("Invalid algorithm choice.");
}

int get_point_count() {
    int n;
    cout << "\nHow many points do you want to enter: ";
    cin >> n;
    if(n < 3) throw runtime_error("You need at least 3 points to form a Hamiltonian cycle.");
    return n;
}

int main(){
    ModeType mode = get_input_mode();
    AlgorithmType algo = get_algorithm_choice(mode);
    if(mode == ModeType::COORDINATE_INPUT) {
        int n = get_point_count();
        auto points = PointManager::get_points_from_user(n);
        VisualizerController visualizer(
            points, algo == AlgorithmType::BRUTE_FORCE ? "TSP Brute-force Visualisation" :
            algo == AlgorithmType::NEAREST_NEIGHBOR ? "TSP Nearest-Neighbour Visualisation" :
            algo == AlgorithmType::GREEDY ? "TSP Greedy Visualisation" : "TSP 2-opt Visualisation");
        switch(algo) {
            case AlgorithmType::BRUTE_FORCE: {
                TSP_Brute_Force solver(points, visualizer);
                double result = solver.solve();
                cout << "\nMinimum path cost: " << result << '\n';
                break;
            }
            case AlgorithmType::NEAREST_NEIGHBOR: {
                TSP_NN solver(points, visualizer);
                double result = solver.solve();
                std::cout << "\nMinimum path cost: " << result << '\n';
                break;
            }
            case AlgorithmType::GREEDY: {
                TSP_Greedy solver(points, visualizer);
                double result = solver.solve();
                std::cout << "\nMinimum path cost: " << result << '\n';
                break;
            }
            case AlgorithmType::TWO_OPT: {
                TSP_2Opt solver(points, visualizer);
                double result = solver.solve();
                cout << "\nMinimum path cost: " << result << '\n';
                break;
            }
        }
        visualizer.loop_until_closed();
    } else if (mode == ModeType::CITY_INPUT) {
        std::string apiKey = ConfigLoader::load_api_key("config.json");
        int cityCount;
        cout << "\nHow many cities do you want to enter (max 50): ";
        cin >> cityCount;
        if(cityCount < 3 || cityCount > 50) throw runtime_error("City count must be between 3 and 50.");
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
    return 0;
}