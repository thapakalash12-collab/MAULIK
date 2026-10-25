#include <stdio.h>
#include <string.h> 
#include <dirent.h>

#include "file_list.h"

char fileNames[MAX_FILES][256];

int loadFiles(const char *folderPath)
{
    DIR *folder;
    struct dirent *entry;

    int count = 0;

    folder = opendir(folderPath);

    if(folder == NULL)
    {
        printf("Unable to open uploads folder\n");
        return 0;
    }

    while((entry = readdir(folder)) != NULL)
    {
        char *name = entry->d_name;

        if(
            strstr(name, ".c") != NULL ||
            strstr(name, ".cpp") != NULL ||
            strstr(name, ".java") != NULL
        )
        {
            strcpy(fileNames[count], name);
            count++;
        }
    }

    closedir(folder);

    return count;
}
