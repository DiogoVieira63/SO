#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>


// EXERCICIO 1

/*
int main (){
    printf ("Processo atual: %d\nProcesso pai: %d\n",getpid(),getppid());
}
*/

// EXERCICIO 2

/*
int main (){
    pid_t pid;
    int status;
    if ((pid = fork ()) == 0){
        printf ("Filho: ID eu %d\tID Pai; %d\n",getpid(),getppid());
        _exit(0);
    } 
    else{
        pid_t child = wait (&status);
        printf ("Pai: ID eu: %d\tID Filho: %d\tID PAI: %d\n",getpid(),child,getppid());
    }
}
*/

// EXERCICIO 3


//Espera pelo processo filho antes de começar uma nova iteração
//processos sequenciais
/*
int main (){
    for (int i = 1; i < 11; i++){
        if (fork ()== 0){
            printf ("Filho n%d: ID eu %d\tID Pai; %d\n",i,getpid(),getppid());
            _exit(i);
        }
        int status;
        wait (&status);
        printf ("exit_status= %d\n",WEXITSTATUS (status));
    }
}
*/

// EXERCICIO 4


// Não espera pelo processo filho antes de começar uma nova iteração
// Espera ocorre fora do ciclo, processo concorrentes
/*
int main (){
    int status;
    for (int i = 1; i < 11;i++){
        if (fork () == 0){
            _exit (i);
        }
    }
    for (int i = 1; i < 11;i++){
        wait (&status);
        printf ("exit_code: %d\n",i,WEXITSTATUS(status));
    }
}
*/

//EXERCICIO 5

/*
int main (){
    //printf ("first is %d\n",getpid());
    pid_t pid;
    for (int i = 0; i < 10; i++){
        if ((pid = fork())){
            break;
        }
    }
    int status;
    if (pid != 0){
        printf ("Process %d is waiting\n",getpid());
        wait (&status);
        printf ("Processo PAI %d, Processo filho %d\n",getpid(),pid);
        }
}

*/
//EXERCICIO 6

/*
int main(int argc, char const *argv[]) {
    int status;
    for(int i = 1; i <= 10; i++) {
        pid_t pid = getpid();
        pid_t ppid = getppid();
        printf("Process %d\nPID = %d\nParentPID = %d\n\n",i,pid,ppid);
        if(fork()) {
            int terminated_pid = wait(&status);
	    printf("Process %d exited, exit code %d.\n", terminated_pid, WEXITSTATUS(status));
            _exit(i);
        }
    }
    return 0;
}

*/

int ex_6 (int L, int C, int matriz[L][C],int number){
    int found = 0;
    int status;
    for (int i = 0; i < L && !found;i++){
        if (!fork()){
            for (int u = 0; u < C && !found;u++)
                if (matriz[i][u] == number) _exit (1);
            _exit (0);
        }
    }
    for (int i = 0; i < L && !found;i++){
        wait (&status);
        if (WEXITSTATUS(status) == 1) {
            found = 1;
        }
    }
    return found;
}

// EXERCICIO 7

int ex_7 (int L, int C,int matriz [L][C],int number){
    int status;
    pid_t array[L], pid;
    for (int i = 0; i < L; i++){
        if ((pid = (!fork ()))){
            for (int u = 0; u < C;u++)
                if (matriz[i][u] == number) _exit (1);
            _exit(0);
        }
        else array[i] = pid;
    }
    for (int i = 0; i < L;i++){
        waitpid(array[i],&status,0);
        if (WEXITSTATUS(status) == 1){
            printf("Linha %d\n",i);
        }
    }
    return 0;
}

//int ex_7v2 (int L, int C,int matriz [L][C],int number){
//    int status,result;
//    pid_t pid;
//    for (int i =0; i < L;i++){
//        if ((pid = fork ())){
//            waitpid (pid,&status,0);
//            if ((result = WEXITSTATUS(status)) != L) printf ("Linha %d\n",result);
//            for (int u = 0; u < C;u++)
//                if (number == matriz [i][u]) _exit (i);
//            _exit (L);
//        }
//    }
//    return 0;
//}


void gera_matriz (int L, int C, int matriz [L][C]);

int main (){
    int L = 10, C = 10;
    srand(time(NULL));
    int matriz [L][C];
    gera_matriz (L,C, matriz);
    int number = rand() % (C);
    printf("The number is %d\n",number);
    ex_7v2 (L,C,matriz,number);
}


void gera_matriz (int L, int C, int matriz [L][C]){
    for (int i = 0; i < L; i++){
        for (int u = 0; u < C; u++){
            matriz [i][u] = rand() % C;
            printf ("%d ",matriz[i][u]);
        }
        putchar ('\n');
    }
}

//ADICIONAL

/*
int main (){
    srand(time(NULL));
    int fd = open ("example",O_RDWR);
    int L = 10, C = 100000;
    int matriz [L][C];
    gera_matriz (L,C,matriz);
    int number = rand() % C;
    printf ("The number is %d\n",number);
    for (int i = 0; i < L; i++){
        if (write (fd,&matriz[i],sizeof (int) * C) < 1)return 1;
    }
    int new_matriz [L][C];
    lseek (fd,0,SEEK_SET);
    pid_t array_pid[L];
    pid_t pid; 
    for (int i = 0; i < L;i++){
        if (!(pid = fork ())){
            if (read (fd,&new_matriz[i],sizeof (int) * C) <= 0) return 1;
            for (int u = 0;u < C;u++)
                if (new_matriz[i][u] == number){
                    _exit (i);
                }
            _exit (-1);
        }
        else array_pid[i] = pid;
    }
    int status, count = 0;
    for (int i = 0; i < L;i++){
        waitpid(array_pid[i],&status,0);
        if (WEXITSTATUS (status) != -1){
            printf ("Linha %d\n",WEXITSTATUS(status));
            count++;
        }
    }
    printf ("foi encontrado em %d linhas\n", count);
    close(fd);
}
*/
