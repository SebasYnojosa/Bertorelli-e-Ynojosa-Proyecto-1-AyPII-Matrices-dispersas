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
slist* prod_esc(int e, slist* matrix)
{
    register int posY = 0, posX;
    /* Se crea una nueva matriz que tiene el mismo tamanio que la original */
    slist* matrix_res = NULL;
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

slist* suma_matrix(slist* matrix, slist* matrix2)
{
    if (!matrix || !matrix2){
        fprintf(stderr,"No se pueden sumar matrices si alguna es nula\n");
        exit(1);
    }
    if (matrix->tam_x != matrix2->tam_x || matrix->tam_y != matrix2->tam_y){
        fprintf(stderr,"No se pueden sumar matrices con distintas dimensiones\n");
    }
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

slist* transpose(slist* matrix){
    slist* matrix_trans = add_end_row(matrix_trans,new_ptr_row(NULL,0,matrix->tam_x,matrix->tam_y));
    slist* actual, *prev, *aux;
    node* ptr;
    register int X;
    // Para cada fila de la matriz original
    for (actual = matrix; actual; actual = actual->next)
        // Para cada columna de esta fila
        for (ptr = actual->row; ptr; ptr = ptr->next){
            X = ptr->posicion_x;
            // Se busca en la transpuesta la fila correspondiente a la posicion x de la columna
            prev = NULL;
            for (aux = matrix_trans; aux && aux->posicion_y <= X; aux = aux->next)
                prev = aux;
            // Si se consiguio la fila, quedara en prev
            // Se inserta al final la columna correspondiente
            if (prev && prev->posicion_y == X)
                prev->row = add_end_item(prev->row,new_item(ptr->value,actual->posicion_y));
            // En caso de no conseguirse, se crea entre prev y aux
            else {
                slist* sptr = new_ptr_row(NULL,X,matrix_trans->tam_y,matrix_trans->tam_x);
                if (prev)
                    prev->next = sptr;
                else 
                    matrix_trans = sptr;
                sptr->next = aux;
                sptr->row = add_end_item(sptr->row,new_item(ptr->value,actual->posicion_y));
            }
        }
    return matrix_trans;

}

/* Funcion para multiplicar dos matrices */
slist* mult_mat(slist* matrix1, slist* matrix2){
    if (!matrix1 || !matrix2){
        fprintf(stderr,"No se pueden multiplicar matrices si alguna es nula\n");
        exit(1);
    }
    if (matrix1->tam_x != matrix2->tam_y){
        fprintf(stderr,"El tamanio de x en la primera matriz debe ser igual al tamanio en y de la segunda matriz\n");
        exit(1);
    }
    // Usamos la transpuesta de la matriz 2 para tener acceso mas rapido por filas
    slist* matriz2_trans = transpose(matrix2);

    slist* mult_matrix = add_end_row(mult_matrix,new_ptr_row(NULL,0,matrix1->tam_y,matrix2->tam_x));
    node* ptr1, *ptr2, *ptr_prod = mult_matrix->row;

}