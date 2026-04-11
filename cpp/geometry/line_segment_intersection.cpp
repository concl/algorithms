/**
 * Author: concl
 * Status: Untested
 * Description: Returns the intersection point of 2 line segments if it exists
 * If the line segments are collinear, returns the endpoints of the intersection segment
 */

#include "point.cpp"
#include "orientation.cpp"

using P = Point<double>;
using LineSegment = pair<P, P>;

vector<P> line_segment_intersection(LineSegment l1, LineSegment l2) {
    
    P a = l1.first;
    P b = l1.second;
    P c = l2.first;
    P d = l2.second;
    
    if (orientation(a, b, c) == -orientation(a, b, d) && orientation(c, d, a) == -orientation(c, d, b)) {
        // The line segments intersect at a single point
        double t = (c - a).cross(d - c) / (b - a).cross(d - c);
        return {a + (b - a) * t};
    }
    
}
