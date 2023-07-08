#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_DIRS 100
#define PATH_SIZE 1024

#ifndef DT_DIR
#define DT_DIR 4
#endif

char *strdup(const char *str);

int contains_git(const char *dir, char *git_directories[]) {
    DIR *dp;
    struct dirent *entry;
    int count = 0;

    dp = opendir(dir);
    if (dp == NULL) {
        perror("opendir");
        return count;
    }

    while ((entry = readdir(dp)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                char path[1024];
                snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);

                DIR *sub_directory = opendir(path);
                if (sub_directory != NULL) {
                    struct dirent *subentry;
                    while ((subentry = readdir(sub_directory)) != NULL) {
                        if (strcmp(subentry->d_name, ".git") == 0) {
                            git_directories[count] = strdup(entry->d_name);
                           count++;
                            break;
                        }
                    }
                    closedir(sub_directory);
                }
            }
        }
    }

    closedir(dp);
    return count;
}

void runGitStatus(const char *dir) {
    char path[PATH_SIZE];
    snprintf(path, sizeof(path), "%s/%s", getcwd(NULL, 0), dir);
    printf("path: %s\n", path);
    // chdir(path);  // Change to the directory for running git commands
    // system("git status");
}

int main() {
    const char *start_directory = "/home/elpatatone/Documents/";  // Starting directory (change as needed)
    char *git_directories[MAX_DIRS];
    int number_of_git_directories = contains_git(start_directory, git_directories);

    printf("Number of directories with a .git folder: %d\n", number_of_git_directories);
    printf("Directories with a .git folder:\n");
    for (int i = 0; i < number_of_git_directories; i++) {
        printf("Name: %s\n", git_directories[i]);
        runGitStatus(git_directories[i]);
        free(git_directories[i]);
    }

    return 0;
}

