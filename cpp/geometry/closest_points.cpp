/**
 * Author: concl
 * Status: Tested on CSES
 * Description: Finds the closest 2 points in 2D space given a group of points. O(n log n)
 * Returns the answer squared.
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
    ll x, y;
};

const ll INF = LLONG_MAX;

ll minimum_distance(vector<Point> pts) {
    
    sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
    });

    
    auto distance = [] (Point a, Point b) {
        ll x = a.x - b.x;
        ll y = a.y - b.y;
        return x * x + y * y; 
    };
    
    auto solve = [&] (vector<Point>& curr_pts, auto& solve) {
        if (curr_pts.size() <= 1) {
            return INF;
        }
        
        int n = curr_pts.size();
        
        vector<Point> set1(curr_pts.begin(), curr_pts.begin() + n / 2);
        vector<Point> set2(curr_pts.begin() + n / 2, curr_pts.end());
        
        ll dividing = curr_pts[n / 2].x;

        ll h1 = solve(set1, solve);
        ll h2 = solve(set2, solve);
        
        ll h = min(h1, h2);
        
        int i1 = 0;
        int i2 = 0;
        int i = 0;
        while (i < n) {
            if (i1 >= set1.size()) {
                curr_pts[i++] = set2[i2++];
            } else if (i2 >= set2.size()) {
                curr_pts[i++] = set1[i1++];
            } else {
                if (set1[i1].y <= set2[i2].y) {
                    curr_pts[i++] = set1[i1++];
                } else {
                    curr_pts[i++] = set2[i2++];
                }
            }
        }
        
        ll res = h;
        vector<Point> considerable;
        for (Point p : curr_pts) {
            ll dx = abs(p.x - dividing);
            if (dx * dx < h) {
                considerable.push_back(p);
            }
        }
        
        int j = 0;
        for (int i = 0; i < considerable.size(); i++) {
            
            while (j < considerable.size() 
                && (considerable[j].y - considerable[i].y) * (considerable[j].y - considerable[i].y) < h) {
                j++;
            }
            
            for (int k = i + 1; k < j; k++) {
                res = min(res, distance(considerable[i], considerable[k]));
            }
        }
        return res;
    };
    
    return solve(pts, solve);
}
