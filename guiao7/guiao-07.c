#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int ctrl_C_counter = 0;
int out = 0;

void ctr_C_handler (int num){
    ctrl_C_counter++;
}

void quit_hanlder (int num){
    out = 1;
    printf ("\nCTRL+C -> %d\n",ctrl_C_counter);
}

void alarm_handler (int num){
    printf ("%d\n",num);
}

int main (){
    signal (SIGALRM,alarm_handler);
    alarm (1);
    while (!out)
    {
        if (signal (SIGINT,ctr_C_handler) == SIG_ERR)
            perror ("SIGINT FAILED\n");
        if (signal(SIGQUIT,quit_hanlder) == SIG_ERR)
            perror ("SIGQUIT FAILED\n");
    }
    return 0;
}