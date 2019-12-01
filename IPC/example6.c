#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
int main ()
{
    long lForkPid; // fork process ID returned from fork()
    long lWaitPid; // exit status returned from wait()
    int iExitStatus = 0; // default exit status of wait()
    int iExit; // var for input
    char szInput[20]; 
    // create a child process
    lForkPid = fork(); // case 0 = child process, case any other int = parent process

    // Both the parent and child continue here
    switch(lForkPid)
    {
        case -1:
            errExit("fork failed: %s", strerror(errno));
            break;
        case 0:  // child process
            printf("Child Process: PID=%ld, PPID=%ld\n" // A child knows its parent
                 , (long) getpid(), (long) getppid());
            printf("Enter an exit value to continue child:");
            scanf("%d", &iExit);
            printf("Child is exiting with a %d\n", iExit);
            return iExit;
        default: // parent process
            // wait() causes the parent process to wait till one of its children exits (normally or abnormally)
            lWaitPid = wait (&iExitStatus); // jump to case 0

            if (lWaitPid == -1)
                errExit("wait error: %s", strerror(errno));
            printf("Parent Process: PID=%ld, PPID=%ld\n"
                 , (long) getpid(), (long) getppid());
            printf("Parent Process: my child's PID=%ld\n"
                 , lForkPid);
            printf("Parent Process: wait pid=%ld\n"
                 , lWaitPid);
            printf("Parent Process: exit status=%d\n"
                 , iExitStatus);
    }
    printf("My PID=%ld\n"
         , (long) getpid());
    return 0;
}
