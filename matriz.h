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

/* Funcion que coloca un elemento nuevo en una posicion especifica de la fila */
node* add_start_item(node* row, node* newp);

/* Funcion que coloca un elemento en una posicion especifica de la fila */
node* add_pos_item(node* row, node* newp, int j);

/* Funcion que coloca la fila recien creada al final de la columna de la matriz */
slist* add_end_row(slist* matrix, slist* newr);

/* Funcion para crear una matriz con n filas y m columnas */
slist* new_matrix(slist* matrix, int n, int m);

/* Funcion para crear una matriz con n filas y m columnas de forma automatica con valores entre 0 y 1 */
slist* new_matrix_auto(slist* matrix, int n, int m);

/* Muestra la matriz en la pantalla incluyendo los ceros */
void print_matrix(slist* matrix);

/* Muestra la matriz en forma de lista */
void print_list(slist* matrix);

/* Multiplica todos los elementos de la matriz por un numero e */
slist* prod_esc(int e, slist* matrix, slist* matrix_res);

/* Busca el elemento de la matriz que esta en la fila i y la columna j */
int search(int i, int j, slist* matrix);

/* Asignar un valor en una posicion ixj de la matriz */
void set_value(int i, int j, int x, slist* matrix);

/* Funcion para transponer un matriz */
void transpose(slist* matrix, slist* matrix_trans);

/* Funcion suma de matrices */
slist* suma_matrix(slist* matrix, slist* matrix2);

#endif // MATRIZ_H
