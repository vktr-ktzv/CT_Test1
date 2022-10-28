#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {
    FILE *popen_result;

    char buff[1024];
    popen_result = popen("pwd", "r");

    if(!popen_result){
            printf("Can't execute command\n");
        return 0;
    }

    int fd = open("File.txt", O_CREAT|| O_WRONLY, 0666);

    while(fgets(buff, sizeof(buff), popen_result) != NULL){
        write (fd, buff, sizeof(popen_result));
    }
 
    close(fd);   
    pclose(popen_result);
    return 0;
}