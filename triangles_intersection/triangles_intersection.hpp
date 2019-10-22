#pragma once

#include <vector>
#include <cstdint>
#include <cmath>
#include <limits>
#include <iostream>

/*
 * Template type T in all template objects in functions
 * should be able to:
 * 1) explicit cast to float
 * 2) float point arithmetic
 */

namespace triangles {
    const float TOLERANCE = 1e-4;

    static bool nearly_equal(float a, float b){
        float abs_a = fabs(a);
        float abs_b = fabs(b);
        float diff  = fabs(a - b);

        if(a == b){
            return true;
        }
            // a or b is zero or both are extremely close to zero
            // other implementations use float min normal instead of float min
        else if(a == 0 || b == 0 || diff < std::numeric_limits<float>::min()) {
            return diff < (TOLERANCE * std::numeric_limits<float>::min());
        }
            // use relative error
        else{
            return (diff / std::min((abs_a + abs_b), std::numeric_limits<float>::max())) < TOLERANCE;
        }
    }

// for ease of coding we will treat a 2D point and a 2D vector
// as the same

    template<typename T>
    struct Point2D {
        T x;
        T y;

        Point2D(T x = 0, T y = 0)
                :
                x(x),
                y(y) {}
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
    template<typename T>
    int orientation(const Point2D<T> &p1, const Point2D<T> &p2, const Point2D<T> &p3) {
        T kross = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);

        if (nearly_equal(static_cast<float>(kross), 0))
            return colinear_o;

        return (kross > 0)? clock_o: counterclock_o;
    }

// overloaded operators
    template<typename T>
    inline bool operator==(const Point2D<T> &left, const Point2D<T> &right) {
        return nearly_equal(static_cast<float>(left.x), static_cast<float>(right.x)) 
                    && nearly_equal(static_cast<float>(left.y), static_cast<float>(right.y));
    }

    template<typename T>
    inline bool operator!=(const Point2D<T> &left, const Point2D<T> &right) {
        return !(left == right);
    }

    template<typename T>
    inline Point2D<T> operator-(const Point2D<T> &left, const Point2D<T> &right) {
        return {left.x - right.x, left.y - right.y};
    }
// multiplying scalar ang vector scalar should be float point number
    template<typename T, typename V>
    inline Point2D<T> operator*(V scalar, const Point2D<T> &vec) {
        return {scalar * vec.x, scalar * vec.y};
    }

    template<typename T>
    inline Point2D<T> operator+(const Point2D<T> &left, const Point2D<T> &right) {
        return {left.x + right.x, left.y + right.y};
    }
// scalar vector multiplying
    template<typename T>
    inline float operator*(const Point2D<T> &left, const Point2D<T> &right) {
        return left.x * right.x + left.y * right.y;
    }

    template<typename T>
    struct Triangle {
        Point2D<T> pts_[3];
        Point2D<T> normals_[3];

        Triangle(const Point2D<T> &p1, const Point2D<T> &p2, const Point2D<T> &p3)
                :
                pts_{p1, p2, p3},
                normals_()
        {
            SetCounterClock();
            CalculateNormals();
        }

        Triangle()
                :
                pts_{{0,0}, {0,0}, {0,0}},
                normals_{{0,0}, {0,0}, {0,0}}
        {}

        // set counter clockwise order
        int SetCounterClock() {
            int orient;
            if((orient = orientation(pts_[0], pts_[1], pts_[2])) == counterclock_o || (orient == colinear_o))
                return orient;

            std::swap(pts_[0], pts_[2]);
            return counterclock_o;
        }

        // calculating internal normals
        void CalculateNormals() {
            Point2D<T> dirSide;
            for (int i = 0; i < 3; i++) {
                int j = (i+1) % 3;
                dirSide = pts_[j] - pts_[i];

                normals_[i].x = -dirSide.y;
                normals_[i].y =  dirSide.x;

                if (normals_[i] * dirSide < 0) {    // out normal
                    normals_[i] = -1 * normals_[i];
                }
            }
        }

        bool IsTrivial() const {
            return orientation(pts_[0], pts_[1], pts_[2]) == 0;
        }
    };

    template <typename T>
    std::istream &operator>>(std::istream &is, Triangle<T> &tr) {
        for(int i = 0; i < 3; ++i)
            is >> tr.pts_[i].x >> tr.pts_[i].y;
        return is;
    }

    template <typename T>
    struct Polygon {
        std::vector<Point2D<T>> pts_;

        explicit Polygon(const std::vector<Point2D<T>> &pts)
                :
                pts_(pts)
        {}

        explicit Polygon(uint32_t num)
                :
                pts_(std::vector<Point2D<T>>(num))
        {}

        Polygon() = default;
        
