#include <iostream>

// Структура для узла в левостороннем дереве
struct Node {
    int key;
    char side;
    Node* left;
    Node* right;
};

Node* newNode(int key, char side) {
    Node* node = new Node();
    node->key = key;
    node->side = side;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

Node* merge(Node* root1, Node* root2) {
    // if tree is empy return another 
    if (!root1) return root2;
    if (!root2) return root1;

    // choose node with low priority 
    if (root1->key > root2->key)
        std::swap(root1, root2);

    // merge right subtree with root2 tree 
    root2->side = 'l';
    root1->right = merge(root1->right, root2);

    // swap left and right subtrees 
    if (!root1->left || (root1->right && root1->left->key > root1->right->key))
        std::swap(root1->left, root1->right);

    return root1;
}

void preOrder(Node* root) {
    if (root) {
      if (root->side == 'R')
        std::cout << root->key << std::endl;
      else if (root->side == 'r')
        std::cout << "Right: "<< root->key << std::endl;
      else if (root->side == 'l')
        std::cout << "Left: "<< root->key << std::endl;
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    Node* root1 = newNode(8, 'R');
    root1->left = newNode(12, 'l');
    root1->right = newNode(3, 'r');
    root1->left->left = newNode(55, 'l');

    Node* root2 = newNode(4, 'R');
    root2->left = newNode(21, 'l');
    root2->right = newNode(7, 'r');

    std::cout << "Дерево 1:\n";
    preOrder(root1);
    std::cout << "--------" << std::endl;

    std::cout << "Дерево 2:\n";
    preOrder(root2);
    std::cout << "--------" << std::endl;


    Node* mergedRoot = merge(root1, root2);

    std::cout << "Слияние двух деревьев: \n";
    preOrder(mergedRoot);
    std::cout << "--------" << std::endl;


    return 0;
}
