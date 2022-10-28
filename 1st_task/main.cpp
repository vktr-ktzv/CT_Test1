#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>

int main()
{
    for (int i = 0; i < 3; i++)
    {
        int pid = fork();
        switch(pid)
        {
            case -1:
                printf("error\n");
                break;

            case 0:
                printf("Hello from CHILD: pid - %d, ppid - %d\n", getpid(), getppid());

                break;

            default:
                printf ("It's a PARENT: pid - %d, ppid - %d\n", getpid(), getppid());
            
        }
    }

    return 0;
}