#include "grafo.h"

typedef struct {
    int order;
    int id;
    char op;
    char val;
} operacao;

typedef struct {
    int *id_trans;
    int num_trans;
    operacao *operacoes;
    int num_opr;
} escalonamento;

typedef struct {
    escalonamento *lista;
    int tam;
} lista_esc;

typedef operacao * operacoes;

int readOps(operacoes *input, int *v);

int testaSeriabilidade(operacoes inputs, int input_size, Grafo *graph_p);

lista_esc separaInput(operacao *in, int tam);
