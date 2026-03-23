#include "TSP_Greedy.h"
#include <algorithm>
#include <tuple>
#include <numeric>
#include <iostream>
#include <thread>
using namespace std;

struct Edge {
    int from;
    int to;
    double weight;
};

// Disjoint Set Union (Union-Find)
// Implements both path compression and union by size for optimal performance.
class DSU {
private:
    vector<int> parent, size;
public:
    DSU(int n) : parent(n), size(n, 1) {
        for(int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int v) {
        if(v == parent[v]) return v;
        return parent[v] = find(parent[v]); // Path compression
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if(a != b) {
            if(size[a] < size[b]) std::swap(a, b); // Union by size
            parent[b] = a;
            size[a] += size[b];
        }
    }
    bool connected(int a, int b) {
        return find(a) == find(b);
    }
};

TSP_Greedy::TSP_Greedy(vector<Point> pts, VisualizerController& vis) : points(move(pts)), visualizer(vis) {}


// Similar to Kruskal's Minimum Spanning Tree algorithm, but constrained to ensure 
// the resulting graph is a valid collection of paths that eventually form a single cycle.
double TSP_Greedy::solve(){
    int n = static_cast<int>(points.size());
    vector<Edge> edges;

    // Generate complete graph edge weights
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            double dist = points[i].distance_to(points[j]);
            edges.push_back({i, j, dist});
        }
    }

    // Sort edges globally from shortest to longest
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    DSU dsu(n);
    vector<int> degree(n, 0);
    vector<pair<int, int>> accepted;

    // Iterate through all edges and attempt to add them to the tour
    for(const auto& e : edges){
        int u = e.from, v = e.to;

        // Visualization: Show edge being considered in Blue
        visualizer.draw_line(u, v, sf::Color::Blue);
        visualizer.render();
        visualizer.sleep(300);

        // Constraints for a valid TSP tour:
        // 1. No node can have a degree > 2 (it must be a simple path/cycle).
        // 2. The edge must not create a premature cycle (unless it's the very last edge connecting the tour).
        bool canAdd = (degree[u] < 2 && degree[v] < 2 && !dsu.connected(u, v));
        if(canAdd){
            dsu.unite(u, v);
            degree[u]++;
            degree[v]++;
            totalDistance += e.weight;
            accepted.emplace_back(u, v);
            // Visualization: Accepted edge turns Green
            visualizer.draw_line(u, v, sf::Color::Green);
        } else {
            // Visualization: Rejected edge flashes Red, then disappears
            visualizer.draw_line(u, v, sf::Color::Red);
            visualizer.render();
            visualizer.sleep(200);
            visualizer.clear_line(u, v);
        }
        visualizer.render();
        // Stop early once we have built a path of N-1 edges
        if (accepted.size() == n - 1) break;
    }

    // Final Step: Find the two endpoint nodes (degree == 1) and connect them
    // to complete the Hamiltonian cycle.
    int a = -1, b = -1;
    for(int i = 0; i < n; ++i) {
        if(degree[i] == 1) {
            if(a == -1) a = i;
            else b = i;
        }
    }
    if(a != -1 && b != -1) {
        visualizer.draw_line(a, b, sf::Color::Green);
        visualizer.render();
        totalDistance += points[a].distance_to(points[b]);
    }
    return totalDistance;
}
