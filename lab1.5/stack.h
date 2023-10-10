#include <string>

class Node {

  public:
  Node(int vid, int vage) {
    id = vid;
    age = vage;
  }

  Node* next = nullptr;
  Node* prev = nullptr;

  void setFields();

  private:
  int id = NULL;
  int age = NULL;

};

class Stack {

  public:
  Node* head = nullptr;
  Node* tail = nullptr;

  Stack() {
    head = tail = nullptr;
    maxsize = size();
    count = 0;
  }
  ~Stack() {
    clear();
  }

  int size();
  void push(int id, int age);
  void fill_random();
  void fill_from_file(std::string);
  Node* pull();
  Node* look();
  void clear();
  void clear_n();
  void print();
  void save_to_file(std::string);

  private:
  int maxsize = NULL;
  int count = NULL;

};
