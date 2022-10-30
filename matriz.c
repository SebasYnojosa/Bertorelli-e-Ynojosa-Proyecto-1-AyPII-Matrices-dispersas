#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

/* Funcion que permitira crear un nuevo elemento de la matriz con su posicion */
node* new_item(int value, int posX)
{
    node* newp = (node*)malloc(sizeof(node));
    newp->value = value;
    newp->posicion_x = posX;
    newp->next = NULL;
}

/* Funcion que permite crear un nuevo puntero a una fila en la columna principal */
slist* new_ptr_row(node* row, int posY, int n, int m)
{
    slist* newr = (slist*)malloc(sizeof(slist));
    newr->row = row;
    newr->posicion_y = posY;
    newr->tam_y = n;
    newr->tam_x = m;
    newr->next = NULL;
}

/* Funcion que coloca el elemento recien creado al final de la lista */
node* add_end_item(node* row, node* newp)
{
    node* ptr;
    if (row == NULL)
        return newp;
    for (ptr = row; ptr->next != NULL; ptr = ptr->next);
    ptr->next = newp;
    return row;
}

/* Funcion que coloca la fila recien creada al final de la columna de la matriz */
slist* add_end_row(slist* matrix, slist* newr)
{
    slist* sptr;
    if (matrix == NULL)
        return newr;
    for (sptr = matrix; sptr->next != NULL; sptr = sptr->next);
    sptr->next = newr;
    return matrix;
}

/* Funcion para crear una matriz con n filas y m columnas */
slist* new_matrix(slist* matrix, int n, int m)
{
    register int posY = 0, posX; 
    int value;

    matrix = add_end_row(matrix,new_ptr_row(NULL,0,n,m));
    slist* sptr = matrix;
    while(posY < matrix->tam_y){
        posX = 0;
        while (posX < matrix->tam_x){
            printf("Valor de la casilla %dx%d: ",posX,posY);
            scanf("%d",&value);
            if (value > 0){
                sptr->row = add_end_item(sptr->row,new_item(value,posX));
            }
            posX++;
        }

        matrix = add_end_row(matrix,new_ptr_row(NULL,posY++,n,m));
        sptr = sptr->next;
    }
    return matrix;
}

/* Muestra la matriz en la pantalla incluyendo los ceros */
void print_matrix(slist* matrix)
{
    register int X, Y = 0;
    slist* sptr = matrix;
    while (Y < matrix->tam_y){
        node* ptr = sptr->row;
        X = 0;
        /* Pregunta si el puntero apunta hacia algun nodo, si no es asi entonces imprime cuantos ceros dependiendo del tamanio de la fila */
        if (!ptr){
            while (X < matrix->tam_x){
                printf("0 ");
                X++;
            }
        } else {
            while (ptr && X < matrix->tam_x){
                while (X < ptr->posicion_x){
                    printf("0 ");
                    X++;
                }
                printf("%d ",ptr->value);
                ptr = ptr->next;
                X++;
            }
            while(X < matrix->tam_x){
                printf("0 ");
                X++;
            }
        }
        printf("\n");
        sptr = sptr->next;
        Y++;
    }
}
