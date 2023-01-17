#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <thread>
//my includes
#include "Polygon.h"


int main() {
    //std::clock_t c_start = std::clock();
    //auto t_start = std::chrono::high_resolution_clock::now();
    int n = 0; // number of Vertexes of Polygon
    int n_dots = 0; // number of Dots
    std::cin >> n;
    std::vector<Vec> vertexes; // vector of vertexes
    std::vector<Vec> dots; // vector of dots for check
    for (int i = 0; i < n; ++i) {
        double x, y;
        std::cin >> x >> y;
        Vec v(x, y);
        vertexes.push_back(v);
    }
    Polygon pol(n, vertexes);
    std::cin >> n_dots;
    for (int j = 0; j < n_dots; ++j) {
        double x, y;
        std::cin >> x >> y;
        Vec v(x, y);
        dots.push_back(v);
    }
    std::vector<Vec> dots2;

    pol.Algorithm(pol, dots);

    //std::clock_t c_end = std::clock();
    //auto t_end = std::chrono::high_resolution_clock::now();
    /*
    std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
              << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n"
              << "Wall clock time passed: "
              << std::chrono::duration<double, std::milli>(t_end-t_start).count()
              << " ms\n";
    */
    return 0;
}
