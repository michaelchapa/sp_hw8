#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    char *execArgs[30][100];    
    int i;
    int j = 0; // Row index
    int x = 0; // Column index
    int rows;
    int status;
    pid_t pid;

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
    }
    
    rows = j + 1;

    // fork()
    pid_t pids[rows]; 
    
    for(i = 0; i < rows; i++){
        if((pids[i] = fork()) < 0){
            printf("Error\n");
            abort();
        } else if (pids[i] == 0){
            printf("PID: %ld, PPID: %ld, CMD: \n", (long) getpid(), (long) getppid());
            execvp(execArgs[i][0], execArgs[i]);
            // printf("PID: %ld, PPID: %ld, CMD: \n", (long) getpid(), (long) getppid());
            return 0;
        }
    }
    
    while (rows > 0){
        // printf("PID: %ld, PPID: %ld, CMD: \n", (long) getpid(), (long) getppid());
        pid = wait(&status);
        --rows;
    }
}
