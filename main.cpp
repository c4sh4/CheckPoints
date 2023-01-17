#include <iostream>
#include <vector>
#include <fstream>
//my includes
#include "Polygon.h"



int main() {
    int n = 0; // number of Vertexes of Polygon
    int n_dots = 0; // number of Dots
    std::cin >> n;
    std::vector<Vec> vertexes; // vector of vertexes
    std::vector<Vec> dots; // vector of dots for check
    for (int i = 0; i < n; ++i) {
        double x, y;
        std::cin >> x >> y;
        Vec v(x,y);
        vertexes.push_back(v);
    }
    Polygon pol(n, vertexes);
    std::cin >> n_dots;
    for (int j = 0; j < n_dots; ++j) {
        double x,y;
        std::cin >> x >> y;
        Vec v(x,y);
        dots.push_back(v);
    }
    std::vector<Vec> dots2;
    pol.Algorithm(pol, dots);
    return 0;
}
