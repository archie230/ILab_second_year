#include <gtest/gtest.h>
#define _DEBUG
#include "triangles_intersection.hpp"

using namespace triangles;

TEST(intersection, CBClip) {
    Point2D r1, r2;

    Triangle tr({0,1}, {0,0}, {1,0});
    Triangle tr1({0.5, 1}, {0.5, -1}, {1.5,0});
    Triangle tr2({1,1}, {-1, -1}, {1,-1});
    Triangle tr3({0.5,1},{-1,-0.5},{0.5, -0.5});

    bool visible = false;

    // simple intersection
    visible = CBClip({-2, -2}, {2, 2}, tr, r1, r2);
    ASSERT_TRUE(visible && (r1 == Point2D(0,0)) && (r2 == Point2D(0.5, 0.5)));

    // segment overlap triangle side
    visible = CBClip({-2, 0}, {2, 0}, tr, r1, r2);
    ASSERT_TRUE(visible && (r1 == Point2D(0,0) && (r2 == Point2D(1, 0))));

    // segment outside
    visible = CBClip({-2, -4}, {-12, -20}, tr, r1, r2);
    ASSERT_FALSE(visible);

    // one part of segment inside
    visible = CBClip({0.1, 0.1}, {-1, -1}, tr, r1, r2);
    ASSERT_TRUE(visible && (r1 == Point2D(0.1,0.1)) && (r2 == Point2D(0, 0)));

    // segment is inside
    visible = CBClip({0.1, 0.1}, {0.2, 0.2}, tr, r1, r2);
    ASSERT_TRUE(visible && (r1 == Point2D(0.1,0.1)) && (r2 == Point2D(0.2, 0.2)));

    // segment touch triangle
    visible = CBClip({0.5, 0.5}, {3,3}, tr, r1, r2);
    ASSERT_TRUE(visible && (r1 == Point2D(0.5, 0.5)) && (r2 == Point2D(0.5, 0.5)));

    // segment intersect
    visible = CBClip({1,1}, {-1,-1}, tr1, r1, r2);
    ASSERT_TRUE(visible && (r1 == Point2D(0.75, 0.75)) && (r2 == Point2D(0.5, 0.5)));

    // one point inside
    visible = CBClip({0.5,1}, {0.5, -0.5}, tr2, r1, r2);
    ASSERT_TRUE(visible && (r1 == Point2D(0.5, 0.5)) && (r2 == Point2D(0.5, -0.5)));
}

TEST(intersection, intersection_poly) {
    Triangle T1({1,1}, {-1, -1}, {1,-1});
    Triangle T2({0.5, 1}, {0.5, -1}, {1.5,0});
    Triangle T3({0,0}, {0,-2}, {2,0});
    Triangle T4({0.5, 1}, {0.5, -1.2}, {1.5,0});
    Triangle T5({0.5,1},{-1,-0.5},{0.5, -0.5});
    Triangle T6({0,0}, {0,0}, {0,0});

    Polygon poly(6);

    // 6 point polygon intersection
    ASSERT_EQ(CalcIntersectionPolygon(T1,T4,poly), 6);
    ASSERT_EQ(poly, Polygon({{0.75,0.75},{0.5,0.5},{0.5,-1},{0.666667,-1},{1,-0.6},{1,0.5}}));

    // 5 point polygon intersection
    ASSERT_EQ(CalcIntersectionPolygon(T1,T2,poly), 5);
    ASSERT_EQ(poly, Polygon({{0.75,0.75}, {0.5,0.5}, {0.5,-1}, {1,-0.5}, {1,0.5}}));

    // 4 point polygon intersection
    ASSERT_EQ(CalcIntersectionPolygon(T1, T3, poly), 4);
    ASSERT_EQ(poly, Polygon({{0,0}, {0,-1}, {1,-1}, {1,0}}));

    // 3 point polygon intersection
    ASSERT_EQ(CalcIntersectionPolygon(T1, T5, poly), 3);
    ASSERT_EQ(poly, Polygon({{-0.5,-0.5},{0.5,-0.5},{0.5,0.5}}));

    // trivial situations:

        // dot with triangle
        ASSERT_EQ(CalcIntersectionPolygon(T3, T6, poly), 0);

        // line with triangle
}

TEST(polygon, CalcConvexPolygonArea) {
    Polygon poly({{1,1}, {-1,1}, {-1,-1}, {1,-1}});
    ASSERT_EQ(poly.area(), 4);

    Polygon poly1({{1,1}, {-1,1}, {-1,-1}});
    ASSERT_EQ(poly1.area(), 2);

    Polygon poly2;
    ASSERT_EQ(poly2.area(), 0);

    Polygon poly3({{0.75,0.75},{0.5,0.5},{0.5,-1},{0.666667,-1},{1,-0.6},{1,0.5}});
    ASSERT_TRUE(nearly_equal(0.745833, poly3.area()));
}

TEST(triangles, orinetation) {
    Triangle tr;

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
}

TEST(points, orientation) {
    ASSERT_EQ(0, orientation({-1,-1}, {1,1}, {0,0}));
    ASSERT_EQ(1, orientation({0,0}, {0,1}, {1,1}));
    ASSERT_EQ(2, orientation({0,0}, {-1, -1}, {1, 0}));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}