#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAXTOKENS 5000
#define MAXTOKENLEN 50

void extractTokens(char fileName[],
                   char tokens[][MAXTOKENLEN],
                   int *count)
{
    FILE *fp;

    char ch;
    char token[MAXTOKENLEN];

    int index = 0;

    *count = 0;

    fp = fopen(fileName,"r");

    if(fp == NULL)
    {
        return;
    }

    while((ch = fgetc(fp)) != EOF)
    {
        if(isalnum(ch) || ch == '_')
        {
            token[index++] = tolower(ch);

            if(index >= MAXTOKENLEN-1)
            {
                index = MAXTOKENLEN-2;
            }
        }
        else
        {
            if(index > 0)
            {
                token[index] = '\0';

                strcpy(tokens[*count],token);

                (*count)++;

                index = 0;

                if(*count >= MAXTOKENS)
                {
                    break;
                }
            }
        }
    }

    fclose(fp);
}

float calculateSimilarity(char file1[], char file2[])
{
    char tokens1[MAXTOKENS][MAXTOKENLEN];
    char tokens2[MAXTOKENS][MAXTOKENLEN];

    int count1;
    int count2;

    int i;
    int j;

    int matches = 0;

    extractTokens(file1,tokens1,&count1);
    extractTokens(file2,tokens2,&count2);

    for(i=0;i<count1;i++)
    {
        for(j=0;j<count2;j++)
        {
            if(strcmp(tokens1[i],tokens2[j]) == 0)
            {
                matches++;
                break;
            }
        }
    }

    if(count1 + count2 == 0)
    {
        return 0;
    }

    return (2.0 * matches * 100.0) / (count1 + count2);
}