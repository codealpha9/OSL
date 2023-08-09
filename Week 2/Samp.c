#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

void printdir(char *dir, int depth) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if ((dp = opendir(dir)) == NULL) {
        fprintf(stderr, "Cannot open directory: %s\n", dir);
        return;
    }

    chdir(dir);

    while ((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name, &statbuf);

        if (S_ISDIR(statbuf.st_mode)) {
            if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0) {
                continue;
            }

            printf("%*s%s/\n", depth, "", entry->d_name);
            
            // Recurse at a new indent level
            printdir(entry->d_name, depth + 4);
        } else {
            printf("%*s%s\n", depth, "", entry->d_name);
        }
    }

    chdir("..");
    closedir(dp);
}

int main() {
    printdir(".", 0); // Start traversal from the current directory
    return 0;
}
