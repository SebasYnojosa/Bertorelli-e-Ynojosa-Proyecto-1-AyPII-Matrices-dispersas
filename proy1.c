#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matriz.h"

int main(void)
{
    srand(time(NULL));
    int n,m,x,elec;
    slist* matriz1 = NULL;
    slist* matriz2 = NULL;
    slist* matriz_esc2 = NULL;

    /* Creacion de la matriz */
    printf("Ingrese las dimensiones de la matriz que quiere crear\n");
    printf("Columnas: ");
    scanf("%d",&m);
    printf("Filas: ");
    scanf("%d",&n);
    
    do{
        printf("Como desea crear la matriz\n");
        printf("(1) De forma manual\n");
        printf("(2) De forma automatica con valores 0 y 1\n");
        printf("Eleccion: ");
        scanf("%d",&elec);
        if (elec == 1)
            matriz1 = new_matrix(matriz1,n,m);
        else if(elec == 2)
            matriz1 = new_matrix_auto(matriz1,n,m);
        printf("\r");
    } while (elec < 1 || elec > 2);

    elec = 0;
    do{
        printf("Como quiere mostrar la matriz\n");
        printf("(1) En forma cuadrada\n");
        printf("(2) En forma de lista\n");
        printf("Eleccion: ");
        scanf("%d",&elec);
        if (elec == 1)
            print_matrix(matriz1);
        else if (elec == 2)
            print_list(matriz1);
        printf("\r");
    } while (elec < 1 || elec > 2);

    /* Multiplicar una matriz */
    printf("Valor para multiplicar la matriz: ");
    scanf("%d",&x);
    slist* matriz_esc1 = prod_esc(x,matriz1);

    printf("\n");
    print_matrix(matriz_esc1);

    /* Transponer la matriz */
    slist* matriz_trans = transpose(matriz1);

    printf("\n");
    print_matrix(matriz_trans);

   

    return 0;
}