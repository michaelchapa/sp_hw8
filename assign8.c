#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

int main(int argc, char *argv[]){
    // Look at fxn execl("/bin/ls", "ls", "-1", NULL); to handle 10 arguments
    // USE execvp(...) to handle your p(?) arguments by looking at $PATH to get
    //  various paths to bash commands (ls, kill, gcc, find, sed, awk, ... etc)

    // Once you execl the program (fork it) you relenquish command to it. 

    char *execArgs[30][100];    
    int i;
    int j = 0; // used for row and column
    int rows = 0, column; // get size of commands and arguments

    for(i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], ",") == 0)
        {
            j+= 1;
        }
        else
        {
            execArgs[j][i] = argv[i];
        }
    }

    printf("argc: %d\n", argc);
    printf("ROWS: %d\n", j);

    return 0;
}
