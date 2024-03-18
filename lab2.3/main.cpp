// Пример простой реализации R-дерева на C++

#include <vector>
#include <climits>

struct Rectangle {
    int x1, y1, x2, y2;

    bool intersects(const Rectangle& other) {
        return x1 <= other.x2 && x2 >= other.x1 && y1 <= other.y2 && y2 >= other.y1;
    }
    bool operator==(const Rectangle& other) {
        return x1 == other.x1 && x2 == other.x2 && y1 == other.y1 && y2 == other.y2;
    }
};

class RTree {
private:
    struct Node {
        Rectangle mbr;
        std::vector<Node*> children;
        bool isLeaf;
    };

    Node* root;

public:
    RTree() {
        root = nullptr;
    }

    void insert(const Rectangle& rect) {
        if (root == nullptr) {
            root = new Node();
            root->mbr = rect;
            root->isLeaf = true;
        } else {
            insert(root, rect);
        }
    }

    void insert(Node* node, const Rectangle& rect) {
        if (node->isLeaf) {
            node->children.push_back(new Node());
            node->children.back()->mbr = rect;
            node->children.back()->isLeaf = true;

            if (node->children.size() > 4) {
                split(node);
            } else {
                node->mbr = getMbr(node->children);
            }
        } else {
            for (auto child : node->children) {
                if (child->mbr.intersects(rect)) {
                    insert(child, rect);
                    break;
                }
            }
        }
    }

    void split(Node* node) {
        Node* newNode = new Node();
        newNode->isLeaf = node->isLeaf;
        node->children.push_back(newNode);

        Rectangle mbr1, mbr2;
        int index = 0;

        while (node->children.size() >= 2) {
            int minDiff = INT_MAX;

            for (int i = 0; i < node->children.size() - 1; ++i) {
                for (int j = i + 1; j < node->children.size(); ++j) {
                    Rectangle rect = getMbr(node->children[i]->mbr, node->children[j]->mbr);
                    int diff = static_cast<int>(rect.x2 - rect.x1) * static_cast<int>(rect.y2 - rect.y1) -
                                static_cast<int>(node->children[i]->mbr.x2 - node->children[i]->mbr.x1) * static_cast<int>(node->children[i]->mbr.y2 - node->children[i]->mbr.y1) -
                                static_cast<int>(node->children[j]->mbr.x2 - node->children[j]->mbr.x1) * static_cast<int>(node->children[j]->mbr.y2 - node->children[j]->mbr.y1);

                    if (diff < minDiff) {
                        minDiff = diff;
                        mbr1 = node->children[i]->mbr;
                        mbr2 = node->children[j]->mbr;
                        index = i;
                    }
                }
            }

            newNode->children.push_back(node->children[node->children.size() - 1]);
            node->children.pop_back();
        }

        newNode->mbr = getMbr(mbr1, mbr2);
        node->children[index]->mbr = mbr1;
        node->children[index + 1]->mbr = mbr2;
    }

    Rectangle getMbr(const std::vector<Node*>& nodes) {
        Rectangle rect;
        rect.x1 = nodes[0]->mbr.x1;
        rect.y1 = nodes[0]->mbr.y1;
        rect.x2 = nodes[0]->mbr.x2;
        rect.y2 = nodes[0]->mbr.y2;

        for (auto node : nodes) {
            if (node->mbr.x1 < rect.x1) {
                rect.x1 = node->mbr.x1;
            }
            if (node->mbr.y1 < rect.y1) {
                rect.y1 = node->mbr.y1;
            }
            if (node->mbr.x2 > rect.x2) {
                rect.x2 = node->mbr.x2;
            }
            if (node->mbr.y2 > rect.y2) {
                rect.y2 = node->mbr.y2;
            }
        }

        return rect;
    }

    Rectangle getMbr(const Rectangle& rect1, const Rectangle& rect2) {
        Rectangle rect;
        rect.x1 = std::min(rect1.x1, rect2.x1);
        rect.y1 = std::min(rect1.y1, rect2.y1);
        rect.x2 = std::max(rect1.x2, rect2.x2);
        rect.y2 = std::max(rect1.y2, rect2.y2);

        return rect;
    }

    void remove(const Rectangle& rect) {
        remove(root, rect);
    }

     void remove(Node* node, const Rectangle& rectToRemove) {
        if (node == nullptr) {
            return;
        }

        if (node->isLeaf) {
            for (auto it = node->children.begin(); it != node->children.end(); ++it) {
                if ((*it)->mbr == rectToRemove) {
                    node->children.erase(it);
                    break;
                }
            }
        } else {
            for (auto child : node->children) {
                if (child->mbr.intersects(rectToRemove)) {
                    remove(child, rectToRemove);
                }
            }
        }
    } 



    std::vector<Rectangle> search(const Rectangle& rect) {
        std::vector<Rectangle> result;
        search(root, rect, result);
        return result;
    }

    void search(Node* node, const Rectangle& rect, std::vector<Rectangle>& result) {
        if (node == nullptr) {
            return;
        }

        if (node->isLeaf) {
            for (auto child : node->children) {
                if (child->mbr.intersects(rect)) {
                    result.push_back(child->mbr);
                }
            }
        } else {
            for (auto child : node->children) {
                if (child->mbr.intersects(rect)) {
                    search(child, rect, result);
                }
            }
        }
    }
};

#include <iostream>

int main() {
    // Test 1: Inserting rectangles
    RTree tree;
    Rectangle rect1 = {0, 0, 5, 5};
    Rectangle rect2 = {3, 3, 8, 8};
    tree.insert(rect1);
    tree.insert(rect2);

    // Test 2: Searching for rectangles
    Rectangle searchRect = {2, 2, 6, 6};
    std::vector<Rectangle> result = tree.search(searchRect);
    std::cout << "Search result:" << std::endl;
    for (const auto& rect : result) {
        std::cout << "(" << rect.x1 << ", " << rect.y1 << "), (" << rect.x2 << ", " << rect.y2 << ")" << std::endl;
    }
    tree.remove(rect1);

    return 0;
}