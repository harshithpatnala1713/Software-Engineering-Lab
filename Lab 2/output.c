#include <stdio.h>
#include <string.h>
#include "output.h"

void writeOutput(struct Student s[], int n) {

    FILE *fp = fopen("output.txt", "w");

    float sum = 0, high = s[0].percent, low = s[0].percent;
    int O=0,A1=0,A=0,B1=0,B=0,C=0,D=0,F=0;

    fprintf(fp, "ID        Name       Total  Percent  Grade  CGPA\n");
    fprintf(fp, "-----------------------------------------------\n");

    for (int i = 0; i < n; i++) {

        fprintf(fp, "%-10s %-10s %6d %8.2f %6s %6.2f\n",
                s[i].id, s[i].name,
                s[i].total, s[i].percent,
                s[i].grade, s[i].cgpa);

        sum += s[i].percent;
        if (s[i].percent > high) high = s[i].percent;
        if (s[i].percent < low)  low = s[i].percent;

        if (!strcmp(s[i].grade,"O")) O++;
        else if (!strcmp(s[i].grade,"A+")) A1++;
        else if (!strcmp(s[i].grade,"A")) A++;
        else if (!strcmp(s[i].grade,"B+")) B1++;
        else if (!strcmp(s[i].grade,"B")) B++;
        else if (!strcmp(s[i].grade,"C")) C++;
        else if (!strcmp(s[i].grade,"D")) D++;
        else F++;
    }

    fprintf(fp, "\nClass Average : %.2f\n", sum/n);
    fprintf(fp, "Highest %%     : %.2f\n", high);
    fprintf(fp, "Lowest %%      : %.2f\n", low);

    fprintf(fp, "\nGrade Count:\n");
    fprintf(fp, "O:%d A+:%d A:%d B+:%d B:%d C:%d D:%d F:%d\n",
            O,A1,A,B1,B,C,D,F);

    fclose(fp);
}
