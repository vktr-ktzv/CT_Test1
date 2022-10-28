#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuff
{
    long mtype;
    char mtext[80];
};

void send_msg(int qid, int msgtype)
{
    struct msgbuff msg = {};
    time_t t;
    char buf[100] = {};

    msg.mtype = msgtype;

    if (msgtype == 1)
    {
        printf("Input text:\n");
        
        //scanf("%s", buf);
        fgets(buf, 100, stdin);
       
    }

    //time(&t);
    snprintf(msg.mtext, sizeof(msg.mtext), "%s", buf);

    if (msgsnd(qid, &msg, sizeof(msg.mtext), IPC_NOWAIT) == -1) 
    {
        perror("msgsnd error");
        exit(EXIT_FAILURE);
    }
    printf("sent: %s\n", msg.mtext);
}
/*static void
get_msg(int qid, int msgtype)
{
    struct msgbuff msg;

    if (msgrcv(qid, &msg, sizeof(msg.mtext), msgtype, MSG_NOERROR | IPC_NOWAIT) == -1) 
    {
        if (errno != ENOMSG) 
        {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }
        printf("No message available for msgrcv()\n");
    } else
        printf("message received: %s\n", msg.mtext);
}*/

int main ()
{
    int qid, opt;
    int mode = 0;               /* 1 = send, 2 = receive */
    int msgtype = 1;
    int msgkey = ftok("first.cpp", 1234);;

    qid = msgget(msgkey, IPC_CREAT | 0666);

    if (qid == -1) 
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    
    
    send_msg(qid, 1);

    send_msg(qid, 2);
     
    return 0;
}