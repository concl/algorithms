
#include <bits/stdc++.h>

using namespace std;


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
        
        // Find relevant line segments
        for (int i = 0; i < posts.size() - 1; i++) {
            
            if ()

        }




        return 0.0;
    }


};