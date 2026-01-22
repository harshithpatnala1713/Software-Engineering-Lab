#include <stdio.h>
#include "student.h"
#include "validation.h"
#include "calculation.h"
#include "output.h"

#define MAX 100

int main(int argc, char *argv[]) {

    struct Student s[MAX];
    int count = 0;
    FILE *fp;

    if (argc != 2) {
        printf("Usage: %s <inputfile>\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Input file not found\n");
        return 1;
    }

    while (fscanf(fp, "%s", s[count].id) != EOF) {

        fscanf(fp, "%s", s[count].name);

        if (!validId(s[count].id) || !validName(s[count].name)) {
            printf("Invalid student ID or name\n");
            return 1;
        }

        for (int i = 0; i < SUBJECTS; i++) {

            int minor, major;

            fscanf(fp, "%s %d %d",
                   s[count].course[i],
                   &minor,
                   &major);

            if (!validMarks(minor, major)) {
                printf("Invalid marks for student %s\n", s[count].id);
                return 1;
            }

            s[count].marks[i] = minor + major;
        }

        calculateResult(&s[count]);
        count++;
    }

    fclose(fp);
    
    writeOutput(s, count);

    return 0;
}
