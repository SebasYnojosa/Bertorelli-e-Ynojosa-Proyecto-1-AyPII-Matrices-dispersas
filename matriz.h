#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct Node{
    int value;
    int posicion_x;
    struct Node* next;
}node;

typedef struct SuperLista{
    node* row;
    int posicion_y;
    int tam_y;
    int tam_x;
    struct SuperLista* next;
}slist;

/* Funcion que permitira crear un nuevo elemento de la matriz con su posicion */
node* new_item(int value, int posX);

/* Funcion que permite crear un nuevo puntero a una fila en la columna principal */
slist* new_ptr_row(node* row, int posY, int n, int m);

/* Funcion que coloca el elemento recien creado al final de la lista */
node* add_end_item(node* row, node* newp);

/* Funcion que coloca la fila recien creada al final de la columna de la matriz */
slist* add_end_row(slist* matrix, slist* newr);

/* Funcion para crear una matriz con n filas y m columnas */
slist* new_matrix(slist* matrix, int n, int m);

/* Muestra la matriz en la pantalla incluyendo los ceros */
void print_matrix(slist* matrix);

#endif // MATRIZ_H