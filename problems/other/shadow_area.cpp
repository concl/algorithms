
#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1);

struct Point {
    double x;
    double y;

    Point() {}
    Point(double x, double y) : x(x), y(y) {}
};

struct Arc {
    double start;
    double end;

};

bool is_inside(Arc arc, double theta) {
    if (arc.start <= arc.end) {
        return theta >= arc.start && theta <= arc.end;
    } else {
        return theta >= arc.start || theta <= arc.end;
    }
}

Arc merge(Arc a, Arc b) {
    
    if (a.start > b.start) {
        swap(a, b);
    }
    if (a.end < b.end) {
        return {a.start, b.end};
    }
    return {a.start, b.end};

}


// Assumes that theta will not be too big or too negative
double normalize(double theta) {
    if (theta < 0) {
        return theta + 2 * PI;
    } else if (theta > 2 * PI) {
        return theta - 2 * PI;
    } else {
        return theta;
    }
}


class ShadowArea {

public:
    double area(vector<string> room) {

        Point light;
        pair<int,int> light_cell;

        // Posts
        vector<pair<int,int>> posts;

        // Find the light
        for (int ro = 0; ro < room.size(); ro++) {
            for (int co = 0; co < room[ro].size(); co++) {
                if (room[ro][co] == '*') {
                    light = Point(co + 0.5, ro + 0.5);
                    light_cell = {ro, co};
                } else if (room[ro][co] == '#') {
                    posts.push_back({ro, co});
                }
            }
        }

        // Sort by distance to light
        sort(posts.begin(), posts.end(), [&](pair<int,int> a, pair<int,int> b) {
            return sqrt(pow(a.first - light_cell.first, 2) + pow(a.second - light_cell.second, 2)) < sqrt(pow(b.first - light_cell.first, 2) + pow(b.second - light_cell.second, 2));
        });

        // Blocked arcs
        vector<Arc> arcs;

        // Area of light
        double area = 0;

        // Relevant segments are processed by considering the arcs that cast a shadow on them
        auto process_segment = [&] (Point p1, Point p2) {

            if (p1.)

        };
        
        // Find relevant line segments
        for (int i = 0; i < posts.size() - 1; i++) {
            
            // Same row or column, only one line segment of interest
            if (posts[i].first == light_cell.first) {

            } else if (posts[i].second == light_cell.second) {


            } else {
                if 

            }

        }

        double total_area = room.size() * room[0].size() - posts.size();
        return total_area - area;
    }


};