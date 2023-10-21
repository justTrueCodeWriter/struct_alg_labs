#include <string>
#include <iostream>
#include <fstream>

class Node {

  public:
  Node(std::string vfield) {
    field = vfield;
  }

  Node* next = nullptr;
  Node* prev = nullptr;

  std::string field = "";

};

class Stack {

  public:
  Node* head = nullptr;
  Node* tail = nullptr;

  Stack() {
    head = tail = nullptr;
    count = 0;
  }

  ~Stack(){}; 

  int size();
  void push(std::string field);
  void fill_random(int n);
  int file_elements_amount(std::string);
  void fill_from_file(std::string);
  Node* pull();
  void clear();
  void clear_n(int n);
  void print();
  void look();
  void save_to_file(std::string);

  private:
  int count = NULL;

};
