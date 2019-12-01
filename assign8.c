#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

int main(int argc, char *argv[]){
    // Look at fxn execl("/bin/ls", "ls", "-1", NULL); to handle 10 arguments
    // USE execvp(...) to handle your p(?) arguments by looking at $PATH to get
    //  various paths to bash commands (ls, kill, gcc, find, sed, awk, ... etc)

    // Once you execl the program (fork it) you relenquish command to it. 

    char argBuffer[100][100]; // [0][0] = cmd name, [0][0+] = cmd args
    int i, j; // used for row and column
    for(i = 1; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    printf("argc: %d\n", argc);
    return 0;
}
