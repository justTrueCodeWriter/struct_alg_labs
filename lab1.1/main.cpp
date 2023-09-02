#include <stdio.h>
#include <string>

#define STUD_STRING_BUFFER 20
#define SUBJECTS_BUFFER 5
#define ERROR_VALUE -1

struct Student {

	int id = NULL;
	char surname[STUD_STRING_BUFFER] = "";
	char name[STUD_STRING_BUFFER] = "";
	char patronymic[STUD_STRING_BUFFER] = "";
	int creditBookId = NULL;
	int marks[SUBJECTS_BUFFER];

};

const char *FILENAME = "students.txt";

int get_students_amount();
int get_data(Student *students, int studentsAmount);
void print_table(Student *students, int studentsAmount);

int main() {

	int studentsAmount = get_students_amount();
	if (studentsAmount == ERROR_VALUE) return -1;

	Student students[studentsAmount];
	if (get_data(students, studentsAmount) == ERROR_VALUE) return -1;

	print_table(students, studentsAmount);

	return 0;

}

int get_students_amount() {

	FILE* ft;
	if ((ft = fopen(FILENAME, "rt")) == nullptr) {
		printf("ERROR: file %s doesn't exist!\n", FILENAME);
		return -1;
	}

	char line[180];
	int amount = 0;
	int isReading = 1;
	for (; fgets(line, sizeof(line), ft); amount++) {}
	
	fclose(ft);

	return amount;
	
}

int get_data(Student *students, int studentsAmount) {

	FILE* ft;
	if ((ft = fopen(FILENAME, "rt")) == nullptr) {
		printf("ERROR: file %s doesn't exist!\n", FILENAME);
		return -1;
	}

	for (int i = 0; i < studentsAmount; i++) {
		fscanf(ft, "%d %s %s %s %d", 
				&students[i].id, 
				students[i].surname, 
				students[i].name, 
				students[i].patronymic, 
				&students[i].creditBookId);
	
		for (int j = 0; j < SUBJECTS_BUFFER; j++) {
			fscanf(ft, "%d ", &students[i].marks[j]);
		}
	}

	return 0;

}

void print_table(Student *students, int studentsAmount) {

	for (int i = 0; i < studentsAmount; i++) {
		printf("%d %-5s\t \r%s\t\t %-5s\t\t ", students[i].id, students[i].surname, 
							students[i].name, students[i].patronymic);
		for (int j = 0; j < SUBJECTS_BUFFER; j++) {
			printf("%d ", students[i].marks[j]);
		}
		printf("\n");
	}

}
