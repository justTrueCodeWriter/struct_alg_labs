#include <iostream>
#include <vector>
#include <algorithm>

struct Record {
    int key;
    Record(int k) : key(k) {}
};

struct TreeNode {
    Record data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Record& r) : data(r), left(nullptr), right(nullptr) {}
};

class BalancedBinarySearchTree {
private:
    TreeNode* root;

    TreeNode* buildBalancedTree(const std::vector<Record>& records, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        TreeNode* newNode = new TreeNode(records[mid]);

        newNode->left = buildBalancedTree(records, start, mid - 1);
        newNode->right = buildBalancedTree(records, mid + 1, end);

        return newNode;
    }

    TreeNode* searchKey(TreeNode* node, int key) {
        if (node == nullptr || node->data.key == key) {
            return node;
        }

        if (key < node->data.key) {
            return searchKey(node->left, key);
        } else {
            return searchKey(node->right, key);
        }
    }

public:
    BalancedBinarySearchTree(const std::vector<Record>& records) {
        // Сортируем записи по ключам
        std::vector<Record> sortedRecords = records;
        std::sort(sortedRecords.begin(), sortedRecords.end(), [](const Record& a, const Record& b) {
            return a.key < b.key;
        });

        // Строим идеально сбалансированное бинарное дерево поиска
        root = buildBalancedTree(sortedRecords, 0, sortedRecords.size() - 1);
    }

    TreeNode* search(int key) {
        return searchKey(root, key);
    }
};

int main() {
    // Пример использования
    std::vector<Record> records = {Record(3), Record(1), Record(5), Record(2), Record(4)};

    // Создаем идеально сбалансированное бинарное дерево поиска
    BalancedBinarySearchTree tree(records);

    // Производим поиск
    int searchKey = 2;
    TreeNode* result = tree.search(searchKey);

    if (result) {
        std::cout << "Запись с ключом " << searchKey << " найдена." << std::endl;
    } else {
        std::cout << "Запись с ключом " << searchKey << " не найдена." << std::endl;
    }

    return 0;
}
