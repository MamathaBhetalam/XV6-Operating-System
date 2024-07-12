#include "types.h"
#include "user.h"
#include "date.h"
#define MAX 1024

int main() {
    int startTimeUniq=0, endTimeUniq, startTimeHead=0, endTimeHead;

    int pid_uniq = fork();
    if (pid_uniq == 0) {
        // Child process: Execute uniq
        int s;
        startTimeUniq=getproccreationtime(getpid());
        s=startTimeUniq;
        int f=open("file.txt",0);
        char buff[MAX];
        int bytesRead = read(f, buff, sizeof(buff));
        uniq("i", bytesRead, buff);
        endTimeUniq = uptime();
        int e=endTimeUniq;
        printf(1,"uniq creation time:%d ",startTimeUniq);
        printf(1,"uniq end time: %d ",endTimeUniq);
        // Print total time for uniq
        printf(1,"Total execution time: %d\n",e-s);
        exit();
    } else {
        // Parent process: Wait for uniq to finish
        wait();
    }

    int pid_head = fork();
    if (pid_head == 0) {
        // Child process: Execute head
       
        int s;
        startTimeHead=getproccreationtime(getpid());
        s=startTimeHead;
        int f=open("file.txt",0);
        char buff[MAX];
        int bytesRead = read(f, buff, sizeof(buff));
        head(10, bytesRead, buff);
        endTimeHead = uptime();
        int e=endTimeHead;
        printf(1,"Head creation time:%d ",startTimeHead);

        printf(1,"Head end time:%d ",endTimeHead);
        // Print total time for head
        printf(1,"Total execution time: %d\n",e-s);
        exit();
    } else {
        // Parent process: Wait for head to finish
        wait();
        
    }

    exit();
}
