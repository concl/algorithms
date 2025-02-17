
#include <bits/stdc++.h>

using namespace std;

// Constants for PI and a small epsilon for floating-point comparisons
const double PI = acos(-1);
const double EPS = 1e-12;

// Checks if two doubles are approximately equal
bool eq(double a, double b) {
    return abs(a - b) < EPS;
}

// Simple 2D point struct
struct Point {
    double x;
    double y;

    Point() {}
    Point(double x, double y) : x(x), y(y) {}
};

// Represents an angular arc on a circle, from 'start' to 'end' (in radians)
struct Arc {
    double start;
    double end;

    Arc(double start, double end) : start(start), end(end) {}
};

// Checks if angle theta lies within the angular span of 'arc'
bool is_inside(const Arc &arc, const double theta) {
    // Special case: if arc covers the whole circle (start == end in this code)
    if (eq(arc.start, arc.end))
        return true;
    
    // If start < end, the arc is a simple interval [start, end]
    if (arc.start < arc.end)
        return (theta >= arc.start && theta <= arc.end);
    // Otherwise, the arc wraps around 2π (e.g., [start, 2π) and [0, end])
    else
        return (theta >= arc.start || theta <= arc.end);
}

// Normalizes an angle to the range [0, 2π)
double normalize(double angle) {
    angle = fmod(angle, 2 * PI);
    if (angle < 0)
        angle += 2 * PI;
    return angle;
}

// Returns the area of the triangle formed by p1, p2, p3
double triangle_area(Point p1, Point p2, Point p3) {
    return 0.5 * abs(p1.x * (p2.y - p3.y) +
                     p2.x * (p3.y - p1.y) +
                     p3.x * (p1.y - p2.y));
}

