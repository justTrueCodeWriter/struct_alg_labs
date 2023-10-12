#include <string>
#include <fstream>
#include <time.h>

class Node {

  public:
  Node(int vid, int vage) {
    id = vid;
    age = vage;
  }

  Node* next = nullptr;
  Node* prev = nullptr;

  int id = NULL;
  int age = NULL;

};

class Stack {

  public:
  Node* head = nullptr;
  Node* tail = nullptr;

  Stack() {
    head = tail = nullptr;
    count = 0;
    srand(time(NULL));
  }

  ~Stack(){}; 

  int size();
  void push(int id, int age);
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
