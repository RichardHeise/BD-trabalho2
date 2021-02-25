#include "grafo.h"

typedef struct {
    int order;
    int id;
    char op;
    char val;
} operacao;

typedef struct {
    vector<int> id_trans;
    int num_trans;
    vector<operacao> operacoes;
    int num_opr;
} escalonamento;

typedef struct {
    vector<escalonamento> lista;
} lista_esc;

typedef operacao * operacoes;

int readOps(operacoes *input, int *v);

int testaSeriabilidade(operacoes inputs, int input_size, Grafo *graph_p);

lista_esc separaInput(operacao *in, int tam);
