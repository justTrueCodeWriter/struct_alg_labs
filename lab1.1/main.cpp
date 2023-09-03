#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void print_person(Student *students, int index);
void print_table(Student *students, int studentsAmount);
void search_surname(Student *students, int studentsAmount);

int main() {

	int studentsAmount = get_students_amount();
	if (studentsAmount == ERROR_VALUE) return -1;

	Student students[studentsAmount];
	if (get_data(students, studentsAmount) == ERROR_VALUE) return -1;

	int userChoice = 0;
	do {
		printf("Choose option:\nPrint table(1), Sort table by name(2), Sort table by column(3), Find person by surname(4), Exit(5)\n>>");
		scanf("%d", &userChoice);
		switch (userChoice) {
			case 1:
				print_table(students, studentsAmount);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				search_surname(students, studentsAmount);
				break;
			case 5:
				exit(1);
			default: printf("INCORRECT: choice must be (1 <= userChoice <= 4)\n");
		}
	}while(userChoice < 1 || userChoice > 4);

	//TODO: add wirking cycle

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

void print_person(Student *students, int index) {
	printf(" %d %-20s\t %-20s\t %-20s\t %d\t ", 
			students[index].id, students[index].surname, 
			students[index].name, students[index].patronymic, 
			students[index].creditBookId);
	for (int j = 0; j < SUBJECTS_BUFFER; j++) {
		printf("%d ", students[index].marks[j]);
	}
	printf("\n");
}

void print_table(Student *students, int studentsAmount) {

	printf("ID Surname\t\t Name\t\t\t Patronymic\t\t BookId\t A B C D E\n");
	printf("------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < studentsAmount; i++) {
		print_person(students, i);
	}

}



void search_surname(Student *students, int studentsAmount) {

	char searchSurname[20];
	printf("Enter searching surname: "); scanf("%s" , searchSurname);

	printf("ID Surname\t\t Name\t\t\t Patronymic\t\t BookId\t A B C D E\n");
	printf("------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < studentsAmount; i++) {
		if (strstr(students[i].surname, searchSurname)) {
			print_person(students, i);
		}
	}

	//TODO: Add "non exist surname" massage

}
