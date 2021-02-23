#include "grafo.h"

typedef struct {
    int order;
    int id;
    char op;
    char val;
} operacao;

typedef operacao * operacoes;

int readOps(operacoes *input, int *v);

void parseGrafo(operacoes inputs, int input_size, Grafo *graph_p);
