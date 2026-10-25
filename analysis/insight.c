#include<stdio.h>
#include "insight.h"

void generateInsight(struct Result results[], int count)
{
    FILE *fp;

    int i;
    int maxIndex = 0;

    fp = fopen("../output/ai_insight.txt","w");

    if(fp == NULL)
    {
        printf("Unable to create ai_insight.txt\n");
        return;
    }

    if(count <= 0)
    {
        fprintf(fp,"No comparisons available.\n");
        fclose(fp);
        return;
    }

    for(i = 1; i < count; i++)
    {
        if(results[i].similarity >
           results[maxIndex].similarity)
        {
            maxIndex = i;
        }
    }

    fprintf(fp,"MAULIK AI ANALYSIS\n");
    fprintf(fp,"====================\n\n");

    fprintf(fp,"Most Suspicious Pair\n\n");

    fprintf(fp,"%s <--> %s\n\n",
            results[maxIndex].file1,
            results[maxIndex].file2);

    fprintf(fp,"Similarity : %.2f %%\n\n",
            results[maxIndex].similarity);

    if(results[maxIndex].similarity >= 60)
    {
        fprintf(fp,"Risk : HIGH\n\n");

        fprintf(fp,
        "Recommendation : Strong similarity detected. Manual review recommended.\n\n");

        fprintf(fp,
        "Final Verdict : Potential Code Reuse Detected\n");
    }
    else if(results[maxIndex].similarity >= 30)
    {
        fprintf(fp,"Risk : MODERATE\n\n");

        fprintf(fp,
        "Recommendation : Similarity review recommended.\n\n");

        fprintf(fp,
        "Final Verdict : Similarity Review Recommended\n");
    }
    else
    {
        fprintf(fp,"Risk : LOW\n\n");

        fprintf(fp,
        "Recommendation : No major similarity detected.\n\n");

        fprintf(fp,
        "Final Verdict : No Significant Similarity Detected\n");
    }

    fclose(fp);

    printf("AI Insight Generated Successfully\n");
}
