#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "read_ln.h"

#define SIZE 103

typedef struct pessoa {
    char nome[100];
    int idade;
} Pessoa;

int add(Pessoa person, int fd) {
    off_t registo = lseek (fd,0,SEEK_END)/sizeof (struct pessoa);
    if (registo && write(fd, &person, sizeof(struct pessoa)) > 0) return 0;
    else return 1;
    //printf("Foi inserido no registo: %zu, a idade é %d\n", registo, person.idade);
}

int read_registo(int fd, int registo) {
    Pessoa person;
    lseek (fd,registo * sizeof(struct pessoa),SEEK_CUR);
    if (read (fd,&person,sizeof (struct pessoa)) > 0) printf("Registo nr %d: Name ->  %s | Age -> %d\n", registo,person.nome,person.idade);
    else return 1;
    return 0;
}

int change_by_registo(int fd, int registo, int idade) {
    Pessoa person;
    off_t max_registo = lseek (fd,0,SEEK_END)/sizeof (struct pessoa);
    //printf ("%zu vs %d\n",max_registo,registo);
    lseek (fd,0,SEEK_SET);
    if (registo >= max_registo) {
        printf ("Registo %d não existe\n",registo);
        return 1; 
    }
    lseek(fd, registo * sizeof(struct pessoa), SEEK_CUR);  //go to position
    if (read(fd, &person, sizeof(struct pessoa)) > 0) {              //read the person to change
        lseek(fd, -sizeof(struct pessoa), SEEK_CUR);
        person.idade = idade;
        if (write(fd,&person,sizeof(struct pessoa)) < 0)return 1;
    }
    return 0;
}


int change_by_name (int fd, char *nome, int idade){
    Pessoa person;
    int found = 0;
    while (!found && read (fd,&person,sizeof(struct pessoa)))
    {
        if (!strcmp (person.nome,nome)){
            person.idade = idade;
            lseek (fd, - sizeof(struct pessoa),SEEK_CUR);
            if (write(fd,&person,sizeof(struct pessoa)) < 0)return 0;
            found = 1;
        }
    }
    return found;
}

int read_all (int fd){
    off_t registo = lseek (fd,0,SEEK_END)/sizeof (struct pessoa);
    for (off_t i = 0; i < registo; i++){
        lseek (fd,0,SEEK_SET);
        if (read_registo (fd,i) == 1) return 1;     
    }
    return 0;
}


int main(int argc, char **argv) {
    int fd = open("hello", O_RDWR, 0600);
    if (argc == 2 && argv[1][1] == 'r') {
        read_all(fd);
        close (fd);
        return 0;
    }
    if (argc != 4) {
        printf ("WRONG FORMAT\n");
        close (fd);
        return 1;
    }
    Pessoa person;
    int number = atoi (argv[2]), result = 0;
    switch (argv[1][1])
    {
    case 'i': 
        person.idade = atoi (argv[3]);
        strcpy (person.nome, argv[2]);
        add (person,fd);
        break;
    case 'u':
        if (number == 0){
            if (argv[2][0] == 0) change_by_registo (fd,0,atoi (argv[3]));
            else result = change_by_name (fd,argv[2],atoi (argv[3]));
        }
        else change_by_registo (fd,atoi(argv[2]),atoi (argv[3]));
        break;
    case 'r':
        read_all (fd);
        break;
    default:
        printf("Invalid option\n");
        break;
    }
   close (fd);
   return result;
}