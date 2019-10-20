#pragma once

#include <vector>
#include <cstdint>
#include <cmath>
#include <limits>
#include <iostream>

namespace triangles {
    const float TOLERANCE = 1e-4;
    bool nearly_equal(float a, float b);
// for ease of coding we will treat a 2D point and a 2D vector
// as the same
    struct Point2D {
        float x;
        float y;

        Point2D(float x = 0, float y = 0)
                :
                x(x),
                y(y) {}
    };

    enum order {
        colinear_o     = 0,
        clock_o        = 1,
        counterclock_o = 2
    };

    int orientation(const Point2D& p1, const Point2D& p2, const Point2D& p3);

// overloaded operators
    inline bool operator==(const Point2D &left, const Point2D &right) {
        return nearly_equal(left.x, right.x) && nearly_equal(left.y, right.y);
    }

    inline bool operator!=(const Point2D &left, const Point2D &right) {
        return !(left == right);
    }

    inline Point2D operator-(const Point2D &left, const Point2D &right) {
        return {left.x - right.x, left.y - right.y};
    }
// multiplying scalar ang vector
    inline Point2D operator*(float scalar, const Point2D &vec) {
        return {scalar * vec.x, scalar * vec.y};
    }

    inline Point2D operator+(const Point2D &left, const Point2D &right) {
        return {left.x + right.x, left.y + right.y};
    }
// scalar vector multiplying
    inline float operator*(const Point2D &left, const Point2D &right) {
        return left.x * right.x + left.y * right.y;
    }

    struct Triangle {
        Point2D pts_[3];
        Point2D normals_[3];

        Triangle(const Point2D& p1, const Point2D& p2, const Point2D& p3);

        Triangle()
                :
                pts_{{0,0}, {0,0}, {0,0}},
                normals_{{0,0}, {0,0}, {0,0}}
        {}

        // set counter clockwise order
        int SetCounterClock();

        // calculating internal normals
        void CalculateNormals();

        bool IsTrivial() const {
            return orientation(pts_[0], pts_[1], pts_[2]) == 0;
        }
    };

    std::istream&  operator>> (std::istream& is, Triangle& tr);

    struct Polygon {
        std::vector<Point2D> pts_;

        explicit Polygon(const std::vector<Point2D>& pts)
                :
                pts_(pts)
        {}

        explicit Polygon(uint32_t num)
                :
                pts_(std::vector<Point2D>(num))
        {}

        Polygon() = default;


        float area();
    };

    std::ostream& operator << (std::ostream&, const Point2D&);

    std::ostream& operator << (std::ostream&, const Polygon&);

    std::ostream& operator << (std::ostream&, const Triangle&);

    bool operator == (const Polygon&, const Polygon&);

    bool operator == (const Triangle&, const Triangle&);

//CYRUS-BECK CLIPPING ALGORITHM for segment + triangled window
/**
 * @param p1 first segment point
 * @param p2 second segment point
 * @param tr triangle window should have counter clock order
 * @param rp first clipped segment point
 * @param q second segment point
 * @return bool var which true if segment is visible at window else false
 */
    bool CBClip (const Point2D& p1, const Point2D& p2, const Triangle& tr, Point2D& start, Point2D& finish);
/**
 *
 * @param T1 triangle should have counter clock order
 * @param T2 T2 triangle should have counter clock order
 * @param pts reference to vector(with size = 6) with future intersection points;
 */
    void CalcIntersection(const Triangle& T1, const Triangle& T2, std::vector<Point2D>& pts);

/**
 * @param T1 triangle should have counter clock order
 * @param T2 triangle should have counter clock order
 * @param poly reference to polygon which would contain intersection polygon
 * @return number of intersection polygon points
 */
    int CalcIntersectionPolygon(const Triangle& T1, const Triangle& T2, Polygon& suspect1);
}