class ShadowArea {
public:
    // Given a representation of the room, returns the shadow area
    double area(vector<string> room) {

        int height = room.size();        // Number of rows
        int width = room[0].size();      // Number of columns

        Point light;                     // Coordinates of the light source
        pair<int, int> light_cell;       // Row/col of the light source cell

        vector<pair<int, int>> posts;    // Positions of posts ('#')

        // Identify the light source and collect all post positions
        for (int ro = 0; ro < room.size(); ro++) {
            for (int co = 0; co < room[ro].size(); co++) {
                if (room[ro][co] == '*') {
                    // Center the light in its cell (hence 0.5 offset)
                    light = Point(co + 0.5, height - ro - 0.5);
                    light_cell = {ro, co};
                } else if (room[ro][co] == '#') {
                    posts.push_back({ro, co});
                }
            }
        }

        // Sort posts by distance to the light source, nearest first
        sort(posts.begin(), posts.end(), [&](const pair<int, int>& a, const pair<int, int>& b) {
            double dxa = a.second - light_cell.second;
            double dya = a.first - light_cell.first;
            double dist_a = dxa * dxa + dya * dya;

            double dxb = b.second - light_cell.second;
            double dyb = b.first - light_cell.first;
            double dist_b = dxb * dxb + dyb * dyb;

            return dist_a < dist_b;
        });

        // List of arcs that are already illuminated (or blocked)
        vector<Arc> arcs;
        double illuminated_area = 0.0;

        // Helper function to merge arcs in 'arcs' so they don't overlap
        auto merge_arcs = [&] () {
            if (arcs.empty())
                return;

            // If arc.start >= arc.end, treat it as spanning past 2π
            for (int i = 0; i < (int)arcs.size(); i++) {
                if (arcs[i].start >= arcs[i].end) {
                    arcs[i].end += 2 * PI;
                }
            }

            // Sort arcs by starting angle
            sort(arcs.begin(), arcs.end(), [](const Arc &a, const Arc &b) {
                return a.start < b.start;
            });
            
            // Merge overlapping arcs
            vector<Arc> merged = {arcs[0]};
            for (int i = 1; i < (int)arcs.size(); i++) {
                if (merged.back().end >= arcs[i].start) {
                    merged.back().end = max(merged.back().end, arcs[i].end);
                } else {
                    merged.push_back(arcs[i]);
                }
            }

            // Check if the last arc loops around and merges with the first
            if (merged.size() > 1) {
                if (merged.back().end >= 2 * PI && 
                    normalize(merged.back().end) >= merged.front().start) {
                    merged.front().start = merged.back().start;
                    merged.pop_back();
                }
            }

            // If any arc covers the entire circle, store just a single arc [0,0]
            for (int i = 0; i < (int)merged.size(); i++) {
                if (merged[i].end - merged[i].start >= 2 * PI) {
                    arcs = {Arc(0,0)};
                    return;
                }
                merged[i].end = normalize(merged[i].end);
            }

            arcs = merged;
        };

        // Returns the intersection point of the line segment p1->p2 with
        // the ray from 'light' at angle 'theta'
        auto line_segment_intersection = [&](const Point& p1, const Point& p2, const double theta) {
            // Handle the vertical line case (avoid division by zero)
            if (abs(p2.x - p1.x) < EPS) {
                double x = p1.x;
                double slope2 = tan(theta);
                double intercept2 = light.y - slope2 * light.x;
                double y = slope2 * x + intercept2;
                return Point(x, y);
            } else {
                // General intersection calculation
                double slope = (p2.y - p1.y) / (p2.x - p1.x);
                double intercept = p1.y - slope * p1.x;

                double slope2 = tan(theta);
                double intercept2 = light.y - slope2 * light.x;

                double x = (intercept2 - intercept) / (slope - slope2);
                double y = slope * x + intercept;
                return Point(x, y);
            }
        };

        // Processes a line segment to see how much area it illuminates,
        // updates arcs and the illuminated_area
        auto process_segment = [&](const Point& p1, const Point& p2) {
            // Angles of segment endpoints relative to light
            double theta1 = atan2((p1.y - light.y), (p1.x - light.x));
            double theta2 = atan2((p2.y - light.y), (p2.x - light.x));
            if (theta1 < 0) theta1 += 2 * PI;
            if (theta2 < 0) theta2 += 2 * PI;

            // Copy of the segment endpoints, may be clipped
            Point m1 = p1;
            Point m2 = p2;
            Point m3 = light;

            // Check if the segment is entirely within an existing arc (blocked)
            // or else clip against the arcs
            for (auto& arc : arcs) {
                // If both angles are inside an existing arc, no new area is added
                if (is_inside(arc, theta1) && is_inside(arc, theta2)) {
                    // Check arc shape (normal or wrapping)
                    if (arc.start <= arc.end && theta1 < theta2) {
                        return;
                    } else if (arc.start >= arc.end) {
                        if (theta1 < theta2) {
                            if (theta1 >= arc.start && theta2 >= arc.start) {
                                return;
                            } else if (theta1 <= arc.end && theta2 <= arc.end ) {
                                return;
                            }
                        } else {
                            return;
                        }
                    }
                }

                // Clip if only one angle is within arc
                if (is_inside(arc, theta1)) {
                    m1 = line_segment_intersection(p1, p2, arc.end);
                }
                if (is_inside(arc, theta2)) {
                    m2 = line_segment_intersection(p1, p2, arc.start);
                }
            }

            // Add triangle area formed by the clipped segment
            illuminated_area += triangle_area(m1, m2, m3);

            // Add a new arc and merge overlapping arcs
            arcs.push_back({theta1, theta2});
            merge_arcs();
        };

        // Process each post's edges relative to the light source
        for (const auto& post : posts) {
            int ro = post.first;
            int co = post.second;

            // If this post is to the right of the light, process its left edge
            if (co > light_cell.second) {
                Point p1(co,     height - ro - 1);
                Point p2(co,     height - ro);
                process_segment(p1, p2);
            }

            // If this post is to the left of the light, process its right edge
            if (co < light_cell.second) {
                Point p1(co + 1, height - ro);
                Point p2(co + 1, height - ro - 1);
                process_segment(p1, p2);
            }

            // If this post is below the light, process its top edge
            if (ro > light_cell.first) {
                Point p1(co,     height - ro);
                Point p2(co + 1, height - ro);
                process_segment(p1, p2);
            }

            // If this post is above the light, process its bottom edge
            if (ro < light_cell.first) {
                Point p1(co + 1, height - ro - 1);
                Point p2(co,     height - ro - 1);
                process_segment(p1, p2);
            }
        }

        // Finally, process the room boundaries (walls)
        for (int i = 0; i < height; ++i) {
            process_segment(Point(0, i + 1), Point(0, i));
            process_segment(Point(width, i), Point(width, i + 1));
        }
        
        for (int i = 0; i < width; ++i) {
            process_segment(Point(i, 0), Point(i + 1, 0));
            process_segment(Point(i + 1, height), Point(i, height));
        }

        // Compute total floor area (excluding posts)
        int total_floor = height * width;
        for (const auto& row : room) {
            for (char c : row) {
                if (c == '#') total_floor--;
            }
        }

        // Shadowed area is total floor minus illuminated area
        return total_floor - illuminated_area;
    }
};


