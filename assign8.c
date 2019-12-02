#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    // Look at fxn execl("/bin/ls", "ls", "-1", NULL); to handle 10 arguments
    // USE execvp(...) to handle your p(?) arguments by looking at $PATH to get
    //  various paths to bash commands (ls, kill, gcc, find, sed, awk, ... etc)

    // Once you execl the program (fork it) you relenquish command to it. 

    char *execArgs[30][100];    
    int i;
    int j = 0; // Row index
    int x = 0; // Column index
    int rows;

    long lForkPid, lWaitPid;
    int iExitStatus = 0;

    // Get commands and arguments and populate multi-dimensional array
    for(i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], ",") == 0)
        {
            execArgs[j][x + 1] = NULL;
            x = 0;
            j+= 1;
        }
        else
        {
            execArgs[j][x] = argv[i];
            x += 1;
        }
    // printf("%s\n", execArgs[j][x]);
    }
    
    rows = j + 1;

    printf("argc: %d\n", argc);
    printf("rows: %d\n", rows);
    
    // Split based on the args
    lForkPid = fork();

    // Both parent and child continue here
    switch(lForkPid)
    {
        case -1:
            printf("Fork Failed\n");
            return 1;
            break;
        case 0: // child process
            printf("Child Process: PID = %ld, PPID = %ld\n"
                , (long) getpid(), (long) getppid());

            // invoke a different executable for the child

            printf("%s %s\n", execArgs[0][0], execArgs[0][1]);
            execvp(execArgs[0][0], execArgs[0]);
            // TODO: ERROR HANDLING? 
        default: // parent process
            lWaitPid = wait(&iExitStatus);

            if(lWaitPid == -1){
                printf("Wait Error\n");
                return 1;
            }

            printf("Parent Process: PID = %ld, PPID = %ld\n"
                , (long) getpid(), (long) getppid()); 
            printf("Parent Process: my child's PID = %ld\n"
                , lForkPid);
            printf("Parent Process: wait pid = %ld\n"
                , lWaitPid);
            printf("Parent Process: exit status = %d\n"
                , iExitStatus);
    }

    return 0;
}
