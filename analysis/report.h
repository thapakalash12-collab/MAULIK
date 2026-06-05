#ifndef REPORT_H
#define REPORT_H

struct Result
{
    char file1[256];
    char file2[256];
    float similarity;
};

void generateReport(struct Result results[], int count);

#endif