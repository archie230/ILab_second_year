#include "triangles_intersection.hpp"
#include <iostream>

using namespace triangles;

int main() {
    Triangle t1, t2;

    std::cout << "first triangle: \n";
    std::cin >> t1;
    if(!std::cin) {
        std::cerr << "bad input";
        exit(EXIT_FAILURE);
    }

    std::cout << "second triangle: \n";
    std::cin >> t2;
    if(!std::cin) {
        std::cerr << "bad input";
        exit(EXIT_FAILURE);
    }

    t1.SetCounterClock();
    t2.SetCounterClock();
    t1.CalculateNormals();
    t2.CalculateNormals();

    Polygon poly(6);
    CalcIntersectionPolygon(t1, t2, poly);

    std::cout << "\nintersection area: " << poly.area() << std::endl;

    return 0;
}