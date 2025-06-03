#include "TSP_2Opt.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <numeric> 

struct pt {
    double x, y;
    pt(double x = 0, double y = 0) : x(x), y(y) {}
    pt operator-(const pt &p) const { return pt(x - p.x, y - p.y); }
    double cross(const pt &p) const { return x * p.y - y * p.x; }
    double cross(const pt &a, const pt &b) const { return (a - *this).cross(b - *this); }
};

static int sgn(double x) { return x > 0 ? 1 : (x < 0 ? -1 : 0); }

static bool inter1(double a, double b, double c, double d) {
    if (a > b) std::swap(a, b);
    if (c > d) std::swap(c, d);
    return std::max(a, c) <= std::min(b, d);
}

static bool segments_intersect(const Point &A, const Point &B, const Point &C, const Point &D) {
    pt a(A.x, A.y), b(B.x, B.y), c(C.x, C.y), d(D.x, D.y);
    if (c.cross(a, d) == 0 && c.cross(b, d) == 0) return inter1(a.x, b.x, c.x, d.x) && inter1(a.y, b.y, c.y, d.y);
    return sgn(a.cross(b, c)) != sgn(a.cross(b, d)) && sgn(c.cross(d, a)) != sgn(c.cross(d, b));
}

bool TSP_2Opt::segments_intersect(const Point& A, const Point& B, const Point& C, const Point& D) const {
    return ::segments_intersect(A, B, C, D);
}

TSP_2Opt::TSP_2Opt(std::vector<Point> pts, VisualizerController &vis)
    : points(std::move(pts)), visualizer(vis),
      rng(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count())) {
    path.resize(points.size());
    std::iota(path.begin(), path.end(), 0);
}

void TSP_2Opt::randomize_path() {
    if (path.empty()) return;
    std::shuffle(path.begin() + 1, path.end(), rng);
}

bool TSP_2Opt::perform_2opt_swap(){
    const int n = static_cast<int>(path.size());
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 2; j < n - (i == 0 ? 1 : 0); ++j) {
            int a = path[i];
            int b = path[(i + 1) % n];
            int c = path[j];
            int d = path[(j + 1) % n];
            if (segments_intersect(points[a], points[b], points[c], points[d])) {
                visualizer.clear_all_lines();
                visualizer.update_path(path);
                visualizer.draw_line(a, b, sf::Color::Red);
                visualizer.draw_line(c, d, sf::Color::Red);
                visualizer.render();
                visualizer.sleep(200);
                std::reverse(path.begin() + i + 1, path.begin() + j + 1);
                visualizer.clear_all_lines();
                visualizer.update_path(path);
                visualizer.render();
                visualizer.sleep(200);
                return true;
            }
        }
    }
    return false;
}

double TSP_2Opt::tour_length() const {
    double dist = 0.0;
    for (size_t i = 1; i < path.size(); i++) dist += points[path[i - 1]].distance_to(points[path[i]]);
    dist += points[path.back()].distance_to(points[path.front()]);
    return dist;
}

double TSP_2Opt::solve() {
    visualizer.render();
    visualizer.sleep(1000);
    randomize_path();
    visualizer.update_path(path);
    visualizer.sleep(1000);
    while(true){
        visualizer.update_path(path);
        visualizer.sleep(100);
        if (!perform_2opt_swap()) break;
    }
    visualizer.update_path(path, true);
    return tour_length();
}
