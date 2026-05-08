#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks1, marks2, marks3;
    float total;
};

void addStudent() {
    FILE *fp = fopen("students.dat", "ab");
    struct Student s;

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks of 3 Subjects: ");
    scanf("%f %f %f", &s.marks1, &s.marks2, &s.marks3);

    s.total = s.marks1 + s.marks2 + s.marks3;

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("✅ Student record added successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nRoll: %d\nName: %s\nMarks: %.2f %.2f %.2f\nTotal: %.2f\n",
               s.roll, s.name, s.marks1, s.marks2, s.marks3, s.total);
    }

    fclose(fp);
}

void rankList() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s[100];
    int i = 0, j, count = 0;

    while (fread(&s[i], sizeof(struct Student), 1, fp)) {
        i++;
    }
    fclose(fp);
    count = i;

    // Sorting (Descending order of total marks)
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (s[i].total < s[j].total) {
                struct Student temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    printf("\n--- Rank List ---\n");
    for (i = 0; i < count; i++) {
        printf("Rank %d: Roll=%d Name=%s Total=%.2f\n",
               i + 1, s[i].roll, s[i].name, s[i].total);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Records\n");
        printf("3. Generate Rank List\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: rankList(); break;
            case 4: exit(0);
            default: printf("❌ Invalid choice!\n");
        }
    }

    return 0;
}
