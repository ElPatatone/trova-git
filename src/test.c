#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>


int main(int argc, char *argv[])
{
    printf("directory: %s", getcwd(NULL, 0));

    return 0;
}
