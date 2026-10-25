#include<stdio.h>
#include "report.h"
 
void generateReport(struct Result results[], int count)
{
    FILE *fp;
    int i;

    fp = fopen("../output/report.txt","w");

    if(fp == NULL)
    {
        printf("Unable to create report.txt\n");
        return;
    }

    fprintf(fp,"MAULIK ANALYSIS REPORT\n");
    fprintf(fp,"========================\n\n");

    for(i = 0; i < count; i++)
    {
        fprintf(fp,"%s <--> %s\n",
                results[i].file1,
                results[i].file2);

        fprintf(fp,"Similarity : %.2f %%\n",
                results[i].similarity);

        if(results[i].similarity >= 60)
        {
            fprintf(fp,"Risk : HIGH\n");
        }
        else if(results[i].similarity >= 30)
        {
            fprintf(fp,"Risk : MODERATE\n");
        }
        else
        {
            fprintf(fp,"Risk : LOW\n");
        }

        fprintf(fp,"\n");
    }

    fclose(fp);

    printf("Report Generated Successfully\n");
}
