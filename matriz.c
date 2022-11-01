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

slist* suma_matrix(slist* matrix, slist* matrix2)
{
    register int X, Y = 0;
    int value;
    slist* sptr = matrix;
    slist* sptr2 = matrix2;
    slist* matrix3 = NULL;
    matrix3 = add_end_row(matrix3,new_ptr_row(NULL,0,matrix->tam_y,matrix->tam_x));/*Creacion de la matriz resultante*/
    slist* sptr3 = matrix3;/*Super lista(matriz)*/
    while (Y < matrix->tam_y){
        node* ptr = sptr->row;
        node* ptr2 = sptr2->row;
        X = 0;
        while (X < matrix->tam_x && ptr != NULL || ptr2 != NULL){
            /*Comprobar si alguna fila es nula, si es nula poner el valor de la que no sea nula*/
            if(!ptr){
                while (X < sptr2->tam_x){
                    value=ptr2->value;
                    ptr2 = ptr2->next;
                    if (value != 0){
                        sptr3->row = add_end_item(sptr3->row,new_item(value,X));/*Agrego un nuevo nodo a la fila*/
                    }
                    X++;
                }
            }else if(!ptr2){
                while (X < sptr->tam_x){
                    value=ptr->value;
                    ptr = ptr->next;
                    if (value != 0){
                        sptr3->row = add_end_item(sptr3->row,new_item(value,X));
                    }
                    X++;
                }
            }else if(ptr->posicion_x==ptr2->posicion_x && X < ptr->posicion_x){
                X++;
            }else if(ptr->posicion_x==ptr2->posicion_x){
                value=(ptr->value)+(ptr2->value);
                ptr = ptr->next;
                ptr2 = ptr2->next;
                if (value != 0){
                    sptr3->row = add_end_item(sptr3->row,new_item(value,X));
                }
                X++;
            }else{
                /*Si la posicion del primero es menor al segundo significa que el primero se sumara con 0*/
                if(ptr->posicion_x<ptr2->posicion_x){
                    value=ptr->value;
                    ptr = ptr->next;
                /*Si la posicion del segundo es menor al primero significa que el segundo se sumara con 0*/
                }else{
                    value=ptr2->value;
                    ptr2 = ptr2->next;
                }
                if (value != 0){
                    sptr3->row = add_end_item(sptr3->row,new_item(value,X));
                }
                X++;
            }
        }
        matrix3 = add_end_row(matrix3,new_ptr_row(NULL,Y++,matrix->tam_y,matrix->tam_x));/*Agrego una nueva fila*/
        sptr = sptr->next;
        sptr2 = sptr2->next;
        sptr3 = sptr3->next;
    }
    return matrix3;
}
