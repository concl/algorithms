
#include <bits/stdc++.h>

using namespace std;

const int M = 8; // Maximum number of children for each B-Tree node

// B-Tree Node
template <typename K, typename T>
class BTreeMapNode {
private:
    vector<K> keys; // Vector to store keys
    vector<T> values; // Vector to store values corresponding to keys
    vector<BTreeMapNode<K, T>*> children; // Pointers to child nodes
    bool is_leaf; // Flag to check if the node is a leaf

};

template <typename K, typename V>
class BTreeMap {

private:

    BTreeMapNode<K, V>* root; // Pointer to the root node of the B-Tree
    int min_keys; // Minimum number of keys in a non-root node

    void splitChild(BTreeMapNode<K, V>* parent, int index) {
        // Implementation of child splitting logic
    }

    void insertNonFull(BTreeMapNode<K, V>* node, const K& key, const V& value) {
        // Implementation of inserting a key-value pair into a non-full node
    }