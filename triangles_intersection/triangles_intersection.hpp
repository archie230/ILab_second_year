#pragma once
#include <vector>
#include <cstdint>
#include <cmath>
#include <limits>
#include <iostream>

namespace triangles {
// for ease of coding we will treat a 2D point and a 2D vector
// as the same
    struct Point2D {
        float x;
        float y;

        Point2D(float x = 0, float y = 0);

        ~Point2D() = default;
    };

    enum order {
        colinear_o     = 0,
        clock_o        = 1,
        counterclock_o = 2
    };

// Slope of line segment (p1, p2): σ = (y2 - y1)/(x2 - x1)
// Slope of line segment (p2, p3): τ = (y3 - y2)/(x3 - x2)
//
// If  σ > τ, the orientation is clockwise (right turn)
//
// Using above values of σ and τ, we can conclude that,
// the orientation depends on sign of  below expression:
//
// (y2 - y1)*(x3 - x2) - (y3 - y2)*(x2 - x1)

// Above expression is negative when σ < τ, i.e.,  counterclockwise
    int orientation(const Point2D& p1, const Point2D& p2, const Point2D& p3);

// overloaded operators
    bool operator== (const Point2D& left, const Point2D& right);
    bool operator!= (const Point2D& left, const Point2D& right);
// math operations with Point2Ds(vectors)
// vector2D - vector2D
    Point2D operator- (const Point2D& left, const Point2D& right);
// scalar * vector2D
    Point2D operator* (float scalar, const Point2D& vec);
// vector2D + vector2D
    Point2D operator+ (const Point2D& left, const Point2D& right);
// sqal(vector2D,vector2D)
    float operator* (const Point2D& left, const Point2D& right);

    struct Triangle {
        Point2D pts_[3];
        Point2D normals_[3];

        Triangle(const Point2D& p1, const Point2D& p2, const Point2D& p3);

        Triangle();

        ~Triangle() = default;

        // set counter clockwise order
        int SetCounterClock();

        // calculating internal normals
        void CalculateNormals();

        bool IsTrivial() const;
    };

    std::istream&  operator >> (std::istream& is, Triangle& tr);

    struct Polygon {
        std::vector<Point2D> pts_;

        explicit Polygon(const std::vector<Point2D>& pts);

        explicit Polygon(uint32_t num);

        Polygon() = default;

        ~Polygon() = default;

        float area();
    };

#ifdef _DEBUG
    std::ostream& operator << (std::ostream& os,const Point2D& p) {
        os << "{" << p.x << ',' << p.y << "}";
        return os;
    }

    std::ostream& operator << (std::ostream& os,const Polygon& p) {
        os << p.pts_.size() << " points polygon: \n";
        for(auto& elem :p.pts_)
            os << elem << ",";
        os << std::endl;
        return os;
    }

    std::ostream& operator << (std::ostream& os,const Triangle& p) {
        os << "triangles: \n";
        for(auto& elem :p.pts_)
            os << elem << ",";
        os << std::endl;
        return os;
    }

    bool operator==(const Polygon& left, const Polygon& right) {
        if(left.pts_.size() != right.pts_.size())
            return false;
        for(int i = 0; i < left.pts_.size(); ++i)
            if(left.pts_[i] != right.pts_[i])
                return false;
        return true;
    }

    bool operator==(const Triangle& left, const Triangle& right) {
        for(int i = 0; i < 3; ++i)
            if(left.pts_[i] != right.pts_[i])
                return false;
        return true;
    }
#endif

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