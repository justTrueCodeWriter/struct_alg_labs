#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

const int MIN = 2;
const int MAX = 4;

class Point 
{
public:
    double coordinates[MIN];
    Point() 
    {
        for (int i = 0; i < MIN; i++)
            coordinates[i] = 0.0;
    }
    Point(double x, double y) 
    {
        coordinates[0] = x;
        coordinates[1] = y;
    }

    bool operator==(Point b)
    {
        for (int i = 0; i < MIN; i++)
            if (coordinates[i] != b.coordinates[i])
                return false;
        return true;
    }

    bool operator<=(Point b)
    {
        for (int i = 0; i < MIN; i++)
            if (coordinates[i] > b.coordinates[i])
                return false;
        return true;
    }

    bool operator>=(Point b)
    {
        for (int i = 0; i < MIN; i++)
            if (coordinates[i] < b.coordinates[i])
                return false;
        return true;
    }
};

class Node 
{
public:
    vector<Point> points;
    vector<Node*> children;
    bool is_leaf;
    Node(bool leaf = true) : is_leaf(leaf) {}
};

class R_Tree
{
private:
    Node* root;

    void Clear(Node* node)
    {
        if (node->is_leaf)
            node->points.clear();
        else
        {
            for (Node* n : node->children)
            {
                Clear(n);
                delete n;
            }
            node->children.clear();
        }
    }

    void Insert_Recursive(Node* node, const Point& point)
    {
        if (node->is_leaf)
        {
            if (node->points.size() < MAX)
            {
                node->points.push_back(point);
            }
            else
            {
                Split_Node(node, point);
            }
        }
        else
        {
            double min_dist = numeric_limits<double>::max();
            Node* next_node = nullptr;
            for (Node* child : node->children)
            {
                double dist = Distance(child->points[0], point);
                if (dist < min_dist)
                {
                    min_dist = dist;
                    next_node = child;
                }
            }

            Insert_Recursive(next_node, point);
        }
    }

    void Split_Node(Node* node, const Point& point)
    {
        node->points.push_back(point);

        // Calculate the minimum bounding rectangle
        Point min_point, max_point;
        for (int i = 0; i < MIN; ++i)
        {
            min_point.coordinates[i] = max_point.coordinates[i] = node->points[0].coordinates[i];
            for (const Point& p : node->points)
            {
                min_point.coordinates[i] = min(min_point.coordinates[i], p.coordinates[i]);
                max_point.coordinates[i] = max(max_point.coordinates[i], p.coordinates[i]);
            }
        }

        // Choose split axis
        int split_axis = 0;
        double max_width = max_point.coordinates[0] - min_point.coordinates[0];
        for (int i = 1; i < MIN; ++i)
        {
            double width = max_point.coordinates[i] - min_point.coordinates[i];
            if (width > max_width)
            {
                max_width = width;
                split_axis = i;
            }
        }

        // Choose split position
        double split_position = (max_point.coordinates[split_axis] + min_point.coordinates[split_axis]) / 2.0;

        // Create new nodes
        Node* left_node = new Node();
        Node* right_node = new Node();

        // Distribute points between the left and right nodes
        for (const Point& p : node->points)
        {
            if (p.coordinates[split_axis] < split_position)
                left_node->points.push_back(p);
            else
                right_node->points.push_back(p);
        }


        node->points.clear();
        node->children.push_back(left_node);
        node->children.push_back(right_node);
        node->is_leaf = false;
    }

    double Distance(const Point& a, const Point& b)
    {
        double dist = 0;
        for (int i = 0; i < MIN; ++i)
        {
            dist += pow(a.coordinates[i] - b.coordinates[i], 2);
        }
        double x = sqrt(dist);
        return sqrt(dist);
    }

    bool Delete_Recursive(Node* node, const Point& point)
    {
        if (node->is_leaf)
        {
            for (vector<Point>::iterator i = node->points.begin(); i != node->points.end(); i++)
                if (*i == point)
                {
                    node->points.erase(i);
                    return true;
                }
            return false;
        }
        else
        {
            for (int i = 0; i < node->children.size(); i++)
            {
                if (Delete_Recursive(node->children[i], point))
                    return true;

            }
            return false;
        }
    }

    bool Search_Recursive(Node* node, const Point& point)
    {
        if (node->is_leaf)
        {
            for (vector<Point>::iterator i = node->points.begin(); i != node->points.end(); i++)
                if (*i == point)
                {
                    return true;
                }
            return false;
        }
        else
        {
            for (int i = 0; i < node->children.size(); i++)
            {
                if (Search_Recursive(node->children[i], point))
                    return true;

            }
            return false;
        }
    }

