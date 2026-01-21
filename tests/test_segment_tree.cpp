
#include "../data_structures/segment_tree.h"
#include <cassert>

void test_segment_tree() {
    // Example test cases for SegmentTree
    vector<int> array = {1, 2, 3, 4, 5};
    SegmentTree<int> st(array, 0, [](int a, int b) { return a + b; });

    assert(st.query(0, 5) == 15); // Sum of entire array
    assert(st.query(1, 4) == 9); // Sum from index 1 to 3
    st.update(2, 10); // Update index 2 to value 10
    assert(st.query(1, 4) == 16); // Sum after update

    for (int length = 1; length <= 100; length++) {
        vector<int> test_array(length, 1);
        SegmentTree<int> test_st(test_array, 0, [](int a, int b) { return a + b; });

        // test range queries
        for (int start = 0; start < length; start++) {
            for (int end = start; end < length; end++) {
                int expected_sum = end - start + 1;
                assert(test_st.query(start, end + 1) == expected_sum);
            }
        }
    }

    cout << "All tests passed!" << endl;
}

int main() {
    test_segment_tree();

    return 0;
}

