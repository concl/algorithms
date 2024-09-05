
// 120. Triangle
// Link: https://leetcode.com/problems/triangle/

#include <bits/stdc++.h>

using namespace std;

// Custom hash function for std::vector<int>
struct VectorHash {
    std::size_t operator()(const std::vector<int>& v) const {
        std::size_t hash = 0;
        std::hash<int> hasher;
        for (int i : v) {
            hash ^= hasher(i) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

// Custom equality function for std::vector<int>
struct VectorEqual {
    bool operator()(const std::vector<int>& v1, const std::vector<int>& v2) const {
        return v1 == v2;
    }
};


// // function returns the minimum path sum starting from the given position in the triangle
int check_path(auto& triangle, auto& cache, int row, int pos) {
    if (row >= triangle.size()) {
        return 0;
    } else if (cache.count({row,pos})) {
        return cache[{row,pos}];
    }
    // this will never cause an index out of bound error, since the next row is larger in size by 1.
    return cache[{row,pos}] = triangle[row][pos] + min(check_path(triangle, cache, row + 1, pos), check_path(triangle, cache, row + 1, pos + 1));
}

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        // minimum path starting from the top
        unordered_map<vector<int>, int, VectorHash, VectorEqual> cache;
        return check_path(triangle, cache, 0, 0);
    }
};
