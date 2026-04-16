/**
 * Author: concl
 * Status: Untested
 * Description: Returns the orientation of 3 points (clockwise, counterclockwise, or collinear)
 */

#include "point.hpp"
 
using P = Point<double>;

int orientation(P a, P b, P c) {
    double cross_product = (b - a).cross(c - a);
    if (cross_product > EPS) return 1; // counterclockwise
    if (cross_product < -EPS) return -1; // clockwise
    return 0; // collinear
}
 