    void Region_Search_Recursive(Node * node,vector<Point>& arr, const Point& bottom_left, const Point& top_right)
    {
        if (node->is_leaf)
        {
            for (Point p : node->points)
            {
                if (p >= bottom_left and p <= top_right)
                    arr.push_back(p);
            }
        }
        else
        {
            for (int i = 0; i < node->children.size(); i++)
                Region_Search_Recursive(node->children[i], arr, bottom_left, top_right);
        }
    }

    void Find_Neighbour_Recursive(Node* node, const Point point, Point& ans, double& min_dist)
    {
        if (node->is_leaf)
        {
            for (Point p : node->points)
            {
                double dist = Distance(p, point);
                if (dist < min_dist)
                {
                    min_dist = dist;
                    ans = p;
                }
            }
        }
        else
        {
            for (int i = 0; i < node->children.size(); i++)
                Find_Neighbour_Recursive(node->children[i], point, ans, min_dist);
        }
    }

    void Show_Recursive(Node* node)
    {
        if (node->is_leaf)
            for (Point p : node->points)
            {
                cout << "(";
                for (int i = 0; i < MIN - 1; i++)
                    cout << p.coordinates[i] << " : ";
                cout << p.coordinates[MIN - 1] << ")" << std::endl;
            }
        else
            for (int i = 0; i < node->children.size(); i++)
                Show_Recursive(node->children[i]);
    }

public:

    R_Tree()
    {
        root = new Node();
    }

    ~R_Tree()
    {
        Clear(root);
        delete root;
    }

    void Insert(const Point& point)
    {
        Insert_Recursive(root, point);
    }

    void Delete(const Point& point)
    {
        Delete_Recursive(root, point);

    }

    bool Search(const Point& point)
    {
        return Search_Recursive(root, point);
    }
    
    vector<Point> Region_Search(const Point& bottom_left, const Point& top_right)
    {
        vector<Point> ans;
        Region_Search_Recursive(root, ans, bottom_left, top_right);
        return ans;
    }

    Point Find_Neighbour(const Point& point)
    {
        double min_dist = numeric_limits<double>::max();
        Point ans;
        Find_Neighbour_Recursive(root, point, ans, min_dist);
        return ans;
    }

    void Show()
    {
        Show_Recursive(root);
    }
};

int main() 
{
    R_Tree tree;
    int key, x, y, x1, y1;
    bool flag = true;
    vector<Point> arr;
    Point p;
    while (flag)
    {
        do
        {
            cout << "1 - Добавить элемент.\n2 - Удалить элемент\n3 - Найти конкретный элемент.\n4 - Найти элементы в диапазоне.\n5 - Найти ближайшего соседа.\n6 - Вывести все элементы.\n7 - Закончить работу.\n";
            cin >> key;
        } while (key < 1 or key > 7);
        switch (key)
        {
        case 1:
            cout << "Введите x и y" << endl;
            cin >> x >> y;
            tree.Insert(Point(x, y));
            break;
        case 2:
            cout << "Введите x и y" << endl;
            cin >> x >> y;
            tree.Delete(Point(x, y));
            break;
        case 3:
            cout << "Введите x и y" << endl;
            cin >> x >> y;
            if (tree.Search(Point(x, y)))
                cout << "Такой элемент есть в дереве." << endl;
            else
                cout << "Элемент не найден." << endl;
            break;
        case 4:
            cout << "Введите x и y для первого элемеента." << endl;
            cin >> x >> y;
            cout << "Введите x и y для второго элемеента." << endl;
            cin >> x1 >> y1;
            arr = tree.Region_Search(Point(x, y), Point(x1, y1));
            cout << "Найденные элементы: ";
            for (int i = 0; i < arr.size() - 1; i++)
            {
                cout << "(" << arr[i].coordinates[0] << " : " << arr[i].coordinates[1] << "), ";
            }
            cout << "(" << arr[arr.size() - 1].coordinates[0] << " : " << arr[arr.size() - 1].coordinates[1] << ")\n";
            break;
        case 5:
            cout << "Введите x и y" << endl;
            cin >> x >> y;
            p = tree.Find_Neighbour(Point(x, y));
            cout << "Ближайшая точка к точке (" << x << " : " << y << "): (" << p.coordinates[0] << " : " << p.coordinates[1] << ")\n";
            break;
        case 6:
            tree.Show();
            break;
        case 7:
            flag = false;
        }
    }
    return 0;
}



// 3 9
