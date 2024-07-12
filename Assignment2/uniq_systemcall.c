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
    char *option = "0";
    if (strcmp(argv[1], "-c") == 0)
    {
        option = "c";
        fd = open(argv[2], O_RDONLY);
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        option = "d";
        fd = open(argv[2], O_RDONLY);
    }
    else if (strcmp(argv[1], "-i") == 0)
    {
        option = "i";
        fd = open(argv[2], O_RDONLY);
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

    uniq(option, bytesRead, buff);

    exit();
    return 0;
}
