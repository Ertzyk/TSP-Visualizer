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

class DSU {
private:
    vector<int> parent, size;
public:
    DSU(int n) : parent(n), size(n, 1) {
        for(int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int v) {
        if(v == parent[v]) return v;
        return parent[v] = find(parent[v]);
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if(a != b) {
            if(size[a] < size[b]) std::swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
    bool connected(int a, int b) {
        return find(a) == find(b);
    }
};

TSP_Greedy::TSP_Greedy(vector<Point> pts, VisualizerController& vis) : points(move(pts)), visualizer(vis) {}

double TSP_Greedy::solve(){
    int n = static_cast<int>(points.size());
    vector<Edge> edges;

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            double dist = points[i].distance_to(points[j]);
            edges.push_back({i, j, dist});
        }
    }

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    DSU dsu(n);
    vector<int> degree(n, 0);
    vector<pair<int, int>> accepted;

    for(const auto& e : edges){
        int u = e.from, v = e.to;
        visualizer.draw_line(u, v, sf::Color::Blue);
        visualizer.render();
        visualizer.sleep(300);
        bool canAdd = (degree[u] < 2 && degree[v] < 2 && !dsu.connected(u, v));
        if(canAdd){
            dsu.unite(u, v);
            degree[u]++;
            degree[v]++;
            totalDistance += e.weight;
            accepted.emplace_back(u, v);
            visualizer.draw_line(u, v, sf::Color::Green);
        } else {
            visualizer.draw_line(u, v, sf::Color::Red);
            visualizer.render();
            visualizer.sleep(200);
            visualizer.clear_line(u, v);
        }
        visualizer.render();
        if (accepted.size() == n - 1) break;
    }
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
