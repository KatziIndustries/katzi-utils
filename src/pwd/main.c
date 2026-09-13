#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char *cwd = getcwd(NULL, 0);

    if (cwd == NULL) {
        perror("pwd");
        return EXIT_FAILURE;
    }

    puts(cwd);

    free(cwd);
    return EXIT_SUCCESS;
}