#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    char *execArgs[30][100];    
    int i, j = 0, x = 0;
    int rows, status;
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
            printf("PID: %ld, PPID: %ld, CMD: %s \n"
                , (long) getpid(), (long) getppid(), execArgs[i][0]);
            execvp(execArgs[i][0], execArgs[i]);
            return 0;
        }
    }
    
    while (rows > 0){
        pid = wait(&status);
        --rows;
    }
}
