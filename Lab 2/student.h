#ifndef STUDENT_H
#define STUDENT_H

#define SUBJECTS 5

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

#endif
