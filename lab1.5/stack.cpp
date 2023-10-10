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

}


