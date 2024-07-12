#include "types.h"
#include "user.h"
#include "date.h"
#define MAX 1024

int main() {
        int pid_uniq_u = fork();
        if (pid_uniq_u == 0) {
            // Child process: Execute uniq (user)
            char *argv[] = { "uniq", "file.txt" };
            getprocinfo1();
            exec("uniq", argv);
            
        } else {
            // Parent process: Wait for uniq to finish
            wait();
        }

        int pid_uniq_k = fork();
        if (pid_uniq_k == 0) {
            // Child process: Execute uniq (kernel)
            

            int f=open("file.txt",0);
            char buff[MAX];
            int bytesRead = read(f, buff, sizeof(buff));
            uniq("i", bytesRead, buff);
            getprocinfo1();
            exit();
        } else {
            // Parent process: Wait for head to finish
            wait();
        }

        
   // }
    exit();
}
