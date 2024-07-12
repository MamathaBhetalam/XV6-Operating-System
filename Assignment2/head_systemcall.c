#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define MAX 1024

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf(1, "empty");
        exit();
    }

    int fd = -1;
    int printcount = 14;

    if (argv[1][0] == '-')
    {
        printcount = atoi(argv[2]);
        fd = open(argv[3], O_RDONLY);
    }
    else
    {
        fd = open(argv[1], O_RDONLY);
    }

    if (fd < 0)
    {
        printf(1, "error in file");
        exit();
    }

    char buff[MAX];
    // char final[MAX] = "";
    int bytesRead = read(fd, buff, sizeof(buff));

    head(printcount, bytesRead, buff);

    exit();
    return 0;
}
