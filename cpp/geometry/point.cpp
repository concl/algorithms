/**
 * Author: concl
 * Status: Untested
 */

#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Implements a Point in 2D space with useful properties.
 * 
 * comment out the template statement and use "using T = double" inside the struct for convenience
 * 
 * @tparam T 
 */
template <typename T>
struct Point {


    T x, y;
    Point(T x, T y): x(x), y(y) { }
    Point operator+(const Point &other) const {
        return Point(x + other.x, y + other.y);
    }
    Point operator-(const Point &other) const {
        return Point(x - other.x, y - other.y);
    }
    Point operator*(const T &scalar) const {
        return Point(x * scalar, y * scalar);
    }

    /**
     * @brief returns the magnitude of the vector from the cross product between this point and another point
     * 
     * @param other 
     * @return Point 
     */
    Point cross(const Point &other) const {
        return x * other.y - y * other.x;
    }

    T dot(const Point &other) const {
        return x * other.x + y * other.y;
    }

};

