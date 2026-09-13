#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;
    
    for (int i = 1; i < argc; i++) {
        const char *path = argv[i];

        int fd = open(path,O_WRONLY | O_CREAT, 0666);

        if (fd == -1)
            return 1;

        close(fd);

        if (utime(path,NULL) == -1)
            return 1;
    }

    return 0;
}