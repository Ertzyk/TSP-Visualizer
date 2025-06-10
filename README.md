# TSP-Visualizer

A C++ project for visualizing solutions to the **Travelling Salesman Problem (TSP)** using **SFML**, with support for both coordinate-based points and real-world cities in Poland.

---

## Features
- Interactive visualization of TSP algorithms:
  - Exact Algorithms:
    - [Brute Force](https://en.wikipedia.org/wiki/Brute-force_search) (Θ(n!))
    - ~~[Held-Karp](https://en.wikipedia.org/wiki/Held%E2%80%93Karp_algorithm) (Θ(n² · 2ⁿ))~~ — *Planned*
  - Heuristic Algorithms:
    - [Nearest Neighbor](https://en.wikipedia.org/wiki/Nearest_neighbour_algorithm) (Θ(n²))
    - [Greedy](https://www.youtube.com/watch?v=nYKsLRxIBmA) (Θ(n² log n))
    - [2-opt](https://en.wikipedia.org/wiki/2-opt) (Worst-case O(n² · 2ⁿ), average-case O(n³) (empirical))
- Two input modes:
  - Manual coordinate input
  - Real-world Polish cities (via OpenRouteService API)
- Real map of Poland as background for city mode
- Smooth visualization with colored transitions

---

## Visualization
Brute Force in coordinate input mode:
<p align="left">
  <img src="assets/demo_brute_force.gif" width="450"/>
</p>

Nearest Neighbor in city input mode:
<p align="left">
  <img src="assets/NN_demo.gif" width="450"/>
</p>

Greedy in coordinate input mode:
<p align="left">
  <img src="assets/greedy_demo.gif" width="450"/>
</p>

2-opt in coordinate input mode:
<p align="left">
  <img src="assets/2-opt_demo.gif" width="450"/>
</p>

---

## Getting Started

### Prerequisites
- **SFML 3.0.0**:
  - Place includes in `C:\SFML\include` and libs in `C:\SFML\lib`
  - Add `C:\SFML\bin` to your system `PATH`so the runtime can find required DLLs
- **cURL**:
  - Place includes in `C:\libs\curl\include` and libs in `C:\libs\curl\lib`
- **OpenRouteService API key**: Required for city mode

### API Key Setup
1. Sign up at [openrouteservice.org](https://openrouteservice.org)
2. Copy your API key
3. Duplicate the config template:
   - Copy `src/config.example.json` → `src/config.json`
4. Paste your API key inside:

```json
{
  "ors_api_key": "YOUR_API_KEY_HERE"
}
```


---

## Running the Program

Compile with this line:
```bash
g++ main.cpp Point.cpp Point_Manager.cpp TSP_Brute_Force.cpp VisualizerController.cpp TSP_NN.cpp TSP_Greedy.cpp TSP_2Opt.cpp CityTSPRunner.cpp ConfigLoader.cpp OpenRouteServiceClient.cpp -o tsp_visualizer.exe -IC:\SFML\include -LC:\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lgdi32 -IC:\libs\curl\include -LC:\libs\curl\lib -lcurl -Iexternal
```
Then run:
```bash
./tsp_visualizer.exe
```

Follow the terminal prompts to:
- Choose input mode (coordinates or cities)
- Select algorithm
- Input data (either coordinates or city names)

---

## Project Structure
```
├── README.md
├── LICENSE
├── .gitignore
├── config.example.json
├── assets/  
│   ├── 2-opt_demo.gif
│   ├── demo_brute_force.gif
│   ├── greedy_demo.gif
│   └── NN_demo.gif
└── src/
    ├── main.cpp
    ├── AlgorithmType.h
    ├── CityTSPRunner.cpp
    ├── CityTSPRunner.h
    ├── ConfigLoader.cpp
    ├── ConfigLoader.h
    ├── HashUtils.h
    ├── OpenRouteServiceClient.cpp
    ├── OpenRouteServiceClient.h
    ├── Point.cpp
    ├── Point.h
    ├── Point_Manager.cpp
    ├── Point_Manager.h
    ├── TSP_2Opt.cpp
    ├── TSP_2Opt.h
    ├── TSP_Brute_Force.cpp
    ├── TSP_Brute_Force.h
    ├── TSP_Greedy.cpp
    ├── TSP_Greedy.h
    ├── TSP_NN.cpp
    ├── TSP_NN.h
    ├── VisualizerController.cpp
    ├── VisualizerController.h
    ├── assets/
    │   └── poland_map.jpg
    └── external/
        └── nlohmann/
            └── json.hpp
```

## External Libraries Used

This project relies on the following third-party C++ libraries:

### SFML
- **Purpose**: Graphics, windowing, and input.
- **Used in**: `VisualizerController`
- **Website**: [sfml-dev.org](https://www.sfml-dev.org)

### libcurl
- **Purpose**: HTTP requests to OpenRouteService.
- **Used in**: `OpenRouteServiceClient`
- **Website**: [curl.se](https://curl.se)

### nlohmann/json
- **Purpose**: JSON parsing and serialization.
- **Used in**: `OpenRouteServiceClient`
- **Website**: [github.com/nlohmann/json](https://github.com/nlohmann/json)