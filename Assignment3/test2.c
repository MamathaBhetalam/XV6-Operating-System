#include "types.h"
#include "user.h"
#include "date.h"
#define MAX 1024

int main(int argc, char* argv[]) {
    if (argc == 2 && atoi(argv[1]) == 1) {
        printf(1, "Kernel process has a higher priority than user process\n\n");
        int pid_uniq_k = fork();
        if (pid_uniq_k == 0) {
            // Child process: Execute uniq (kernel)
            printf(1, "-- pid for uniq (kernel): %d --\n", changepriority(getpid(), 3));
            int f=open("file.txt",0);
            char buff[MAX];
            int bytesRead = read(f, buff, sizeof(buff));
            uniq("i", bytesRead, buff);
            exit();
        } else {
            // Parent process: Wait for uniq(kernel) to finish
            wait();
        }
        int pid_uniq_u = fork();
        if (pid_uniq_u == 0) {
            // Child process: Execute uniq (user)
            printf(1, "-- pid for uniq (user): %d --\n", changepriority(getpid(), 5));
            char *argv[] = { "uniq", "file.txt" };
            exec("uniq", argv);
        } else {
            // Parent process: Wait for uniq (user) to finish
            wait();
        }
    } 
    else if (argc == 2 && atoi(argv[1]) == 2)
    {

        printf(1, "User process has a higher priority than user process\n\n");
        int pid_uniq_u = fork();
        if (pid_uniq_u == 0) {
            // Child process: Execute uniq (user)
            printf(1, "-- pid for uniq (user): %d --\n", changepriority(getpid(), 3));
            char *argv[] = { "uniq", "file.txt" };
            exec("uniq", argv);
        } else {
            // Parent process: Wait for uniq to finish
            wait();
        }

        int pid_uniq_k = fork();
        if (pid_uniq_k == 0) {
            // Child process: Execute uniq (kernel)
            printf(1, "-- pid for uniq (kernel): %d --\n", changepriority(getpid(), 5));
            int f=open("file.txt",0);
            char buff[MAX];
            int bytesRead = read(f, buff, sizeof(buff));
            uniq("i", bytesRead, buff);
            exit();
        } else {
            // Parent process: Wait for head to finish
            wait();
        }

        
    }
    exit();
}
