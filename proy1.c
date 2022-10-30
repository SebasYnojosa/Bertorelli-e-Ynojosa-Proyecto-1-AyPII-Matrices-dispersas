#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main(void)
{
    int n,m;

    printf("Ingrese cuantas filas tendra la matriz: ");
    scanf("%d",&n);
    printf("Ingrese cuantas columnas tendra la matriz: ");
    scanf("%d",&m);
    while (n < 1 || m < 1){
        printf("\nNo se puede crear una matriz con menos de una fila y/o columna\n");
        printf("Ingrese cuantas filas tendra la matriz: ");
        scanf("%d",&n);
        printf("Ingrese cuantas columnas tendra la matriz: ");
        scanf("%d",&m);
    }
    slist* matriz = NULL;
    matriz = new_matrix(matriz,n,m);

    print_matrix(matriz);

    return 0;
}