int main() {

    ShadowArea sa;

    vector<string> room =   {
        "###........#.##.....#.#.#....##.#...#..#....##..#.",
        ".....#........#..#...#..##....##..................",
        ".....#..#..#...........#....#.....#....#..........",
        "#....#.......#.......#...###..#.#.#..##.###..#....",
        ".............#....#......##.#.....#....#..........",
        "......#..................#.#.....#...#...#.....#.#",
        ".#............#.....#...#..#........#..##........#",
        "##..#...........#.#.##..........#....#.#......#...",
        ".#..#....#.#.....#........#......#.............##.",
        "#.#....#.##...........#####.....#.....##.........#",
        "...........#....*.....#...#....#.#...#.#.##..#.#..",
        ".##.#..#.##.............#...#..............######.",
        "..#........#...#......##.....##.#.......#....#..#.",
        "......###..............##..#....#..............#..",
        "#.....#.....#....#....#.#...##..###...........#...",
        ".#...#...#...#.....##.#.........#.#....#....#.....",
        ".....#..#..#.....###.....#.......#.....##........#",
        "#...#..#..#...#.............##.....#...#....#.#...",
        "...............................#...#.#.#...#.#....",
        "..#.#.#.#..................##.....#...#..#.....#..",
        "....#.#.#...............#.#####..##..#............",
        ".........#...#.#...........#..#...###.#.#....#.#.#",
        "..#..#...#..##......#.#.........#..#..#......#...#",
        "..#...........#......##...#.....##.##....##.....#.",
        "...#.#............##......#............#...#.#....",
        "#........#......#####......#........#..##......#..",
        "...#.#...#...##....#..#....##........##....#.#.#..",
        "#.......#........#..#.#.......#..#.#....#..#......",
        ".....#.##......#...##..............#..#...#......#",
        "....##...#......#.#......#..#.#...#....##....##...",
        ".............#....#.......#.#...#.#....#......#.#.",
        ".......#..#..............#..##.......#.#..#..##...",
        ".......###..#.#.....#..#.#.......###..........#...",
        "....#......#....#......#.##.....#..........#.#....",
        ".#.....#.......#.......#.......#..#....#.#........",
        ".......#.##.#......#........................#...#.",
        ".#..................#..#...............#..#...##..",
        "...###..#.......#...##.....#....##...#.........#..",
        "..#.#.......###..#.............#..#......##..#....",
        "...#....##.................#......#...............",
        "..#...#......##....##..##..#....#....##.#..#......",
        ".#.#..........#....#...#.#......#.....#..#........",
        "....#...#..................#........##..#.........",
        ".#...##...##...........#.#.#.....#.........###....",
        "#.#......#....#...........................#..#....",
        "##.....#.#.#..#.#..#............#.....##..#......#",
        "#....#.................#.#...#...#..##...##...#...",
        ".###...#...#.........#...###....#....##...#..#.#..",
        "..#...........#..#.#..#.......#.............#....#",
        "...............##.....#.....#........#.....#...#.."
    };
    cout << sa.area(room) << endl;

    // Arc arc1(Angle(1,1), Angle(-1, 1));
    // Angle theta = Angle(-1, -1);

    // cout << is_inside(arc1, theta) << endl;

    return 0;
}