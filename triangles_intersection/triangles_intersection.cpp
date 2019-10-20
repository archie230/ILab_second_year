#include "triangles_intersection.hpp"

namespace triangles {

    bool nearly_equal(float a, float b){
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
    /////////////////
    //Point2D section
    /////////////////
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
    int orientation(const Point2D &p1, const Point2D &p2, const Point2D &p3) {
        float kross = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);

        if (nearly_equal(kross, 0))
            return colinear_o;

        return (kross > 0)? clock_o: counterclock_o;
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

    int Triangle::SetCounterClock() {
        int orient;
        if((orient = orientation(pts_[0], pts_[1], pts_[2])) == counterclock_o || (orient == colinear_o))
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

    std::istream &operator>>(std::istream &is, Triangle &tr) {
        for(int i = 0; i < 3; ++i)
            is >> tr.pts_[i].x >> tr.pts_[i].y;
        return is;
    }
    //////////////////
    //Clipping section
    //////////////////
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

    void CalcIntersection(const Triangle &T1, const Triangle &T2, std::vector<Point2D> &pts) {
        Point2D start,finish;
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

    std::ostream &operator<<(std::ostream &os, const Point2D &p) {
        os << "{" << p.x << ',' << p.y << "}";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const Polygon &p) {
        os << p.pts_.size() << " points polygon: \n";
        for(auto& elem :p.pts_)
            os << elem << ",";
        os << std::endl;
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const Triangle &p) {
        os << "triangles: \n";
        for(auto& elem :p.pts_)
            os << elem << ",";
        os << std::endl;
        return os;
    }

    bool operator==(const Polygon &left, const Polygon &right) {
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

    /////////////////
    //Polygon section
    /////////////////
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
