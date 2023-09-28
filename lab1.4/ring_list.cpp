#include "ring_list.h"
#include <malloc.h>

void push_next(RingList& ring, int d) {

	Element *e = (Element*)malloc(sizeof(Element));

	e->data = d;

	if (ring.current == nullptr) {
		ring.current = e;
		e->next = e;
		e->prev = e;
		return;
	}
	e->next = ring.current->next;
	e->prev = ring.current;

	ring.current->next->prev = e;
	ring.current->next = e;

}

void push_prev(RingList& ring, int d) {

	Element *e = (Element*)malloc(sizeof(Element));

	e->data = d;

	if (ring.current == nullptr) {
		ring.current = e;
		e->next = e;
		e->prev = e;
		return;
	}
	e->next = ring.current;
	e->prev = ring.current->prev;

	ring.current->prev->next = e;
	ring.current->prev = e;

}

int pull(RingList& ring) {

	if (ring.current == nullptr) return 0;

	int d = ring.current->data;
	Element *e = ring.current;

	if (ring.current->next == ring.current) {
		ring.current = nullptr;
	}
	else {
		ring.current->prev->next = ring.current->next;
		ring.current->next->prev = ring.current->prev;
		ring.current = ring.current->next;
	}
	free(e);

	return d;

}

void go_next(RingList& ring) {

	if (ring.current == nullptr) return;

	ring.current = ring.current->next;

}

void go_prev(RingList& ring) {

	if (ring.current == nullptr) return;

	ring.current = ring.current->prev;

}

void push_cur(RingList& ring, int data) {

  push_next(ring, data);
  go_next(ring);

}

void print_ring(RingList ring) {

	if (ring.current == nullptr) {
		printf("Empty list\n");
		return;
	}

	printf("%i", ring.current->data);

	for (Element *cur = ring.current->next; cur != ring.current; cur = cur->next) {
		printf(" <-> %i", cur->data);
	}

	printf("\n");
}

void search_element_index(RingList ring) {
  if (ring.current == nullptr) {
		printf("Empty list\n");
		return;
	}

  int searchElement = 0;
  printf(">>"); scanf("%d", &searchElement);

  int i = 0;
  if (ring.current->data == searchElement) {
	  printf("%i - [%i]\n", ring.current->data, i);
  }
  i++;
	for (Element *cur = ring.current->next; cur != ring.current; cur = cur->next) {
    if (cur->data == searchElement) {
		  printf("%i - [%i]\n", cur->data, i);
    }
    i++;
	}

	printf("\n");
}

void clear_ring (RingList& ring) {

	if (ring.current == nullptr) return;

	while(ring.current->next != ring.current) {
		Element *e = ring.current->next;
		ring.current->next = ring.current->next->next;
		free(e);
	}

	ring.current = nullptr;

}
