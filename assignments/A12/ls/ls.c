#include "ls.h"
// You may not need all these headers ...
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

// Use this function to display the files. DO NOT CHANGE IT.
void _printLine(unsigned int size, unsigned int sizeOnDisk, const char* name)
{
    printf("%010u   %010u   %s\n", size, sizeOnDisk, name);
}

// Assume this to be the maximum length of a file name returned by readdir
#define MAX_FILE_NAME_LENGTH 255

int list(const char* path, const char *filterByExtension)
{
    DIR *dir = opendir(path); //returns a pointer to the first file
    if (dir == NULL) {
        perror("Fehler beim Öffnen des Verzeichnisses");
        return -1;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue; // Bricht den aktuellen Schleifendurchlauf ab und springt zum nächsten readdir
        }
        if (filterByExtension != NULL) {
            const char* dot = strchr(entry->d_name, '.');
            if (dot == NULL) {
                continue;
            }
            if (strcmp(dot+1, filterByExtension) != 0) {
                continue;
            }
        }
        printf("Gefunden: %s\n", entry->d_name);
    }
    closedir(dir);
    return 0;
}
