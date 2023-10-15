#include <stdio.h>
#include <malloc.h>
#include "list.h"

void push_front(List& list) {

	Student * e = (Student*)malloc(sizeof(Student));

	fill_element(*e);

	e->next = list.head;
	list.head = e;

	list.size++;

}

void push_back(List& list) {

	Student * e = (Student*)malloc(sizeof(Student));

	fill_element(*e);

	e->next = nullptr;

	if (list.head == nullptr) 
		list.head = e;
	else {
		Student * cur = list.head;
		while(cur->next != nullptr)
			cur = cur->next;
		cur->next = e;
	}
	list.size++;

}

void push_position(int n, List& list) {

	if (n <= 0) {
		printf("INCORRECT!\n");
		return;
	}
	if (n-1 > list.size) {
		printf("INCORRECT!\n");
		return;
	}
	if (n-1 == 0) {
		push_front(list);
		return;
	}
	if (n-1 == list.size) {
		push_back(list);
		return;
	}
	else {
		Student* current = list.head;
		for (int i = 0; i < n-2; i++) {
			if (current == NULL) {
				printf("INCORRECT!\n");
				return;
			}
			current = current->next;
		}
		Student* e = (Student*)malloc(sizeof(Student));
		fill_element(*e);
		e->next = current->next;
		current->next = e;
		list.size++;
	}

}

void pull_front(List& list) {

	if (list.head == nullptr) return;

	Student * e = list.head;
	list.head = list.head->next;

	free(e);

	list.size--;
}

void pull_back(List& list) {

	if (list.head == NULL) return;
	Student* cur = list.head;
	if (list.head->next == NULL) {
		list.head = NULL;
		free(cur);
		return;
	}
	while (cur->next->next != NULL)
		cur = cur->next;
	free(cur->next);
	cur->next = NULL;

	list.size--;
}

void pull_position(int n, List& list) {

	int tmp;
	if (list.head == NULL) return; 
	if (n <= 0) {
		printf("INCORRECT!\n");
		return;
	}
	if (n-1 >= list.size) {
		printf("INCORRECT\n");
		return;
	}
	if (n-1 == 0) {
		pull_front(list);
		return;
	}
	else {
		Student* current = list.head;
		for (int i = 0; i < n-2; i++) {
			if (current == NULL) {
				printf("INCORRECT:\n");
				return;
			}
			current = current->next;
		}
		Student* next = current->next->next;
		free(current->next);
		current->next = next;
		list.size--;
		return;
	}

}

void fill_element(Student& e) {

	printf("Surname: "); scanf("%s", e.surname);			

	printf("Year, Group: "); scanf("%d%d", &e.year, &e.group);	

	printf("Marks: ");
	scanf("%d", &e.mark);
	

}

void print_list(List& list) {

	if (list.head != nullptr) {

		printf("------------------------------------------------\n");

		for (Student * cur = list.head; cur != nullptr; cur = cur->next) {
			printf("Surname: %s\n", cur->surname);
			printf("Year: %i\n", cur->year);	
			printf("Group: %i\n", cur->group);	

			printf("Marks: ");
			printf("%d ", cur->mark);
		}

		printf("------------------------------------------------\n");

	}

	else
		printf("\nNothing to display. List is empty!\n\n");

}

void clear_list(List& list) {
	if (list.head == NULL) return;

	while(list.head != NULL) {
		Student* e = list.head;	
		list.head = list.head->next;
		free(e);
	}

}
