#include <iostream>
#include <vector>

using namespace std;

struct BPlusNode {
    vector<int> keys;
    vector<BPlusNode*> children;
    bool isLeaf;

    BPlusNode(bool leaf = false) {
        isLeaf = leaf;
    }
};

int findNextGreater(BPlusNode* root, int key) {
    if (!root) return -1; // В случае пустого дерева

    int index = 0;
    while (index < root->keys.size() && key > root->keys[index]) {
        index++;
    }

    if (index == root->keys.size()) {
        // If end of node 
        if (root->isLeaf) {
            // If curren note is leaf, then next greater key not found
            return -1;
        }
        // Recursively go to the last child and find next greater key
        return findNextGreater(root->children.back(), key);
    } else {
        // If our key is greater than current node, return it
        return root->keys[index];
    }
}

int main() {
    BPlusNode* root = new BPlusNode(true);
    root->keys = {1, 3, 5, 7, 9};

    cout << "Enter key to find its next greater: ";
    int key;
    cin >> key;

    int nextGreater = findNextGreater(root, key);
    if (nextGreater != -1) {
        cout << "Next greater key: " << nextGreater << endl;
    } else {
        cout << "Next greater key not found." << endl;
    }

    return 0;
}
