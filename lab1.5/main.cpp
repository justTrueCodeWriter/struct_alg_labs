#include "stack.h"

int main() {

  Stack* stackField1 = new Stack();   
  Stack* stackField2 = new Stack();   

  int userChoice;
  bool isWorking = true;
  do {
    printf("Size(1)\t\t\tClear(6)\nPush(2)\t\t\tClear N(7)\nFill random(3)\t\tPrint(8)\nFill from file(4)\tLook(9)\nPull(5)\t\t\tSave to file(10)\n\t\t\tDrop to another(11)\n\t\t\tExit(12)\n>>"); 
    scanf("%d", &userChoice);

    switch (userChoice) { 
      case 1: 
        printf("size: %d\n", stackField1->size());
        break;
      case 2: 
        {
          int id, age;
          printf("ID: "); scanf("%d", &id);
          printf("Age: "); scanf("%d", &age);
          stackField1->push(id, age);  
        }
        break;
      case 3: 
        {
          int n;
          do{
            printf("n = "); scanf("%d", &n);
          }while(n <= 0);
          stackField1->fill_random(n);
        }
        break;
      case 4: 
        stackField1->fill_from_file("inData.txt");
        break;
      case 5: 
        stackField1->pull();
        break;
      case 6: 
        stackField1->clear();
        break;
      case 7: 
        {
          int n;
          do {
            printf("n = "); scanf("%d", &n);
          }while(n <= 0);
          stackField1->clear_n(n);
        }
        break;
      case 8: 
        stackField1->print();
        break;
      case 9: 
        stackField1->look();
        break;
      case 10: 
        stackField1->save_to_file("outData.txt");
        break;
      case 11:
        {
          Node* node = stackField1->pull();
          stackField2->push(node->id, node->age);
          printf("------------|Stack 2|-------------\n");
          stackField2->print();
        }
        break;
      case 12:
        isWorking = false;
        break;
  }
  }while(isWorking);
  delete stackField1;
  delete stackField2;

}
