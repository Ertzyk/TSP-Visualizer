#include "CityTSPRunner.h"
#include "Point.h"
#include "VisualizerController.h"
#include "AlgorithmType.h"
#include "OpenRouteServiceClient.h"
#include "TSP_Brute_Force.h"
#include "TSP_NN.h"
#include "TSP_Greedy.h"
#include <iostream>

CityTSPRunner::CityTSPRunner(const std::string& key, const std::vector<std::string>& cities, AlgorithmType algo)
    : apiKey(key), cityNames(cities), algorithm(algo) {}

void CityTSPRunner::run() {
    try {
        OpenRouteServiceClient client(apiKey);
        auto latlon = client.get_coordinates(cityNames);
        std::vector<Point> points;
        const double POLAND_MIN_LAT = 48.6;
        const double POLAND_MAX_LAT = 55.5;
        const double POLAND_MIN_LON = 13.5;
        const double POLAND_MAX_LON = 24.7;
        for (int i = 0; i < static_cast<int>(latlon.size()); ++i) {
            double lat = latlon[i].first;
            double lon = latlon[i].second;
            int x = static_cast<int>((lon - POLAND_MIN_LON) / (POLAND_MAX_LON - POLAND_MIN_LON) * 1000);
            int y = static_cast<int>((POLAND_MAX_LAT - lat) / (POLAND_MAX_LAT - POLAND_MIN_LAT) * 1000);
            points.emplace_back(x, y, i);
        }
        VisualizerController visualizer(points,
            algorithm == AlgorithmType::BRUTE_FORCE ? "TSP Brute Force Visualization (Cities)" :
            algorithm == AlgorithmType::NEAREST_NEIGHBOR ? "TSP Nearest Neighbor Visualization (Cities)" :
            "TSP Greedy Visualization (Cities)");
        auto matrix = client.get_duration_matrix(latlon);
        Point::set_duration_matrix(matrix);
        switch (algorithm) {
            case AlgorithmType::BRUTE_FORCE: {
                TSP_Brute_Force solver(points, visualizer);
                double result = solver.solve();
                std::cout << "\nMinimum travel time: " << (result / 3600.0) << " hours\n";
                break;
            }
            case AlgorithmType::NEAREST_NEIGHBOR: {
                TSP_NN solver(points, visualizer);
                double result = solver.solve();
                std::cout << "\nMinimum travel time: " << (result / 3600.0) << " hours\n";
                break;
            }
            case AlgorithmType::GREEDY: {
                TSP_Greedy solver(points, visualizer);
                double result = solver.solve();
                std::cout << "\nMinimum travel time: " << (result / 3600.0) << " hours\n";
                break;
            }
        }
        visualizer.loop_until_closed();
    } catch (const std::exception& e) {
        std::cerr << "\nCityTSPRunner failed: " << e.what() << std::endl;
    }
}