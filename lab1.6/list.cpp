#include <stdio.h>
#include <malloc.h>
#include "list.h"

void push_front(List& list, int d) {

	Element * e = (Element*)malloc(sizeof(Element));

  e->d = d;

	e->next = list.head;
	list.head = e;

	list.size++;

}

void push_back(List& list, int d) {

	Element * e = (Element*)malloc(sizeof(Element));

  e->d = d; 

	e->next = nullptr;

	if (list.head == nullptr) 
		list.head = e;
	else {
		Element * cur = list.head;
		while(cur->next != nullptr)
			cur = cur->next;
		cur->next = e;
	}
	list.size++;

}

void push_position(int n, List& list, int d) {

	if (n <= 0) {
		printf("INCORRECT!\n");
		return;
	}
	if (n-1 > list.size) {
		printf("INCORRECT!\n");
		return;
	}
	if (n-1 == 0) {
		push_front(list, d);
		return;
	}
	if (n-1 == list.size) {
		push_back(list, d);
		return;
	}
	else {
		Element* current = list.head;
		for (int i = 0; i < n-2; i++) {
			if (current == NULL) {
				printf("INCORRECT!\n");
				return;
			}
			current = current->next;
		}
		Element* e = (Element*)malloc(sizeof(Element));
    e->d = d;
		e->next = current->next;
		current->next = e;
		list.size++;
	}

}

int pull_front(List& list) {

  int d = list.head->d;

	if (list.head == nullptr) return 0;

	Element * e = list.head;
	list.head = list.head->next;

	free(e);

	list.size--;
  return d;
}

int pull_back(List& list) {

	if (list.head == NULL) return 0;
	Element* cur = list.head;
	if (list.head->next == NULL) {
		list.head = NULL;
		free(cur);
		return 0;
	}
	while (cur->next->next != NULL) {
		cur = cur->next;
  }
  int d = cur->d;
	free(cur->next);
	cur->next = NULL;

	list.size--;
  return d;
}

int pull_position(int n, List& list) {

	int tmp;
	if (list.head == NULL) return 0; 
	if (n <= 0) {
		printf("INCORRECT!\n");
		return 0;
	}
	if (n-1 >= list.size) {
		printf("INCORRECT\n");
		return 0;
	}
	if (n-1 == 0) {
		pull_front(list);
		return 0;
	}
	else {
		Element* current = list.head;
		for (int i = 0; i < n-2; i++) {
			if (current == NULL) {
				printf("INCORRECT:\n");
				return 0;
			}
			current = current->next;
		}
    int d = current->next->d;
		Element* next = current->next->next;
		free(current->next);
		current->next = next;
		list.size--;
		return d;
	}

}

void print_list(List& list) {

	if (list.head != nullptr) {
		for (Element * cur = list.head; cur != nullptr; cur = cur->next) {
			printf("%d ", cur->d);
		}
    printf("\n");
	}

	else
		printf("\nNothing to display. List is empty!\n\n");

}

void clear_list(List& list) {
	if (list.head == NULL) return;

	while(list.head != NULL) {
		Element* e = list.head;	
		list.head = list.head->next;
		free(e);
	}

}
