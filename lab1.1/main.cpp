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

void surname_sort(Student *students, int studentsAmount);
void choice_subject_sort(Student *students, int studentsAmount);
void choosed_mark_sort(Student *students, int studentsAmount, int subjectIndex);

void search_surname(Student *students, int studentsAmount);

int main() {

	int studentsAmount = get_students_amount();
	if (studentsAmount == ERROR_VALUE) return -1;

	Student students[studentsAmount];
	if (get_data(students, studentsAmount) == ERROR_VALUE) return -1;

	int programCycle = true;
	int userChoice = 0;
	do {
		printf("Choose option:\nPrint table(1), Sort table by surname(2), Sort table by column(3), Find person by surname(4), Exit(5)\n\033[0;32m>>\033[0;0m");
		scanf("%d", &userChoice);
		switch (userChoice) {
			case 1:
				print_table(students, studentsAmount);
				break;
			case 2:
				surname_sort(students, studentsAmount);
				break;
			case 3:
				choice_subject_sort(students, studentsAmount);
				break;
			case 4:
				search_surname(students, studentsAmount);
				break;
			case 5:
				programCycle = false;
				break;
			default: printf("\033[0;31mINCORRECT: choice must be (1 <= userChoice <= 4)\n\033[0m");
		}
	}while(programCycle);

	//TODO: add wirking cycle

	return 0;

}

int get_students_amount() {

	FILE* ft;
	if ((ft = fopen(FILENAME, "rt")) == nullptr) {
		printf("\033[0;31mERROR: file %s doesn't exist!\n\033[0;0m", FILENAME);
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
		printf("\033[0;31mERROR: file %s doesn't exist!\n\033[0;0m", FILENAME);
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
	char space = ' ';
	if (students[index].id > 9) space = '\0';

	printf("%c%d %-20s\t %-20s\t %-20s\t %d\t ", space,
			students[index].id, students[index].surname, 
			students[index].name, students[index].patronymic, 
			students[index].creditBookId);
	for (int j = 0; j < SUBJECTS_BUFFER; j++) {
		printf("%d ", students[index].marks[j]);
	}
	printf("\n");
}

void print_table(Student *students, int studentsAmount) {

	printf("\033[0;33mID Surname\t\t Name\t\t\t Patronymic\t\t BookId\t A B C D E\n\033[0;0m");
	printf("------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < studentsAmount; i++) {
		print_person(students, i);
	}

}

void surname_sort(Student *students, int studentsAmount) {

	for (int i = 0; i < studentsAmount-1; i++) {
		for (int j = 0; j < studentsAmount-i-1; j++) {
			for (int k = 0; students[j].surname[k] != '\n'; k++) {
				if (students[j].surname[k] > students[j+1].surname[k])	{
					Student tmp = students[j];
					students[j] = students[j+1];
					students[j+1] = tmp;
					break;
				}
				else if (students[j].surname[k] < students[j+1].surname[k]) {
					break;
				}	
			}
		}
	}

}

void choice_subject_sort(Student *students, int studentsAmount) {

	char userChoice;

	printf("Choose subject to sort marks:\nA - Math\nB - IT\nC - History\nD - Unix\nE - Philosophy\n\033[0;32m>>\033[0;0m");
	scanf(" %c", &userChoice);

	switch (userChoice) {
		case 'A':
			choosed_mark_sort(students, studentsAmount, 0);
			break;
		case 'B':
			choosed_mark_sort(students, studentsAmount, 1);
			break;
		case 'C':
			choosed_mark_sort(students, studentsAmount, 2);
			break;
		case 'D':
			choosed_mark_sort(students, studentsAmount, 3);
			break;
		case 'E':
			choosed_mark_sort(students, studentsAmount, 4);
			break;
		default: printf("\033[0;31mSubject doesn't exists!\n\033[0m");
	}			

}

void choosed_mark_sort(Student *students, int studentsAmount, int subjectIndex) {
	for (int i = 0; i < studentsAmount-1; i++) {
		for (int j = 0; j < studentsAmount-i-1; j++) {
			if (students[j].marks[subjectIndex] < students[j+1].marks[subjectIndex]) {
				Student tmp = students[j];
				students[j] = students[j+1];
				students[j+1] = tmp;
			}
		}
	}
}

bool is_request(Student *students, int studentsAmount, char *searchSurname) {
	int isRequestExists = 0;
	for (int i = 0; i < studentsAmount; i++) {
		if (strcasestr(students[i].surname, searchSurname)) {
			isRequestExists = 1;	
			break;
		}
	}

	return isRequestExists;

}

void search_surname(Student *students, int studentsAmount) {

	char searchSurname[20];

	printf("Enter searching surname: "); scanf("%s" , searchSurname);

	bool isRequestExists = is_request(students, studentsAmount, searchSurname);
	if (!isRequestExists) {
		printf("\033[0;31mRequest doesn't exists!\n\033[0m");
		return;
	}

	printf("\033[0;33mID Surname\t\t Name\t\t\t Patronymic\t\t BookId\t A B C D E\n\033[0;0m");
	printf("------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < studentsAmount; i++) {
		if (strcasestr(students[i].surname, searchSurname)) {
			print_person(students, i);
		}
	}

	

}
