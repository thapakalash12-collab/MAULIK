#ifndef FILE_LIST_H
#define FILE_LIST_H

#define MAX_FILES 100

extern char fileNames[MAX_FILES][256];

int loadFiles(const char *folderPath);

#endif