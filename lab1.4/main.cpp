#include <stdio.h>
#include <malloc.h>
#include "ring_list.h"

int main() {

	RingList ringField;

	int userChoice = 0;

	do {	
			printf("Mode:\nPush next(1)\nPush prev(2)\nPush cur(3)\nPull(4)\nPrint ring(5)\nSearch element index(6)\nGo next(7)\nGo prev(8)\nClear ring(9)\nExit(10)\n> "); scanf("%d", &userChoice);
			switch (userChoice) {
				case 1: {
                  int d;
                  printf(">>"); scanf("%d", &d);
                  push_next(ringField, d);
                } break;
				case 2: {
                  int d;
                  printf(">>"); scanf("%d", &d);
                  push_prev(ringField, d); 
                } break;
        case 3: {
                  int d;
                  printf(">>"); scanf("%d", &d);
                  push_cur(ringField, d);
                } break;
				case 4:	pull(ringField); break; 
				case 5: print_ring(ringField); break;
        case 6: search_element_index(ringField); break;
				case 7: go_next(ringField); break;
				case 8: go_prev(ringField); break;
				case 9: clear_ring(ringField); return 0; break;
        case 10: break;
				default: printf("Incorrect choice!\n");
			}
	}while(userChoice != 10);

}
