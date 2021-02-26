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

typedef vector<operacao> operacoes;

operacoes readOps(int *v);

int testaSeriabilidade(operacoes inputs, int ver);

vector<escalonamento> separaInput(operacoes in, int tam);

int testaEquivalencia(operacoes inputs);
