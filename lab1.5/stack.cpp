#include <stdio.h>
#include "stack.h"

void Node::setFields() {
}

int Stack::size() {
  return count;
}

void Stack::push(int id, int age) {
  
  Node* node = new Node(id, age);

  if (head == NULL) 
    head = tail = node;
  else {
    tail->next = node;
    tail->prev = tail;
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
