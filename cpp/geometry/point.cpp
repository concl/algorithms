/**
 * Author: concl
 * Status: The cross product is tested
 */

#include <bits/stdc++.h>

using namespace std;

/**
 * Implements a Point in 2D space (2D vector) with useful properties.
 * 
 * comment out the template statement and use "using T = double" inside the struct for convenience
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
     * This quantity is positive if the other point is on the "left", 
     * and negative if the other point is on the "right".
     */
    T cross(const Point &other) const {
        return x * other.y - y * other.x;
    }

    T dot(const Point &other) const {
        return x * other.x + y * other.y;
    }
    
    Point perp() const {
        return Point(-y, x);
    }
    
    Point magnitude() const {
        return sqrt(x * x + y * y);
    }
    
    Point unit() const {
        T mag = magnitude();
        return Point(x / mag, y / mag);
    }
    
    friend ostream& operator<<(ostream &os, const Point &p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

