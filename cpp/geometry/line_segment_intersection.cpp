/**
 * Author: concl
 * Status: Tested on CSES
 * Description: Returns the intersection point of 2 line segments if it exists
 * If the line segments are collinear, returns the endpoints of the intersection segment
 */

#include "orientation.hpp"
#include "point.hpp"

using P = Point<double>;
using LineSegment = pair<P, P>;

vector<P> line_segment_intersection(LineSegment l1, LineSegment l2) {

    P a = l1.first;
    P b = l1.second;
    P c = l2.first;
    P d = l2.second;

    // if the segments are parallel
    if (orientation(a, b, c) == 0 && orientation(a, b, d) == 0) {
        // The line segments are collinear
        // Check if the segments overlap
        if (max(a.x, b.x) < min(c.x, d.x) || max(c.x, d.x) < min(a.x, b.x) ||
            max(a.y, b.y) < min(c.y, d.y) || max(c.y, d.y) < min(a.y, b.y)) {
            return {}; // No intersection
        }

        // The segments overlap; return the endpoints of the intersection segment
        if ((b - a).dot(d - c) < 0)
            swap(a, b);
        if ((c - a).dot(d - a) < 0)
            return {a, d};
        return {c, b};
    }

    if ((abs(orientation(a, b, c) + orientation(a, b, d)) <= 1) 
        && (abs(orientation(c, d, a) + orientation(c, d, b)) <= 1)) {
        // The line segments intersect at a single point
        // The parameter t is calculated as the cross between the lines drawn from a to c and d
        // since this quantity increases linearly as the line cd moves in the direction of ab
        // When cd is drawn at the end of ab, the cross of ac and ad is exactly the cross
        // between ab and cd.
        double t = (c - a).cross(d - c) / (b - a).cross(d - c);
        return {a + (b - a) * t};
    }

    return {}; // No intersection
}
