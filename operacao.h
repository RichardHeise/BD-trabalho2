#include "grafo.h"

typedef struct {
    int order;
    int id;
    char op;
    char val;
} operacao;

typedef operacao * operacoes;

int readOps(operacoes *input);

void printEscalonamento(int *out, int n);

void parseGrafo(operacoes inputs, int input_size, Grafo *graph_p);
