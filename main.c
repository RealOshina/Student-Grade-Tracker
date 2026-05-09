#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct {
	char name[40];				// 40 bytes
	float grades[4];			// 4 Subjects: Math, Science, English, Social (16 bytes)
	int grade_count;			// 4 bytes
	float average;				// 4 bytes
} Student;						// 52 bytes

void add_student(Student *s);
void search_student(char name[40]);
float calc_average(float grades[], int grade_count);
void save_to_file(Student *s, int count);
void load_from_file(char name[40]);

Student student[100];
int student_count = 0;

int main() {
	Student s;

	while (true) {
		char input[3];

		printf("What do you want to do?\n");
		printf("[1] Add Student\n[2] Load File\n[3] Search Student\n[4] Exit\n\n");
		printf("> ");

		while (fgets(input, sizeof(input), stdin)) {
			if (sscanf_s(input, "%c", input, (unsigned)sizeof(input)) == 1) {
				if (input[0] == '1') {
					printf("\nEnter a student name: ");

					while (fgets(s.name, sizeof(s.name), stdin)) {
						if (sscanf_s(s.name, "%s", s.name, (unsigned)sizeof(s.name)) == 1) {
							break;
						} else {
							printf("Invalid Input.\n\n");
							printf("Enter a student name: ");
						}
					}

					printf("Enter a student grades:\n");

					int i;
					char input[20];
					char option[1];
					char* subjects[4] = { "Math", "Science", "English", "Social" };

					for (i = 0; i < 4; i++) {
						printf("%s > ", subjects[i]);

						while (fgets(input, sizeof(input), stdin)) {
							if (sscanf_s(input, "%f", &s.grades[i]) == 1) {
								if (s.grades[i] < 0 || s.grades[i] > 100) {
									printf("Invalid Input.\n\n");
									printf("%s > ", subjects[i]);
								} else {
									s.grade_count = 4;
									break;
								}
							} else {
								printf("Invalid Input.\n\n");
								printf("%s > ", subjects[i]);
							}
						}
					}

					for (i = 0; i < 4; i++) {
						printf("%.2f\n", s.grades[i]);
					}

					s.average = calc_average(s.grades, s.grade_count);
					printf("%f", s.average);

					add_student(&s);
					save_to_file(student, student_count);

					break;
				} else if (input[0] == '2') {
					printf("Enter a student name: ");

					char input[40];
					while (fgets(input, sizeof(input), stdin)) {
						if (sscanf_s(input, "%s", input, (unsigned)sizeof(input)) == 1) {
							load_from_file(input);
							break;
						} else {
							printf("Invalid Input.\n\n");
							printf("Enter a student name: ");
						}
					}
					break;
				} else if (input[0] == '3') {
					printf("Enter a student name: ");

					char input[40];
					while (fgets(input, sizeof(input), stdin)) {
						if (sscanf_s(input, "%s", input, (unsigned)sizeof(input)) == 1) {
							search_student(input);
							break;
						} else {
							printf("Invalid Input.\n\n");
							printf("Enter a student name: ");
						}
					}
					break;
				} else if (input[0] == '4') {
					exit(0);
				} else {
					printf("Invalid Input.\n\n");
					printf("> ");
				}
			} else {
				printf("Invalid Input.\n\n");
				printf("> ");
			}
		}
	}

	return 0;
}

void add_student(Student* s) {
	student[student_count] = *s;
	student_count++;
}

void search_student(char name[40]) {
	FILE* fptr;
	char buffer[50];

	sprintf_s(buffer, sizeof(buffer), "%s.txt", name);
	fopen_s(&fptr, buffer, "r");

	if (fptr == NULL) {
		printf("Counldn't open the file.\n\n");
		return;
	}

	char* read_objects[5] = { "Math", "Science", "English", "Social", "Average" };

	char studentName[40];

	fgets(buffer, sizeof(buffer), fptr);
	sscanf_s(buffer, "%s", studentName, (unsigned)_countof(studentName));
	printf("Student Name: %s\n", buffer);

	int i;
	for (i = 0; i < 5; i++) {
		float grade;

		fgets(buffer, sizeof(buffer), fptr);
		sscanf_s(buffer, "%f", &grade);
		printf("%s: %.2f\n", read_objects[i], grade);
	}

	printf("\n\nSuccesfuly read the file.\n\n");

	fclose(fptr);
}

float calc_average(float grades[], int grade_count) {
	int i;
	float sum = 0;

	for (i = 0; i < grade_count; i++) {
		sum += grades[i];
	}

	return sum / grade_count;
}

void save_to_file(Student *s, int count) {
	FILE* fptr;
	char buffer[50];

	sprintf_s(buffer, sizeof(buffer), "%s.txt", s->name);
	fopen_s(&fptr, buffer, "w");

	if (fptr == NULL) {
		printf("\n\nCouldn't create the file.\n\n");
		return;
	}

	fprintf(fptr, "%s\n", s->name);
	int i;
	for (i = 0; i < 4; i++) {
		fprintf(fptr, "%.2f\n", s->grades[i]);
	}

	fprintf(fptr, "%.2f\n", s->average);
	fprintf(fptr, "\n\nIf you want to change the score, please change the number only."
		"\nThe arrangement is Math, Science, English, Social, Average.\n\n");

	printf("\n\nSuccesfuly to save the file.\n\n");

	fclose(fptr);
}

void load_from_file(char name[40]) {
	FILE* fptr;
	char buffer[50];

	sprintf_s(buffer, sizeof(buffer), "%s.txt", name);
	fopen_s(&fptr, buffer, "r");

	if (fptr == NULL) {
		printf("Counldn't open the file.\n\n");
		return;
	}
	
	char* read_objects[5] = { "Math", "Science", "English", "Social", "Average" };

	char studentName[40];

	fgets(buffer, sizeof(buffer), fptr);
	sscanf_s(buffer, "%s", studentName, (unsigned)_countof(studentName));
	printf("Student Name: %s\n", buffer);

	int i;
	for (i = 0; i < 5; i++) {
		float grade;

		fgets(buffer, sizeof(buffer), fptr);
		sscanf_s(buffer, "%f", &grade);
		printf("%s: %.2f\n", read_objects[i], grade);
	}

	printf("\n\nSuccesfuly read the file.\n\n");

	fclose(fptr);
}