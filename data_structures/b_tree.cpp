
#include <bits/stdc++.h>

using namespace std;

const int NUM_KEYS = 8; // Maximum number of keys in a B-Tree node

// B-Tree Node
template <typename K, typename T>
class BTreeMapNode {
private:
    K keys[NUM_KEYS]; // Array of keys
    T values[NUM_KEYS]; // Array of values associated with the keys
    BTreeNode* children[NUM_KEYS + 1]; // Array of child pointers
    BTreeNode* parent; // Pointer to the parent node
    int num_keys; // Current number of keys in the node
    bool is_leaf; // Flag to check if the node is a leaf

public:
    BTreeNode(bool leaf = true) : parent(nullptr), num_keys(0), is_leaf(leaf) {
        fill(begin(keys), end(keys), T());
        fill(begin(children), end(children), nullptr);
    }
};

class 
