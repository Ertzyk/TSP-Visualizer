#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat>
using namespace std;

class Point {
public:
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    double distance_to(const Point& other) const {
        return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
    }
};

class PointManager {
public:
    static vector<Point> get_points_from_user(int n) {
        vector<Point> points;
        for (int i = 0; i < n; i++) {
            double x, y;
            cout << "Enter X coordinate for point " << i + 1 << ": ";
            cin >> x;
            cout << "Enter Y coordinate for point " << i + 1 << ": ";
            cin >> y;
            points.emplace_back(x, y);
        }
        return points;
    }
    
    static void print_points(const vector<Point>& points) {
        cout << "\nStored Points:\n";
        for (size_t i = 0; i < points.size(); i++) {
            cout << "Point " << i + 1 << ": (" << points[i].x << ", " << points[i].y << ")\n";
        }
    }
};

class TSP {
private:
    vector<Point> points;
    double minDist;
    vector<int> bestPath;
    
    void tsp_recursive(vector<bool>& visited, int current, int count, double cost, vector<int>& path) {
        if (count == points.size()) {
            cost += points[current].distance_to(points[0]); //Return to start
            if (cost < minDist) {
                minDist = cost;
                bestPath = path;
            }
            return;
        }
        
        for (size_t i = 0; i < points.size(); i++) {
            if (!visited[i]) {
                visited[i] = true;
                path.push_back(i);
                tsp_recursive(visited, i, count + 1, cost + points[current].distance_to(points[i]), path);
                path.pop_back();
                visited[i] = false;
            }
        }
    }
public:
    TSP(vector<Point> points) : points(points), minDist(DBL_MAX) {}
    
    double solve() {
        vector<bool> visited(points.size(), false);
        visited[0] = true;
        vector<int> path = {0};
        tsp_recursive(visited, 0, 1, 0.0, path);
        return minDist;
    }
    
    void print_best_path() const {
        cout << "\nShortest path found (Brute-force): ";
        for (int idx : bestPath) {
            cout << "(" << points[idx].x << ", " << points[idx].y << ") -> ";
        }
        cout << "(" << points[bestPath[0]].x << ", " << points[bestPath[0]].y << ")"; // Return to start
        cout << "\nTotal Distance: " << minDist << "\n";
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n;
    cout << "How many points do you want to enter: ";
    cin >> n;
    
    vector<Point> points = PointManager::get_points_from_user(n);
    PointManager::print_points(points);
    
    TSP tsp_solver(points);
    tsp_solver.solve();
    tsp_solver.print_best_path();
    
    return 0;
}