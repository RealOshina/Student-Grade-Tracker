#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct {
	char name[40];				// 40 bytes
	float grades[4];			// 4 Subjects: Math, Science, English, Social (16 bytes)
	int grade_count;			// 4 bytes
	float average;				// 4 bytes
} Student;						// 52 bytes

void add_student(Student* s);
void search_student(char name[40]);
void calc_average(float grades[], int grade_count);
void save_to_file(Student* s);
void load_from_file(char name[40]);

int main() {
	Student s;

	printf("Enter a student name: ");

	while (fgets(s.name, sizeof(s.name), stdin)) {
		if (sscanf_s(s.name, "%s", s.name, (unsigned)sizeof(s.name)) == 1) {
			break;
		}
		else {
			printf("Invalid Input.\n\n");
			printf("Enter a student name: ");
		}
	}

	printf("Enter a student grades:\n");

	int i;
	for (i = 0; i < 4; i++) {
		switch (i) {
		case 0:
			printf("Math > ");
			break;
		case 1:
			printf("Science > ");
			break;
		case 2:
			printf("English > ");
			break;
		case 3:
			printf("Social > ");
			break;
		default:
			printf("Error");
			return 1;
		};

		while (scanf_s("%f", &s.grades[i]) == 0) {
			printf("Invalid Input.\n\n");

			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
	}

	return 0;
}

void add_student(Student* s) {

}

void search_student(char name[40]) {

}

void calc_average(float grades[], int grade_count) {

}

void save_to_file(Student* s) {

}

void load_from_file(char name[40]) {

}