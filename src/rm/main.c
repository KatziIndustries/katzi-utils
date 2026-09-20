#define _XOPEN_SOURCE 700

#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int force = 0;

static int remove_entry(const char *path, const struct stat *sb,
                         int typeflag, struct FTW *ftwbuf)
{
    (void)sb;
    (void)ftwbuf;

    if (typeflag == FTW_D)
        return rmdir(path);

    return unlink(path);
}

int rm_rf(const char *path)
{
    return nftw(path, remove_entry, 64, FTW_DEPTH | FTW_PHYS);
}

int main(int argc, char **argv)
{
    int recursive = 0;
    int force_flag = 0;

    int i = 1;

    for (; i < argc; i++) {
        if (argv[i][0] != '-')
            break;

        for (int j = 1; argv[i][j]; j++) {
            switch (argv[i][j]) {
                case 'r':
                case 'R':
                    recursive = 1;
                    break;

                case 'f':
                    force_flag = 1;
                    break;

                case '-':
                    break;

                default:
                    fprintf(stderr, "rm: unknown option -- '%c'\n",
                            argv[i][j]);
                    return 1;
            }
        }
    }

    if (i >= argc) {
        if (!force_flag)
            fprintf(stderr, "rm: missing operand\n");
        return force_flag ? 0 : 1;
    }

    int ret = 0;

    for (; i < argc; i++) {
        const char *path = argv[i];

        if (recursive) {
            if (rm_rf(path) != 0) {
                if (!force_flag)
                    perror(path);
                ret = 1;
            }
        } else {
            if (unlink(path) != 0) {
                if (!force_flag)
                    perror(path);
                ret = 1;
            }
        }
    }

    return ret;
}