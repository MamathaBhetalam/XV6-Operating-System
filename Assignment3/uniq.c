#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define MAX 1024

int main(int argc, char *argv[])
{
    printf(1, "Uniq command is getting executed in user mode\n");

    // if (argc < 2)
    // {
    //     printf(1, "empty");
    //     exit();
    // }
    int fd = -1;
    int isShowCount = 0;
    int isShowDuplicates = 0;
    int isIgnoreCase = 0;
    if (strcmp(argv[1], "-c") == 0)
    {
        isShowCount = 1;
        fd = open(argv[2], O_RDONLY);
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        isShowDuplicates = 1;
        fd = open(argv[2], O_RDONLY);
    }
    else if (strcmp(argv[1], "-i") == 0)
    {
        isIgnoreCase = 1;
        fd = open(argv[2], O_RDONLY);
    }
    else if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
    }
    // else
    // {
    //     printf(1, "Invalid arguments\n");
    //     exit();
    // }

    char buff[MAX];
    int bytesRead;
    if (argc == 1)
    {
        bytesRead = read(0, buff, sizeof(buff));
    }
    else
    {
        if (fd < 0)
        {
            printf(1, "error in file");
            write(1, "\n", 1);
            exit();
        }
        bytesRead = read(fd, buff, sizeof(buff));
    }
    char current_line[512];
    char prev_line[512];
    int c = 0;
    int count = 1;
    for (int i = 0; i < bytesRead; i++)
    {
        if (buff[i] == '\n')
        {
            current_line[c] = '\0';
            if (isIgnoreCase)
            {
                char prev_line_lowercase[512] = "";
                char curr_line_lowercase[512] = "";
                strcpy(curr_line_lowercase, current_line);
                strcpy(prev_line_lowercase, prev_line);
                for (int i = 0; i < strlen(curr_line_lowercase); ++i)
                {
                    if (curr_line_lowercase[i] >= 'A' && curr_line_lowercase[i] <= 'Z')
                    {
                        curr_line_lowercase[i] = 'a' + (curr_line_lowercase[i] - 'A');
                    }
                }

                for (int i = 0; i < strlen(prev_line_lowercase); ++i)
                {
                    if (prev_line_lowercase[i] >= 'A' && prev_line_lowercase[i] <= 'Z')
                    {
                        prev_line_lowercase[i] = 'a' + (prev_line_lowercase[i] - 'A');
                    }
                }

                if (strcmp(curr_line_lowercase, prev_line_lowercase) != 0)
                {
                    if (strlen(prev_line) > 1)
                    {
                        printf(1, "%s", prev_line);
                        write(1, "\n", 1);
                        count = 1;
                    }
                }
                else
                {
                    count++;
                }
            }
            else if (strcmp(current_line, prev_line) != 0)
            {
                if (strlen(prev_line) > 1)
                {
                    if (isShowCount)
                    {
                        printf(1, "%d %s", count, prev_line);
                        write(1, "\n", 1);
                    }
                    else if (isShowDuplicates)
                    {
                        if (count > 1)
                        {
                            printf(1, "%s", prev_line);
                            write(1, "\n", 1);
                        }
                    }
                    else
                    {
                        printf(1, "%s", prev_line);
                        write(1, "\n", 1);
                    }
                    count = 1;
                }
            }
            else
            {
                count++;
            }

            strcpy(prev_line, current_line);
            memset(current_line, 0, sizeof(current_line));
            c = 0;
        }
        else
        {
            current_line[c++] = buff[i];
        }
    }
    if (isShowCount)
    {
        printf(1, "%d %s", count, prev_line);
        write(1, "\n", 1);
    }
    else if (isShowDuplicates)
    {
        if (count > 1)
        {
            printf(1, "%s", prev_line);
            write(1, "\n", 1);
        }
    }
    else
    {
        printf(1, "%s", prev_line);
        write(1, "\n", 1);
    }

    exit();
    return 0;
}
