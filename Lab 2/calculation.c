#include <string.h>
#include "calculation.h"

void calculateResult(struct Student *s) {

    s->total = 0;
    for (int i = 0; i < SUBJECTS; i++)
        s->total += s->marks[i];

    s->percent = s->total / (float)SUBJECTS;
    s->cgpa = s->percent / 10;

    assignGrade(s);
}

void assignGrade(struct Student *s) {

    if (s->percent >= 90) strcpy(s->grade, "O");
    else if (s->percent >= 85) strcpy(s->grade, "A+");
    else if (s->percent >= 75) strcpy(s->grade, "A");
    else if (s->percent >= 65) strcpy(s->grade, "B+");
    else if (s->percent >= 60) strcpy(s->grade, "B");
    else if (s->percent >= 55) strcpy(s->grade, "C");
    else if (s->percent >= 50) strcpy(s->grade, "D");
    else strcpy(s->grade, "F");
}
