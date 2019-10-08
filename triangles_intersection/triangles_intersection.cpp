#include "triangles_intersection.hpp"

namespace triangles {

    const float TOLERANCE = 1e-4;
    
    bool nearly_equal(float a, float b){
        float abs_a = fabs(a);
        float abs_b = fabs(b);
        float diff = fabs(a - b);

        if(a == b){
            return true;
        }
            // a or b is zero or both are extremely close to zero
            // other implementations use float min normal instead of float min
        else if(a == 0 || b == 0 || diff < std::numeric_limits<float>::min()){
            return diff < (TOLERANCE * std::numeric_limits<float>::min());
        }
            // use relative error
        else{
            return (diff / std::min((abs_a + abs_b), std::numeric_limits<float>::max())) < TOLERANCE;
        }
    }
    /////////////////
    //Point2D section
    /////////////////
    Point2D::Point2D(float x, float y)
            :
            x(x),
            y(y) {}

    int orientation(const Point2D &p1, const Point2D &p2, const Point2D &p3) {
        int val = (p2.y - p1.y) * (p3.x - p2.x) -
                  (p2.x - p1.x) * (p3.y - p2.y);

        if (val == 0) return colinear_o;

        return (val > 0)? clock_o: counterclock_o;
    }

    bool operator==(const Point2D &left, const Point2D &right) {
        return nearly_equal(left.x, right.x) && nearly_equal(left.y, right.y);
    }

    bool operator!=(const Point2D &left, const Point2D &right) {
        return !(left == right);
    }

    Point2D operator-(const Point2D &left, const Point2D &right) {
        return {left.x - right.x, left.y - right.y};
    }

    Point2D operator*(float scalar, const Point2D &vec) {
        return {scalar * vec.x, scalar * vec.y};
    }

    Point2D operator+(const Point2D &left, const Point2D &right) {
        return {left.x + right.x, left.y + right.y};
    }

    float operator*(const Point2D &left, const Point2D &right) {
        return left.x * right.x + left.y * right.y;
    }
    //////////////////
    //Triangle section
    //////////////////
    Triangle::Triangle(const Point2D &p1, const Point2D &p2, const Point2D &p3)
            :
            pts_{p1, p2, p3},
            normals_()
    {
        SetCounterClock();
        CalculateNormals();
    }

    Triangle::Triangle()
            :
            pts_{{0,0}, {0,0}, {0,0}},
            normals_{{0,0}, {0,0}, {0,0}}
    {}

    int Triangle::SetCounterClock() {
        int orient;
        if((orient = orientation(pts_[0], pts_[1], pts_[2])) == 2 || (orient == 0))
            return orient;

        std::swap(pts_[0], pts_[2]);
        return counterclock_o;
    }

    void Triangle::CalculateNormals() {
        Point2D dirSide;
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

    bool Triangle::IsTrivial() const {
        return orientation(pts_[0], pts_[1], pts_[2]) == 0;
    }

    std::istream &operator>>(std::istream &is, Triangle &tr) {
        for(int i = 0; i < 3; ++i)
            is >> tr.pts_[i].x >> tr.pts_[i].y;
    }
    //////////////////
    //Clipping section
    //////////////////
#define MIN(a,b) a<b ? a:b
#define MAX(a,b) a>b ? a:b
    bool CBClip(const Point2D &p1, const Point2D &p2, const Triangle &tr, Point2D &start, Point2D &finish) {
        float t,num,den;
        Point2D dirV,F;          // vectors
        float t1 = 0.0;
        float t2 = 1.0;

        // compute direction vector
        dirV = p2 - p1;

        for (int i = 0; i < 3; ++i) {
            F = p1 - tr.pts_[i];

            num = tr.normals_[i] * F;
            den = tr.normals_[i] * dirV;

            if (nearly_equal(den, 0.0)) {          // Parallel or Point
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
                    t2 = MIN(t, t2);
                } else {
                    if(t > 1)
                        return false;
                    t1 = MAX(t, t1);
                }
            }
        }

        return ({ bool visible;
            if (t1 <= t2) {
                start   = p1 + t1 * dirV;
                finish  = p1 + t2 * dirV;
                visible = true;
            } else visible = false;
            visible;});
    }

    void CalcIntersection(const Triangle &T1, const Triangle &T2, std::vector<Point2D> &pts) {
        Point2D start,finish;
        for (int i = 0; i < 3; ++i) {
            int j = (i+1) % 3;
            if (CBClip(T1.pts_[i], T1.pts_[j], T2, start, finish)) {
                if (start != finish)
                    if (pts[pts.size() - 1] != start)
                        pts.push_back(start);
                pts.push_back(finish);
            }
        }

        if ((pts.size() > 1) && (pts[pts.size()-1] == pts[0]))
            pts.resize(pts.size() - 1);
    }

    int CalcIntersectionPolygon(const Triangle &T1, const Triangle &T2, Polygon &suspect1) {
        if(T1.IsTrivial() || T2.IsTrivial()) {
            suspect1.pts_.resize(0);
            return 0;
        }

        if(suspect1.pts_.size() != 6)
            suspect1.pts_.resize(6);
        suspect1.pts_.resize(0);

        Polygon suspect2(6);
        suspect2.pts_.resize(0);

        CalcIntersection(T1, T2, suspect1.pts_);
        CalcIntersection(T2, T1, suspect2.pts_);

        if(suspect2.pts_.size() > suspect1.pts_.size())
            std::swap(suspect1, suspect2);

        return suspect1.pts_.size();
    }

    /////////////////
    //Polygon section
    /////////////////
    Polygon::Polygon(const std::vector<Point2D> &pts)
            :
            pts_(pts)
    {}

    Polygon::Polygon(uint32_t num)
            :
            pts_(std::move(std::vector<Point2D>(num)))
    {}

    float Polygon::area() {
        if(pts_.size() < 3)
            return 0;
        float area = 0;

        for(int i = 0; i < pts_.size(); ++i) {
            int j = (i + 1) % pts_.size();
            area += pts_[i].x*pts_[j].y-pts_[i].y*pts_[j].x;
        }

        return area / 2;
    }
}
