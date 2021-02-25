#include "grafo.h"
using namespace std;

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

typedef operacao * operacoes;

int readOps(operacoes *input, int *v);

int testaSeriabilidade(vector<operacao> inputs, int input_size, Grafo *graph_p);

vector<escalonamento> separaInput(operacao *in, int tam);
