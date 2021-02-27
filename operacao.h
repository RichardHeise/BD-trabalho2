#ifndef __operacao__
#define __operacao__

#include "grafo.h"
#include <map>

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

typedef map<pair<pair<int,int>,char>,pair<int,int>> escritas;

typedef map<char, int> ultima_escrita;

operacoes leEntrada(int *v);

vector<escalonamento> separaEntradas(operacoes entradas);

#endif