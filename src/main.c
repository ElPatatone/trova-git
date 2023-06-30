#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

int main() {
    DIR *dir;
    char current_dir[PATH_MAX];

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        printf("Unable to open directory.\n");
        return 1;
    }

    // Get the path of the current directory
    if (getcwd(current_dir, sizeof(current_dir)) != NULL) {
        printf("Current directory path: %s\n", current_dir);
    } else {
        printf("Unable to get current directory path.\n");
    }

    // Close the directory
    closedir(dir);

    return 0;
}
