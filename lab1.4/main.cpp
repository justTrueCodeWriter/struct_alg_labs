#include <stdio.h>
#include <malloc.h>
#include "ring_list.h"

int main() {

	RingList ringField;

	int userChoice = 0;

	do {	
			printf("Mode:\nPush next(1)\nPush prev(2)\nPush cur(3)\nPush position(4)\nPull(5)\nPull position(6)\nPrint ring(7)\nSearch element index(8)\nGo next(9)\nGo prev(10)\nClear ring(11)\nExit(12)\n> "); scanf("%d", &userChoice);
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
				case 4: push_position(ringField); break;
				case 5:	pull(ringField); break; 
				case 6: pull_position(ringField); break;
				case 7: print_ring(ringField); break;
        case 8: search_element_index(ringField); break;
				case 9: go_next(ringField); break;
				case 10: go_prev(ringField); break;
				case 11: clear_ring(ringField); return 0; break;
        case 12: break;
				default: printf("Incorrect choice!\n");
			}
	}while(userChoice != 12);

}
