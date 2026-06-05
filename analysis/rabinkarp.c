#include<stdio.h>
#include<string.h>
#include<ctype.h>

#include "rabinkarp.h"

#define MAX_TEXT 10000

long long generateHash(char str[])
{
    long long hash = 0;

    int i;

    for(i = 0; str[i] != '\0'; i++)
    {
        hash = hash * 31 + str[i];
    }

    return hash;
}

void readAndClean(
    char fileName[],
    char text[]
)
{
    FILE *fp;

    char ch;

    int index = 0;

    fp = fopen(fileName,"r");

    if(fp == NULL)
    {
        text[0] = '\0';
        return;
    }

    while((ch = fgetc(fp)) != EOF)
    {
        if(!isspace(ch))
        {
            text[index++] =
                tolower(ch);
        }
    }

    text[index] = '\0';

    fclose(fp);
}

float calculateRabinKarpSimilarity(
    char file1[],
    char file2[]
)
{
    char text1[MAX_TEXT];
    char text2[MAX_TEXT];

    int i;

    int matches = 0;

    int total;

    readAndClean(file1,text1);
    readAndClean(file2,text2);

    int len1 = strlen(text1);
    int len2 = strlen(text2);

    total = len1 > len2 ?
            len1 :
            len2;

    if(total == 0)
    {
        return 0;
    }

    for(i = 0;
        i < len1 && i < len2;
        i++)
    {
        if(text1[i] == text2[i])
        {
            matches++;
        }
    }

    return
    (
        matches * 100.0
    )
    /
    total;
}