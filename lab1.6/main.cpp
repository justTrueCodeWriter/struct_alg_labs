#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

void fill_random(List& list, int n) {

  for (int i = 0; i < n; i++) {
    int data = ((rand() % (100-0)) + 0);
    push_back(list, data);
  }

}

void swap_elements(List& list, int n, int m) {
  int data1;
  int data2;

  if (n == m) {
    printf("INCORRECT!\n");
    return;
  }

  if (n < m) {
    data1 = pull_position(n, list);
    data2 = pull_position(m-1, list);
    print_list(list);
    push_position(m-1, list, data1);
    push_position(n, list, data2);

    printf("%d %d\n", data1, data2);

  }

  else if (n > m) {
    data1 = pull_position(n, list);
    data2 = pull_position(m, list);
    print_list(list);
    push_position(m, list, data1);
    push_position(n, list, data2);

    printf("%d %d\n", data1, data2);
  }

}

int main() {

  srand(time(NULL));

  List list_field;

  fill_random(list_field, 10);
  print_list(list_field); 
  
  int n, m;
  printf("n = "); scanf("%d", &n);
  printf("m = "); scanf("%d", &m);
  
  swap_elements(list_field, n, m);
  print_list(list_field);

}
