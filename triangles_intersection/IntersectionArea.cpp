#include "triangles_intersection.hpp"

using namespace triangles;

int main() {
    Triangle<float> t1, t2;

    std::cin >> t1;
    if(!std::cin) {
        std::cerr << "bad input";
        exit(EXIT_FAILURE);
    }

    std::cin >> t2;
    if(!std::cin) {
        std::cerr << "bad input";
        exit(EXIT_FAILURE);
    }

    t1.SetCounterClock();
    t2.SetCounterClock();
    t1.CalculateNormals();
    t2.CalculateNormals();

    Polygon<float> poly(6);
    CalcIntersectionPolygon(t1, t2, poly);
    std::cout << poly.area();

    return 0;
}