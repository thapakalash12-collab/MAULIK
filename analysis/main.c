#include<stdio.h>
#include<string.h>

#include "file_list.h"
#include "similarity.h"
#include "rabinkarp.h"
#include "statistics.h"
#include "report.h"
#include "insight.h"

#define MAX_RESULTS 1000

int main()
{
    int totalFiles;

    int i;
    int j;

    int count = 0;

    float similarities[MAX_RESULTS];

    int high;
    int moderate;
    int low;

    struct Result results[MAX_RESULTS];

    char path1[300];
    char path2[300];

    float tokenSim;
    float rabinSim;

    totalFiles = loadFiles("../uploads");

    printf("====================================\n");
    printf("MAULIK SOURCE CODE SIMILARITY SYSTEM\n");
    printf("====================================\n");

    printf("Total Files Loaded : %d\n\n",
           totalFiles);

    for(i = 0; i < totalFiles; i++)
    {
        for(j = i + 1; j < totalFiles; j++)
        {
            sprintf(path1,
                    "../uploads/%s",
                    fileNames[i]);

            sprintf(path2,
                    "../uploads/%s",
                    fileNames[j]);

            tokenSim =
            calculateSimilarity(
                path1,
                path2
            );

            rabinSim =
            calculateRabinKarpSimilarity(
                path1,
                path2
            );

            results[count].similarity =
            (
                0.6 * tokenSim
            )
            +
            (
                0.4 * rabinSim
            );

            strcpy(
                results[count].file1,
                fileNames[i]
            );

            strcpy(
                results[count].file2,
                fileNames[j]
            );

            similarities[count] =
            results[count].similarity;

            count++;
        }
    }

    calculateStatistics(
        similarities,
        count,
        &high,
        &moderate,
        &low
    );

    generateReport(
        results,
        count
    );

    generateInsight(
        results,
        count
    );

    FILE *dash;

    dash =
    fopen(
        "../output/dashboard_data.txt",
        "w"
    );

    if(dash != NULL)
    {
        fprintf(
            dash,
            "%d\n",
            totalFiles
        );

        fprintf(
            dash,
            "%d\n",
            count
        );

        fprintf(
            dash,
            "%d\n",
            high
        );

        fprintf(
            dash,
            "%d\n",
            moderate
        );

        fprintf(
            dash,
            "%d\n",
            low
        );

        fclose(dash);
    }

    printf("\n");
    printf(
        "Total Comparisons : %d\n",
        count
    );

    printf(
        "High Risk : %d\n",
        high
    );

    printf(
        "Moderate Risk : %d\n",
        moderate
    );

    printf(
        "Low Risk : %d\n",
        low
    );

    printf(
        "\nReport Generated Successfully\n"
    );

    printf(
        "AI Insight Generated Successfully\n"
    );

    printf(
        "Dashboard Data Generated Successfully\n"
    );

    printf(
        "\nAnalysis Completed Successfully\n"
    );

    return 0;
}