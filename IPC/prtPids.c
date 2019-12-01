#include <stdio.h>
#include <unistd.h>
int main ()
{
    long lPid = getpid();   // gets process ID
    long lPPid = getppid(); // gets parent process ID
    
    printf("PID = %ld, PPID = %ld\n", lPid, lPPid);

    return 0;
}
