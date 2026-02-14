
#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct Node {
    int8_t balance;
    Node* left;
    Node* right;
    T val;
    Node(const T& value, Node* l = nullptr, Node* r = nullptr, int8_t bal = 0)
        : val(value), left(l), right(r), balance(bal) {}
};

template <typename T>
class AVLTree {
    struct Node {
        int8_t balance;

        Node* left;
        Node* right;
        Node* parent;

        T val;
        Node(const T& value, Node* l = nullptr, Node* r = nullptr, int8_t bal = 0)
            : val(value), left(l), right(r), balance(bal) {}
    };

    Node* root;
public:
    AVLTree()
    : root(nullptr){}

    void insert(const T& value) {

        if (root == nullptr) {
            root = new Node(value);
            return;
        } else {
            
        }

    }


};
