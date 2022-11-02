#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

/* Funcion que coloca un elemento nuevo en una posicion especifica de la fila */
node* add_start_item(node* row, node* newp)
{
    if (!row)
        return newp;
    newp->next = row;
    row = newp;
    return row;
}

/* Funcion que coloca un elemento en una posicion especifica de la fila */
node* add_pos_item(node* row, node* newp, int j)
{
    node* ptr = row;
    int pos = 0;
    while (ptr->next && pos < j-2){
        if (pos < ptr->posicion_x)
            pos++;
        ptr = ptr->next;
        pos++;
    }
    newp->next = ptr->next;
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
            printf("Valor de la casilla %dx%d: ",posX+1,posY+1);
            scanf("%d",&value);
            if (value != 0){
                sptr->row = add_end_item(sptr->row,new_item(value,posX));
            }
            posX++;
        }

        matrix = add_end_row(matrix,new_ptr_row(NULL,posY++,n,m));
        sptr = sptr->next;
    }
    return matrix;
}

/* Funcion para crear una matriz con n filas y m columnas de forma automatica con valores entre 0 y 1 */
slist* new_matrix_auto(slist* matrix, int n, int m)
{
    
    register int posY = 0, posX;
    int value;
    matrix = add_end_row(matrix,new_ptr_row(NULL,0,n,m));
    slist* sptr = matrix;
    while(posY < matrix->tam_y){
        posX = 0;
        while (posX < matrix->tam_x){
            value = rand()%2;
            if (value != 0){
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
    register int posX, posY = 0;
    slist* sptr = matrix;
    while (posY < matrix->tam_y){
        node* ptr = sptr->row;
        posX = 0;
        /* Pregunta si el puntero apunta hacia algun nodo, si no es asi entonces imprime cuantos ceros dependiendo del tamanio de la fila */
        if (!ptr){
            while (posX < matrix->tam_x){
                printf("0 ");
                posX++;
            }
        } else {
            /* Bucle que se ejecuta */
            while (ptr && posX < sptr->tam_x){
                while (posX < ptr->posicion_x){
                    printf("0 ");
                    posX++;
                }
                printf("%d ",ptr->value);
                ptr = ptr->next;
                posX++;
            }
            while(posX < sptr->tam_x){
                printf("0 ");
                posX++;
            }
        }
        printf("\n");
        sptr = sptr->next;
        posY++;
    }
}

/* Muestra la matriz en forma de lista */
void print_list(slist* matrix)
{
    register int posY = 0, contfilas = 0; // contfilas contara las filas que contengan elementos distintos de cero
    slist* sptr = matrix;
    printf("Columnas de la matriz: %d\n",matrix->tam_x);
    printf("Filas de la matriz: %d\n",matrix->tam_y);
    printf("X:Y->Valor\n");
    while (posY < matrix->tam_y){
        node* ptr = sptr->row;
        /* Pregunta si el puntero apunta hacia algun nodo, si no es asi entonce se saltara directamente a la siguiente fila */
        if (ptr)
            contfilas++;
        while (ptr){
            printf("%d:%d->%d\n",ptr->posicion_x+1,posY+1,ptr->value);
            ptr = ptr->next;
        }
        sptr = sptr->next;
        posY++;
    }
    printf("Filas no nulas: %d\n",contfilas);
}

/* Multiplica todos los elementos de la matriz por un numero e */
slist* prod_esc(int e, slist* matrix, slist* matrix_res)
{
    register int posY = 0, posX;
    /* Se crea una nueva matriz que tiene el mismo tamanio que la original */
    matrix_res = add_end_row(matrix_res,new_ptr_row(NULL,0,matrix->tam_y,matrix->tam_x));
    slist* sptr1 = matrix;
    slist* sptr2 = matrix_res;
    while (posY < matrix->tam_y){
        node* ptr = sptr1->row;
        posX = 0;
        while (ptr && posX < matrix->tam_x){
            while (posX < ptr->posicion_x)
                posX++;
            sptr2->row = add_end_item(sptr2->row,new_item(ptr->value*e,posX));
            ptr = ptr->next;
            posX++;
        }
        matrix_res = add_end_row(matrix_res,new_ptr_row(NULL,posY++,matrix->tam_y,matrix->tam_x));
        sptr1 = sptr1->next;
        sptr2 = sptr2->next;
    }
    
    return matrix_res;
}

/* Busca el elemento de la matriz que esta en la fila i y la columna j */ 
int search(int i, int j, slist* matrix)
{
    register int posX = 0, posY = 0;
    slist* sptr = matrix;
    /* Se resta uno a los valores de i y j para que coincidan con las posiciones almacenadas en las estructuras */
    i--;
    j--;
    /* Bucle que recorre la columna de la matriz hasta la posicion i */
    while (posY < i){
        sptr = sptr->next;
        posY++;
    }
    node* ptr = sptr->row;
    /* Si el puntero apunta a NULL entonces significa que la fila esta compuesta de ceros, entonces devuelve un 0 */
    if (!ptr || j < ptr->posicion_x)
        return 0;
    /* Bucle que recorrera la fila en la que se encuentra sptr hasta la posicion j */
    while (ptr->next && posX < j){
        if (posX < ptr->posicion_x)
            posX++;
        ptr = ptr->next;
        posX++;
    }
    if (ptr->posicion_x != j)
        return 0;
    return ptr->value;
}

/* Asignar un valor en una posicion jxi de la matriz, y si esta contiene un cero entonces crear un nuevo nodo */
void set_value(int i, int j, int x, slist* matrix)
{
    register int posX = 0, posY = 0;
    slist* sptr = matrix;
    /* Se resta uno a los valores de i y j para que coincidan con las posiciones almacenadas en las estructuras */
    i--;
    j--;
    /* Bucle que recorre la columna de la matriz hasta la posicion i */
    while (posY < i){
        sptr = sptr->next;
        posY++;
    }
    node* ptr = sptr->row;
    /* Si no se consigue  */
    if (!ptr || j < ptr->posicion_x)
        return;
    /* Bucle que se mueve a traves de la fila hasta la posicion j */
    while (ptr->next && ptr->posicion_x < j)
        ptr = ptr->next;
    /* Se consiguio un elemento en la posicion j dada y se cambia el valor de esta */
    if (ptr->posicion_x == j){
        ptr->value = x;
    }
}
/* EN DESARROLLLO */
/* Funcion para transponer un matriz 
slist* transpose(slist* matrix, slist* matrix_trans)
{
    register int posY = 0, posX;
    register int i;
    /* Se crea una nueva matriz que tiene el tamanio contrario a la original 
    matrix_trans = add_end_row(matrix_trans,new_ptr_row(NULL,0,matrix->tam_x,matrix->tam_y));
    /* Se crea un arreglo con punteros a cada fila de la matriz original de forma que sea mas rapido accader a cada elemento 
    slist* sptr = matrix->row;
    node* ptrs[matrix->tam_y];
    for (i = 0; i < matrix->tam_y; i++){
        ptrs[i] = sptr->row;
        sptr = sptr->next;
    }
    slist* sptr2 = matrix_trans;
    while (posY < matrix_trans->tam_y){
        posX = 0;
    }
} 
/* EN DESARROLLO */