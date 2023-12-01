#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Node {
    int value;
    vector<Node*> children;
};

// Функция для вычисления максимальной массы для каждого узла
void calculateMaxWeights(Node* root, int limit) {
    if (root == nullptr) {
        return;
    }

    if (root->children.empty()) {
        // Если узел - лист, выводим минимальное значение массы, если оно меньше предельно допустимой м ассы
        if (root->value <= limit) {
            cout << "Максимальная масса для узла: " << root->value << endl;
        } else {
            cout << "Узел недостижим по предельно допустимой массе" << endl;
        }
        return;
    }

    int maxChildWeight = numeric_limits<int>::min();

    // Рекурсивно вычисляем максимальную массу для каждого ребенка узла
    for (Node* child : root->children) {
        calculateMaxWeights(child, limit);
        if (child->value > maxChildWeight) {
            maxChildWeight = child->value;
        }
    }

    // Максимальная масса узла - сумма максимальных масс его детей и его собственного значения
    root->value = maxChildWeight;
    for (Node* child : root->children) {
        root->value += child->value;
    }

    // Проверяем, не превышает ли масса узла предельно допустимую массу
    if (root->value > limit) {
        cout << "Узел недостижим по предельно допустимой массе" << endl;
        root->value = 0; // Если узел недостижим, устанавливаем его массу в 0
    } else {
        cout << "Максимальная масса для узла: " << root->value << endl;
    }
}

int main() {
    // Создаем пример дерева
    Node* root = new Node{0};
    Node* child1 = new Node{2};
    Node* child2 = new Node{3};
    Node* child3 = new Node{4};

    root->children.push_back(child1);
    root->children.push_back(child2);
    root->children.push_back(child3);

    Node* subChild1 = new Node{1};
    Node* subChild2 = new Node{2};
    Node* subChild3 = new Node{5};

    child1->children.push_back(subChild1);
    child1->children.push_back(subChild2);
    child2->children.push_back(subChild3);

    int limit = 10; // Предельно допустимая масса

    // Вызываем функцию для вычисления максимальной массы для каждого узла
    calculateMaxWeights(root, limit);

    // Очищаем память, выделенную под узлы
    delete subChild1;
    delete subChild2;
    delete subChild3;
    delete child1;
    delete child2;
    delete child3;
    delete root;

    return 0;
}
