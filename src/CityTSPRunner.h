#ifndef CITY_TSP_RUNNER_H
#define CITY_TSP_RUNNER_H

#include <string>
#include <vector>
#include "VisualizerController.h"
#include "TSP_NN.h"
#include "TSP_Greedy.h"
#include "TSP_Brute_Force.h"
#include "OpenRouteServiceClient.h"

enum class AlgorithmType;

class CityTSPRunner {
private:
    std::string apiKey;
    std::vector<std::string> cityNames;
    AlgorithmType algorithm;
public:
    CityTSPRunner(const std::string& key, const std::vector<std::string>& cities, AlgorithmType algo);
    void run();
};

#endif