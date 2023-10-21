#include "stack.h"

void task() {

  Stack* singleDetails = new Stack();   

  std::ifstream inStream("item.txt");
  std::string id;
  
  if (!inStream.is_open()) {
    printf("File doesn't exists!");
    return;
  }

  for (inStream >> id; !inStream.eof(); inStream >> id) {
    if (id.find(":")==std::string::npos) {
      singleDetails->push(id);
    }
  }

  singleDetails->print();

}

int main() {

  task();

}
