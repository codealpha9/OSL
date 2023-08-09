#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    char directory_path[256];
    printf("Enter the path of the directory: ");
    scanf("%255s", directory_path);

    DIR *dir = opendir(directory_path);
    if (dir == NULL) {
        printf("Invalid directory path.\n");
        return 1;
    }

    struct dirent *entry;
    char *subdirectories[1000];
    int subdirectories_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == 4 && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {

            subdirectories[subdirectories_count] = strdup(entry->d_name);
            subdirectories_count++;
        }
    }
    
    closedir(dir);

    qsort(subdirectories, subdirectories_count, sizeof(char *), compare_strings);

    printf("Subdirectories in alphabetical order:\n");
    for (int i = 0; i < subdirectories_count; i++) {
        printf("%s\n", subdirectories[i]);
        free(subdirectories[i]);
    }

    return 0;
}
