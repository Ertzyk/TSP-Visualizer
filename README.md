# TSP-Visualizer

A C++ project for visualizing solutions to the **Travelling Salesman Problem (TSP)** using **SFML**, with support for both coordinate-based points and real-world cities in Poland.

---

## Features
- Interactive visualization of TSP algorithms:
  - Brute Force (Θ(n!))
  - Nearest Neighbor (Θ(n²))
  - Greedy (Θ(n² log n))
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
g++ main.cpp Point.cpp Point_Manager.cpp TSP_Brute_Force.cpp VisualizerController.cpp TSP_NN.cpp TSP_Greedy.cpp CityTSPRunner.cpp ConfigLoader.cpp OpenRouteServiceClient.cpp -o tsp_visualizer.exe -IC:\SFML\SFML-3.0.0\include -LC:\SFML\SFML-3.0.0\lib -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lgdi32 -IC:\libs\curl\curl-8.13.0_2-win64-mingw\include -LC:\libs\curl\curl-8.13.0_2-win64-mingw\lib -lcurl -Iexternal
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
src/
├── assets/                  # Background map
│   └── poland_map.png
├── external/               # Third-party headers
│   └── nlohmann/json.hpp
├── config.json             # (Your API key — NOT COMMITTED)
├── config.example.json     # Public template for config
├── main.cpp
├── TSP_*.cpp               # Algorithms
└── ...                     # Core logic and visualization
```