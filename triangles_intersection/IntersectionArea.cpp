#include "triangles_intersection.hpp"

using triangles::Triangle;
using triangles::operator>>;
using triangles::Polygon;
using triangles::CalcIntersectionPolygon;

const int invalid_input = -230;

int main() {
    Triangle<float> t1, t2;

    std::cin >> t1;
    if(!std::cin) {
        std::cout << invalid_input;
        exit(EXIT_FAILURE);
    }

    std::cin >> t2;
    if(!std::cin) {
        std::cerr << invalid_input;
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