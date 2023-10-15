#define SURNAME_BUFFER 15
#define MARKS_SIZE 5

struct Element {

  int d;
	Element *next;

};

struct List {

	Element* head = nullptr;
	int size;

};

void push_front(List& list, int d);
void push_back(List& list, int d);
void push_position(int n, List& list, int d);

int pull_front(List& list);
int pull_back(List& list);
int pull_position(int n, List& list);

void clear_list(List& list);

void print_list(List& list);
