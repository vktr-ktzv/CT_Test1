#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

struct msgbuff
{
    long mtype;
    char mtext[80];
};

static void
send_msg(int qid, int msgtype)
{
    struct msgbuff msg;
    time_t t;

    msg.mtype = msgtype;

    time(&t);
    //snprintf(msg.mtext, sizeof(msg.mtext), "a message at %s",
    //ctime(&t));

    if (msgsnd(qid, &msg, sizeof(msg.mtext), IPC_NOWAIT) == -1) 
    {
        perror("msgsnd error");
        exit(EXIT_FAILURE);
    }
    printf("sent: %s\n", msg.mtext);
}

static int
get_msg(int qid, char* buff)
{
    struct msgbuff msg;

    if (msgrcv(qid, &msg, sizeof(msg.mtext), 0, MSG_NOERROR | IPC_NOWAIT) == -1) 
    {
        if (errno != ENOMSG) 
        {
            perror("msgrcv");
            return 0;
            //exit(EXIT_FAILURE);
        }
        printf("No message available for msgrcv()\n");
    } else
    {
        printf("message received: %s\n", msg.mtext);
        strcpy(buff, msg.mtext);
        return msg.mtype;
    }
}

int main ()
{
    char buf [100];
    int qid, opt;
    int mode = 0;               /* 1 = send, 2 = receive */
    int msgtype = 1;
    int msgkey = ftok("first.cpp", 1234);

    qid = msgget(msgkey, IPC_CREAT | 0666);

    if (qid == -1) 
    {
        perror("msgget");
        exit(EXIT_FAILURE);
        printf("here\n");
    }

    //get_msg(qid, msgtype);
    /*while (true)
    {
        if(get_msg(qid, buf) == 2)
        {
            printf("Get message type 2. Break\n");
            break;
        };
    }*/
    get_msg(qid, buf);
    FILE *popen_result;

    char buff[1024];
    popen_result = popen(buf, "r");

    if(!popen_result){
            printf("Can't execute command\n");
        return 0;
    }

    

     while(fgets(buff, sizeof(buff), popen_result)!=NULL){
        printf("%s", buff);
     }
 
     
    pclose(popen_result);

    
     
    return 0;
}