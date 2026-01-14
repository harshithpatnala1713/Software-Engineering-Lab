#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SUBJECTS 5
#define MAX 100

struct Student {
    char id[20];
    char name[30];
    char course[SUBJECTS][20];
    int marks[SUBJECTS];
    int total;
    float percent;
    char grade[3];
    float cgpa;
};

// Function declarations
int validId(char id[]);
int validName(char name[]);
int validMarks(int minor, int major);

void calculateMarks(struct Student *s);
void findGrade(struct Student *s);
void writeResult(struct Student stud[], int n);
void classSummary(struct Student stud[], int n, FILE *fp);

// Main
int main(int argc, char *argv[]) {

    struct Student stud[MAX];
    int count = 0;
    FILE *fp;

    if (argc != 2) {
        printf("Usage: %s <inputfile>\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    while (fscanf(fp, "%s", stud[count].id) != EOF) {

        fscanf(fp, "%s", stud[count].name);

        if (!validId(stud[count].id) || !validName(stud[count].name)) {
            printf("Invalid student data\n");
            return 1;
        }

        for (int i = 0; i < SUBJECTS; i++) {
            int minor, major;

            fscanf(fp, "%s %d %d",
                   stud[count].course[i],
                   &minor, &major);

            if (!validMarks(minor, major)) {
                printf("Invalid marks for %s\n", stud[count].id);
                return 1;
            }

            stud[count].marks[i] = minor + major;
        }

        calculateMarks(&stud[count]);
        count++;
    }

    fclose(fp);

    writeResult(stud, count);
    return 0;
}

// Validation

int validId(char id[]) {
    for (int i = 0; id[i]; i++)
        if (!isalnum(id[i]))
            return 0;
    return 1;
}

int validName(char name[]) {
    for (int i = 0; name[i]; i++)
        if (!isalpha(name[i]))
            return 0;
    return 1;
}

int validMarks(int minor, int major) {
    if (minor < 0 || minor > 40) return 0;
    if (major < 0 || major > 60) return 0;
    return 1;
}

// Calculation

void calculateMarks(struct Student *s) {

    s->total = 0;

    for (int i = 0; i < SUBJECTS; i++)
        s->total += s->marks[i];

    s->percent = s->total / (float)SUBJECTS;
    s->cgpa = s->percent / 10;

    findGrade(s);
}

void findGrade(struct Student *s) {

    if (s->percent >= 90) strcpy(s->grade, "O");
    else if (s->percent >= 85) strcpy(s->grade, "A+");
    else if (s->percent >= 75) strcpy(s->grade, "A");
    else if (s->percent >= 65) strcpy(s->grade, "B+");
    else if (s->percent >= 60) strcpy(s->grade, "B");
    else if (s->percent >= 55) strcpy(s->grade, "C");
    else if (s->percent >= 50) strcpy(s->grade, "D");
    else strcpy(s->grade, "F");
}

// Output

void writeResult(struct Student stud[], int n) {

    FILE *fp = fopen("output.txt", "w");

    fprintf(fp, "ID        Name       Total  Percent  Grade  CGPA\n");
    fprintf(fp, "-----------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%-10s %-10s %6d %8.2f %6s %6.2f\n",
                stud[i].id,
                stud[i].name,
                stud[i].total,
                stud[i].percent,
                stud[i].grade,
                stud[i].cgpa);
    }

    classSummary(stud, n, fp);
    fclose(fp);
}

void classSummary(struct Student stud[], int n, FILE *fp) {

    float sum = 0, high = stud[0].percent, low = stud[0].percent;
    int O=0,A1=0,A=0,B1=0,B=0,C=0,D=0,F=0;

    for (int i = 0; i < n; i++) {

        sum += stud[i].percent;
        if (stud[i].percent > high) high = stud[i].percent;
        if (stud[i].percent < low)  low = stud[i].percent;

        if (!strcmp(stud[i].grade,"O")) O++;
        else if (!strcmp(stud[i].grade,"A+")) A1++;
        else if (!strcmp(stud[i].grade,"A")) A++;
        else if (!strcmp(stud[i].grade,"B+")) B1++;
        else if (!strcmp(stud[i].grade,"B")) B++;
        else if (!strcmp(stud[i].grade,"C")) C++;
        else if (!strcmp(stud[i].grade,"D")) D++;
        else F++;
    }

    fprintf(fp, "\nClass Average : %.2f\n", sum / n);
    fprintf(fp, "Highest %%     : %.2f\n", high);
    fprintf(fp, "Lowest %%      : %.2f\n", low);

    fprintf(fp, "\nGrade Count:\n");
    fprintf(fp, "O  : %d\nA+ : %d\nA  : %d\nB+ : %d\nB  : %d\nC  : %d\nD  : %d\nF  : %d\n",
            O,A1,A,B1,B,C,D,F);
}