        T area() const{
            if(pts_.size() < 3)
                return 0;
            T area = 0;

            for(int i = 0; i < pts_.size(); ++i) {
                int j = (i + 1) % pts_.size();
                area += pts_[i].x*pts_[j].y-pts_[i].y*pts_[j].x;
            }

            return area / 2;
        }
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Point2D<T> &p) {
        os << "{" << p.x << ',' << p.y << "}";
        return os;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Polygon<T> &p) {
        os << p.pts_.size() << " points polygon: \n";
        for(auto& elem :p.pts_)
            os << elem << ",";
        os << std::endl;
        return os;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Triangle<T> &p) {
        os << "triangles: \n";
        for(auto& elem :p.pts_)
            os << elem << ",";
        os << std::endl;
        return os;
    }

    template <typename T>
    bool operator==(const Polygon<T> &left, const Polygon<T> &right) {
        if(left.pts_.size() != right.pts_.size())
            return false;
        for(int i = 0; i < left.pts_.size(); ++i)
            if(left.pts_[i] != right.pts_[i])
                return false;
        return true;
    }

    template <typename T>
    bool operator==(const Triangle<T> &left, const Triangle<T> &right) {
        for(int i = 0; i < 3; ++i)
            if(left.pts_[i] != right.pts_[i])
                return false;
        return true;
    }

//CYRUS-BECK CLIPPING ALGORITHM for segment + triangled window
/**
 * @param p1 first segment point
 * @param p2 second segment point
 * @param tr triangle window should have counter clock order
 * @param rp first clipped segment point
 * @param q second segment point
 * @return bool var which true if segment is visible at window else false
 */
    template <typename T>
    bool CBClip (const Point2D<T> &p1, const Point2D<T> &p2, const Triangle<T> &tr, Point2D<T> &start, Point2D<T> &finish) {
        T t,num,den;
        Point2D<T> dirV,F;          // vectors
        T t1 = 0.0;
        T t2 = 1.0;

        // compute direction vector
        dirV = p2 - p1;

        for (int i = 0; i < 3; ++i) {
            F = p1 - tr.pts_[i];

            num = tr.normals_[i] * F;
            den = tr.normals_[i] * dirV;

            if (nearly_equal(static_cast<float>(den), 0.0)) {          // Parallel or Point
                // parallel - if outside then forget the line; if inside then there are no
                // intersections with this side
                // but there may be with other edges, so in this case just keep going
                if (num < 0.0)
                    return false;   //   Parallel and outside or point (p1 == p2) and outside
            } else {
                t = -(num/den);
                if (den < 0.0) {
                    if(t < 0.0)
                        return false;
                    t2 = std::min(t, t2);
                } else {
                    if(t > 1)
                        return false;
                    t1 = std::max(t, t1);
                }
            }
        }

        if (t1 <= t2) {
            start   = p1 + t1 * dirV;
            finish  = p1 + t2 * dirV;
            return true;
        } else
            return false;
    }
/**
 *
 * @param T1 triangle should have counter clock order
 * @param T2 T2 triangle should have counter clock order
 * @param pts reference to vector(with size = 6) with future intersection points;
 */
    template <typename T>
    void CalcIntersection(const Triangle<T> &T1, const Triangle<T> &T2, std::vector<Point2D<T>> &pts) {
        Point2D<T> start,finish;
        for (int i = 0; i < 3; ++i) {
            int j = (i+1) % 3;
            if (CBClip(T1.pts_[i], T1.pts_[j], T2, start, finish)) {
                if (start != finish && ((i != 0 && pts[pts.size() - 1] != start) || i == 0))
                    pts.push_back(start);
                if ((i != 0 && pts[pts.size() - 1] != finish) || i == 0)
                    pts.push_back(finish);
            }
        }

        if ((pts.size() > 1) && (pts[pts.size()-1] == pts[0]))
            pts.resize(pts.size() - 1);
    }

/**
 * @param T1 triangle should have counter clock order
 * @param T2 triangle should have counter clock order
 * @param poly reference to polygon which would contain intersection polygon
 * @return number of intersection polygon points
 */
    template <typename T>
    int CalcIntersectionPolygon(const Triangle<T> &T1, const Triangle<T> &T2, Polygon<T> &suspect1) {
        if(T1.IsTrivial() || T2.IsTrivial()) {
            suspect1.pts_.resize(0);
            return 0;
        }

        if(suspect1.pts_.size() != 6)
            suspect1.pts_.resize(6);
        suspect1.pts_.resize(0);

        Polygon<T> suspect2(6);
        suspect2.pts_.resize(0);

        CalcIntersection(T1, T2, suspect1.pts_);
        CalcIntersection(T2, T1, suspect2.pts_);

        if(suspect2.pts_.size() > suspect1.pts_.size())
            std::swap(suspect1, suspect2);

        return suspect1.pts_.size();
    }
}