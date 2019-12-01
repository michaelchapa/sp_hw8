#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
int main ()
{
    long lForkPid;
    // a variable to demonstrate each process has their own copy
    long lMyVal = 10;

    // create a child process
    lForkPid = fork();

    // Both the parent and child continue here
    switch(lForkPid)
    {
        case -1:
            printf("Fork Failed\n");
            return 1;
            break;
        case 0:  // child process
            lMyVal += 5;
            printf("CHILD SUCCESS:\n");
            printf("Child Process: PID=%ld, PPID=%ld\n\n"
                 , (long) getpid(), (long) getppid());
            break;
        default: // parent process
            printf("RUNNING PARENT PROCESS:\n");
            printf("Parent Process: PID=%ld, PPID=%ld\n"
                 , (long) getpid(), (long) getppid());
            sleep(2);
            printf("Parent Process: my child's PID=%ld\n\n"
                 , lForkPid);
    }

    lMyVal += 5;
    printf("My PID=%ld, lMyVal=%ld\n"
         , (long) getpid(), lMyVal);
    return 0;
}
