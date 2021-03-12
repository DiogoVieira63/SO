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
    int status;
    for (int i = 0; i < 10; i++){
        if (fork()){//father
            wait (&status); //wait for child 
            printf ("%d -- CHILD %d AND FATHER %d \n",i,getpid (),getppid());
            _exit(0); //end current process
        }
    }
}
*/

//EXERCICIO 6/7

/*
int find_number (int L, int C, int matriz[L][C],int number){
    int found = 0;
    int status;
    for (int i = 0; i < L && !found;i++){
        if (!fork()){
            for (int u = 0; u < C && !found;u++)
                if (matriz[i][u] == number) _exit (1);
            _exit (0);
        }
    }
    for (int i = 0; i < L;i++){
        waitpid (getpid()+1+i,&status,0);
        if (WEXITSTATUS(status) == 1) {
            //found = 1; ex6
            printf ("linha %d\n",i);
        }
    }
    return found;
}

void gera_matriz (int L, int C, int matriz [L][C]);

int main (){
    srand(time(NULL));
    int matriz [10][10];
    gera_matriz (10,10, matriz);
    int number = rand() % (10);
    printf("The number is %d\n",number);
    find_number (10,10,matriz, number);
}

*/
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


int main (){
    srand(time(NULL));
    int fd = open ("example",O_RDWR);
    int L = 10, C = 10;
    int matriz [L][C];
    gera_matriz (L,C,matriz);
    int number = rand() % C;
    printf ("The number is %d\n",number);
    for (int i = 0; i < L; i++){
        if (write (fd,&matriz[i],sizeof (int) * C) < 1)return 1;
    }
    int new_matriz [L][C];
    lseek (fd,0,SEEK_SET);
    for (int i = 0; i < L;i++){
        if (!fork ()){
            if (read (fd,&new_matriz[i],sizeof (int) * C) <= 0) return 1;
            for (int u = 0;u < C;u++)
                if (new_matriz[i][u] == number){
                    printf ("%d\n",i);
                    _exit (i);
                }
            _exit (0);
        }
    }
    //for (int i = 0; i < L; i++){
    //    for (int u = 0; u < C; u++)printf ("%d ",new_matriz[i][u]);
    //    putchar ('\n');
    //}
        
    
    int status, count = 0;
    for (int i = 0; i < L;i++){
        waitpid(getpid () +1+i,&status,0); //espera pelo processo de forma crescente
        //wait (&status);
        if (WEXITSTATUS (status) != 0){
            printf ("Linha %d\n",WEXITSTATUS(status));
            count++;
        }
    }
    printf ("foi encontrado em %d linhas\n", count);
    close(fd);
}

