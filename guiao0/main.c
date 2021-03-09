#include "function.h"
#include <stdio.h>
#include <stdlib.h>

int array[4000]; //global variable


int main (){
    //int array[4000]; //automatic variable
    //int *array = malloc(4000 * sizeof(int)); 
    fill(array,4000,2);
    find (array+1000,1000,2);//pesquisa entre o array 1000 e 2000
    fill (&array[1000],1000,0);//mudar os valores entre 1000 e 2000
    for (int i = 0; i < 4000;i+=100)printf("%d -> %d\n",i,array[i]);
    //free (array);
}