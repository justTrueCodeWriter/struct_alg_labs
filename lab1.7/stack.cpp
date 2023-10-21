#include <stdio.h>
#include "stack.h"

int Stack::size() {
  return count;
}

void Stack::push(std::string field) {
  
  Node* node = new Node(field);

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
  printf("--------\nID: %s\n--------\n", tail->field.c_str());

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
    printf("%s <-- ", cur->field.c_str());
    cur = cur->next;
  }
  printf("\n");
}
void Stack::save_to_file(std::string filename) {
  FILE* ft;
  ft = fopen(filename.c_str(), "wt");
  Node* cur = head;
  while (cur) {
    fprintf(ft, "%s\n", cur->field.c_str());
    cur = cur->next;
  }
}
