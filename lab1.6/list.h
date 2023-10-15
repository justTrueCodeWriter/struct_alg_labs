#define SURNAME_BUFFER 15
#define MARKS_SIZE 5

struct Student {

	char surname[SURNAME_BUFFER];
	int year;
	int group;
	int mark;
	Student *next;

};

struct List {

	Student* head = nullptr;
	int size;

};

void push_front(List& list);
void push_back(List& list);
void push_position(int n, List& list);

void pull_front(List& list);
void pull_back(List& list);
void pull_position(int n, List& list);

void fill_element(Student& e);
void clear_list(List& list);

void print_list(List& list);
