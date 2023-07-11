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

void runGitStatus(const char *dir, const char *start_directory) {
    char path[PATH_SIZE];
    snprintf(path, sizeof(path), "%s/%s", start_directory, dir);
    chdir(path);
    system("git status > .git_status_output");

    FILE *status_file = fopen(".git_status_output", "r");
    if (status_file == NULL) {
        perror("fopen");
        return;
    }

    char line[PATH_SIZE];
    int modified = 0;
    int deleted = 0;

    while (fgets(line, sizeof(line), status_file) != NULL) {
        if (strstr(line, "modified:") || strstr(line, "deleted: ")) {
            modified = 1;
            break;
        }
    }

    fclose(status_file);
    remove(".git_status_output");

    if (modified || deleted) {
        printf("--------------------------------------------------------------------------------------\n");
        printf("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
        printf("--------------------------------------------------------------------------------------\n");
        printf("\n\e[1mName: %s\e[0m\n", dir);
        printf("\e[1mPath: %s\e[0m\n", path);
        system("git status");
    }
}

int main() {

    FILE *config_file;
    char directory[100] = "";
    config_file = fopen("config.txt", "r");
    if (config_file != NULL) {
        fgets(directory, sizeof(directory), config_file);
        // Remove newline character if present
        if (directory[strlen(directory) - 1] == '\n') {
            directory[strlen(directory) - 1] = '\0';
        }
        fclose(config_file);
    }

    // const char *start_directory = "/home/elpatatone/Documents";  // Starting directory (change as needed)
    char *git_directories[MAX_DIRS];
    int number_of_git_directories = contains_git(directory, git_directories);
    printf("Number of directories with a .git folder: %d\n", number_of_git_directories);
    for (int i = 0; i < number_of_git_directories; i++) {
        runGitStatus(git_directories[i], directory);
        free(git_directories[i]);
    }

    return 0;
}

