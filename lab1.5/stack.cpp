#include <stdio.h>
#include "stack.h"

int Stack::size() {
  return count;
}

void Stack::push(int id, int age) {
  
  Node* node = new Node(id, age);

  if (head == NULL) {
    head = node;
    tail = node;
  }
  else {
    tail->next = node;
    node->next = nullptr;
    node->prev = tail;
    tail = node;
  }
  count++;

}

void Stack::fill_random(int n) {

  for (int i = 0; i < n; i++) {
    int id = i;
    int age = (rand() % (100 - 0)) + 0; 
    push(id, age);
  }

}

int Stack::file_elements_amount(std::string filename) {

  int amount = 0;
  std::ifstream file(filename);
  if (file.is_open()) {
    std::string line;
    while(getline(file, line)) {
      amount++;
    }
  }
  return amount;
}

void Stack::fill_from_file(std::string filename) {
  int amount = file_elements_amount(filename);
  FILE* ft;
  ft = fopen(filename.c_str(), "rt");
  if (ft == NULL) return;
  while (count < amount) {
    int id, age;  
    fscanf(ft, "%d %d", &id, &age);
    push(id, age);
  }

}

Node* Stack::pull() {
  Node* node = tail;
  Node* tmpNode;
  if (!node) {
    printf("Stack is empty!\n");
    return nullptr;
  }
  if (node == head) {
    head = tail = nullptr;
    count--;
    tmpNode = node;
    delete node;
    return tmpNode;
  }
 
  tail->prev->next = nullptr;
  tail = node->prev;
  tmpNode = node;
  delete node;
  count--;
  return tmpNode;

}

void Stack::look() {
  
  if (!head) {
    printf("Stack is empty!\n");
    return;
  }
  printf("--------\nID: %d\nAge: %d\n--------\n", tail->id, tail->age);

}

void Stack::clear() {
  
  while (head)
  {
    pull();
  }
}

void Stack::clear_n(int n) {
  int k = 0;
  while (k < n)
  {
    pull();
    k++;
  }
}
void Stack::print() {

  if (!head) {
    printf("Stack is empty!\n");
    return;
  }
  Node* cur = head;
  while (cur)
  {
    printf("--------\nID: %d\nAge: %d\n--------", cur->id, cur->age);
    cur = cur->next;
  }
  printf("\n");
}
void Stack::save_to_file(std::string filename) {
  FILE* ft;
  ft = fopen(filename.c_str(), "wt");
  Node* cur = head;
  while (cur) {
    fprintf(ft, "%d %d\n", cur->id, cur->age);
    cur = cur->next;
  }
}
