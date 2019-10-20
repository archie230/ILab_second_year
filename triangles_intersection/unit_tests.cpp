#include <gtest/gtest.h>
#include "triangles_intersection.hpp"

using namespace triangles;

TEST(intersection, CBClip) {
    Point2D<float> r1, r2;

    Triangle<float> tr({0,1}, {0,0}, {1,0});
    Triangle<float> tr1({0.5, 1}, {0.5, -1}, {1.5,0});
    Triangle<float> tr2({1,1}, {-1, -1}, {1,-1});
    Triangle<float> tr3({0.5,1},{-1,-0.5},{0.5, -0.5});

    bool visible = false;

    // simple intersection
    visible = CBClip({-2, -2}, {2, 2}, tr, r1, r2);
    ASSERT_TRUE(visible && (r1 == Point2D<float>(0,0)) && (r2 == Point2D<float>(0.5, 0.5)));

    // segment overlap Triangle<float> side
    visible = CBClip({-2, 0}, {2, 0}, tr, r1, r2);
    ASSERT_TRUE(visible && (r1 == Point2D<float>(0,0) && (r2 == Point2D<float>(1, 0))));

    // segment outside
    visible = CBClip({-2, -4}, {-12, -20}, tr, r1, r2);
    ASSERT_FALSE(visible);

    // one part of segment inside
    visible = CBClip({0.1, 0.1}, {-1, -1}, tr, r1, r2);
    ASSERT_TRUE(visible && (r1 == Point2D<float>(0.1,0.1)) && (r2 == Point2D<float>(0, 0)));

    // segment is inside
    visible = CBClip({0.1, 0.1}, {0.2, 0.2}, tr, r1, r2);
    ASSERT_TRUE(visible && (r1 == Point2D<float>(0.1,0.1)) && (r2 == Point2D<float>(0.2, 0.2)));

    // segment touch Triangle<float>
    visible = CBClip({0.5, 0.5}, {3,3}, tr, r1, r2);
    ASSERT_TRUE(visible && (r1 == Point2D<float>(0.5, 0.5)) && (r2 == Point2D<float>(0.5, 0.5)));

    // segment intersect
    visible = CBClip({1,1}, {-1,-1}, tr1, r1, r2);
    ASSERT_TRUE(visible && (r1 == Point2D<float>(0.75, 0.75)) && (r2 == Point2D<float>(0.5, 0.5)));

    // one point inside
    visible = CBClip({0.5,1}, {0.5, -0.5}, tr2, r1, r2);
    ASSERT_TRUE(visible && (r1 == Point2D<float>(0.5, 0.5)) && (r2 == Point2D<float>(0.5, -0.5)));
}

TEST(intersection, intersection_poly) {
    Triangle<float> T1({1,1}, {-1, -1}, {1,-1});
    Triangle<float> T2({0.5, 1}, {0.5, -1}, {1.5,0});
    Triangle<float> T3({0,0}, {0,-2}, {2,0});
    Triangle<float> T4({0.5, 1}, {0.5, -1.2}, {1.5,0});
    Triangle<float> T5({0.5,1},{-1,-0.5},{0.5, -0.5});
    Triangle<float> T6({0,0}, {0,0}, {0,0});
    Triangle<float> T7({1,0}, {0,1}, {0,0});
    Triangle<float> T8({0.5, 0.5}, {0,1}, {0,0});

    Polygon<float> poly(6);

    // 6 point Polygon<float> intersection
    ASSERT_EQ(CalcIntersectionPolygon<float>(T1,T4,poly), 6);   // ??????
    ASSERT_EQ(poly, Polygon<float>({{0.75,0.75},{0.5,0.5},{0.5,-1},{0.666667,-1},{1,-0.6},{1,0.5}}));

    // 5 point Polygon<float> intersection
    ASSERT_EQ(CalcIntersectionPolygon<float>(T1,T2,poly), 5);
    ASSERT_EQ(poly, Polygon<float>({{0.75,0.75}, {0.5,0.5}, {0.5,-1}, {1,-0.5}, {1,0.5}}));

    // 4 point Polygon<float> intersection
    ASSERT_EQ(CalcIntersectionPolygon<float>(T1, T3, poly), 4);
    ASSERT_EQ(poly, Polygon<float>({{0,0}, {0,-1}, {1,-1}, {1,0}}));

    // 3 point Polygon<float> intersection
    ASSERT_EQ(CalcIntersectionPolygon<float>(T1, T5, poly), 3);
    ASSERT_EQ(poly, Polygon<float>({{-0.5,-0.5},{0.5,-0.5},{0.5,0.5}}));

    ASSERT_EQ(CalcIntersectionPolygon<float>(T7, T8, poly), 3);
    ASSERT_EQ(poly, Polygon<float>({{0.5,0.5},{0,1},{0,0}}));

    // trivial situations:
        // dot with Triangle<float>
        ASSERT_EQ(CalcIntersectionPolygon<float>(T3, T6, poly), 0);

        // line with Triangle<float>
}

TEST(polygon, CalcConvexPolygonArea) {
    Polygon<float> poly({{1,1}, {-1,1}, {-1,-1}, {1,-1}});
    ASSERT_EQ(poly.area(), 4);

    Polygon<float> poly1({{1,1}, {-1,1}, {-1,-1}});
    ASSERT_EQ(poly1.area(), 2);

    Polygon<float> poly2;
    ASSERT_EQ(poly2.area(), 0);

    Polygon<float> poly3({{0.75,0.75},{0.5,0.5},{0.5,-1},{0.666667,-1},{1,-0.6},{1,0.5}});
    ASSERT_TRUE(nearly_equal(0.745833, poly3.area()));
}

TEST(triangles, orinetation) {
    Triangle<float> tr;

    // linear order
    tr.pts_[0] = {-1,-1};
    tr.pts_[1] = {1,1};
    tr.pts_[2] = {0,0};
    tr.SetCounterClock();
    ASSERT_EQ(0, orientation(tr.pts_[0], tr.pts_[1], tr.pts_[2]));

    // clock order
    tr.pts_[0] = {0,0};
    tr.pts_[1] = {0,1};
    tr.pts_[2] = {1,1};
    tr.SetCounterClock();
    ASSERT_EQ(2, orientation(tr.pts_[0], tr.pts_[1], tr.pts_[2]));

    // counter clock order
    tr.pts_[0] = {0,0};
    tr.pts_[1] = {-1,-1};
    tr.pts_[2] = {1, 0};
    tr.SetCounterClock();
    ASSERT_EQ(2, orientation(tr.pts_[0], tr.pts_[1], tr.pts_[2]));

    tr.pts_[0] = {0.5, 0.5};
    tr.pts_[1] = {0,1};
    tr.pts_[2] = {0,0};
    ASSERT_EQ(counterclock_o, orientation(tr.pts_[0], tr.pts_[1], tr.pts_[2]));
}

TEST(points, orientation) {
    ASSERT_EQ(0, orientation<float>({-1,-1}, {1,1}, {0,0}));
    ASSERT_EQ(1, orientation<float>({0,0}, {0,1}, {1,1}));
    ASSERT_EQ(2, orientation<float>({0,0}, {-1, -1}, {1, 0}));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}