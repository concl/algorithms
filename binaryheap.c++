
#include <bits/stdc++.h>
#define ll long long

using namespace std;

namespace min_heap{

// written by chatgpt
void heapify(vector<int>& arr, int n, int i) {
    // start from the root node (i) and move to the largest (if exists)
    while (true) {
        int smallest = i;  
        int left = 2 * i + 1; 
        int right = 2 * i + 2; 

        // if left child is larger than root
        if (left < n && arr[left] < arr[smallest])
            smallest = left;

        // if right child is larger than largest so far
        if (right < n && arr[right] < arr[smallest])
            smallest = right;

        // if largest is not root
        if (smallest != i) {
            swap(arr[i], arr[smallest]);

            // move to the next node
            i = smallest;
        } else {
            break; // if the root is the largest, break the loop
        }
    }
}
// written by chatgpt
void build_heap(vector<int>& arr) {
    // start from the last internal node who has children
    for (int i = arr.size() / 2 - 1; i >= 0; --i)
        heapify(arr, arr.size(), i);
}

// takes a vector<int> which is assumed to be an implicit binary heap, and adds an element x while satisfying heap property.
void heappush(vector<int>& arr, int x) {
    // add the element to the back (first available position in level order (bfs order))
    int pos = arr.size();
    arr.push_back(x);

    // swap with parent repeatedly if its smaller
    while (pos != 0 && arr[pos] < arr[(pos - 1) >> 1]) {
        swap(arr[pos],arr[(pos - 1) >> 1]);
        pos--;
        pos >>= 1;
    }
}

// takes a vector<int> which is an implicit binary heap and removes the smallest element, while keeping heap property.
int heappop(vector<int>& arr) {

    // output is the first element of the heap
    int out = arr[0];

    // pop out the back element (last element in level order (bfs order))
    int sift = arr.back();
    arr.pop_back();

    // set the front to be the back element, and sift it down, keeping heap property.
    arr[0] = sift;
    int pos = 0;
    int n = arr.size();
    
    while (true) {
        int smallest = pos;  
        int left = 2 * pos + 1; 
        int right = 2 * pos + 2; 

        // if left child is larger than root
        if (left < n && arr[left] < arr[smallest])
            smallest = left;

        // if right child is larger than largest so far
        if (right < n && arr[right] < arr[smallest])
            smallest = right;

        // if largest is not root
        if (smallest != pos) {
            swap(arr[pos], arr[smallest]);

            // move to the next node
            pos = smallest;
        } else {
            break; // if the root is the largest, break the loop
        }
    }
    return out;
}

}


namespace max_heap{

void heapify(vector<int>& arr, int n, int i) {
    // Start from the current node (i) and move to the largest (if exists)
    while (true) {
        int largest = i;  
        int left = 2 * i + 1; 
        int right = 2 * i + 2; 

        // If left child is larger than root
        if (left < n && arr[left] > arr[largest])
            largest = left;

        // If right child is larger than largest so far
        if (right < n && arr[right] > arr[largest])
            largest = right;

        // If largest is not root
        if (largest != i) {
            swap(arr[i], arr[largest]);

            // Move to the next node
            i = largest;
        } else {
            break; // If the root is the largest, break the loop
        }
    }
}

void build_heap(vector<int>& arr) {
    // Start from the last internal node who has children
    for (int i = arr.size() / 2 - 1; i >= 0; --i)
        heapify(arr, arr.size(), i);
}

void heappush(vector<int>& arr, int x) {
    // Add the element to the back (first available position in level order (bfs order))
    int pos = arr.size();
    arr.push_back(x);

    // Swap with parent repeatedly if it's larger
    while (pos != 0 && arr[pos] > arr[(pos - 1) / 2]) {
        swap(arr[pos], arr[(pos - 1) / 2]);
        pos = (pos - 1) / 2;
    }
}

int heappop(vector<int>& arr) {
    // Output is the first element of the heap
    int out = arr[0];

    // Pop out the back element (last element in level order (bfs order))
    int sift = arr.back();
    arr.pop_back();

    // Set the front to be the back element, and sift it down, keeping heap property.
    if (!arr.empty()) { // Important check to avoid accessing an empty vector
        arr[0] = sift;
        heapify(arr, arr.size(), 0);
    }

    return out;
}

}


using namespace min_heap;

// sorts elements in ascending order (not completely optimized)
void heapSort(vector<int>& arr) {
    vector<int> heap = arr;
    build_heap(heap);

    // Pop all elements from the heap into arr
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = heappop(heap);
    }
}

void testBuildHeap() {
    vector<int> arr = {3, 2, 5, 1, 4};
    build_heap(arr);

    // Check if every parent node is less than or equal to its child nodes
    for (int i = 0; i < arr.size(); ++i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < arr.size()) {
            assert(arr[i] <= arr[left]);
        }

        if (right < arr.size()) {
            assert(arr[i] <= arr[right]);
        }
    }

    cout << "build_heap passed all tests.\n";
}

void testHeappush() {
    vector<int> arr;

    // Push elements and check if the smallest is always at the root
    for (int i = 5; i > 0; --i) {
        heappush(arr, i);
        assert(arr[0] == i);
    }

    cout << "heappush passed all tests.\n";
}

void testHeappop() {
    vector<int> arr;

    // Build a heap
    for (int i = 1; i <= 5; ++i) {
        heappush(arr, i);
    }

    // Pop elements and check if the smallest is always returned
    for (int i = 1; i <= 5; ++i) {
        assert(heappop(arr) == i);
    }

    cout << "heappop passed all tests.\n";
}

void testHeapSort() {
    // Test with several different vectors
    vector<vector<int>> testCases = {
        {},
        {1},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {-3, -1, -2, -5, -4},
        {2, 2, 2, 2, 2},
    };

    for (vector<int>& arr : testCases) {
        vector<int> sorted(arr);
        sort(sorted.begin(), sorted.end());

        heapSort(arr);

        // Check if the array is sorted correctly
        assert(arr == sorted);
    }

    cout << "heapSort passed all tests.\n";
}


int main() {
    testBuildHeap();
    testHeappush();
    testHeappop();
    testHeapSort();

    return 0;
}
