#include <iostream>
#include <vector>
using namespace std;

//Struct to represent a point
struct Point {
    double x, y;
};

//Get points from user input
vector<Point> getPointsFromUser(){
    int n;
    cout << "How many points do you want to enter: ";
    cin >> n;
    vector<Point> points(n);
    for(int i = 0; i < n; i++) {
        cout << "Enter X coordinate for point " << i + 1 << ": ";
        cin >> points[i].x;
        cout << "Enter Y coordinate for point " << i + 1 << ": ";
        cin >> points[i].y;
    }
    return points;
}

//Print all points
void printPoints(const std::vector<Point>& points) {
    std::cout << "\nStored Points:\n";
    for (size_t i = 0; i < points.size(); i++) {
        std::cout << "Point " << i + 1 << ": (" << points[i].x << ", " << points[i].y << ")\n";
    }
}

//Main function
int main() {
    std::vector<Point> points = getPointsFromUser();
    printPoints(points);
    return 0;
}