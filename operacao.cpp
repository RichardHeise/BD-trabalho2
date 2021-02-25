#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#include "operacao.h"

int readOps(operacoes inputs, int *v) {

    int numInputs = 0;
    while( scanf("%d %d %c %c\n",&inputs[numInputs].order,
                                 &inputs[numInputs].id,
                                 &inputs[numInputs].op,
                                 &inputs[numInputs].val) == 4 ) {
        numInputs++;
    }


    for (int i = 0; i < numInputs; i++) {
        if (inputs[i].id > (*v)) {
            (*v) = inputs[i].id;
        }
    }

    return numInputs;
}

int testaSeriabilidade(operacoes inputs, int input_size, Grafo *grafo_p) {

    for(int i = 0; i < input_size; i++) {
        for(int j = i+1; j < input_size; j++) {
            if( (inputs[i].id != inputs[j].id) && (inputs[i].val == inputs[j].val) ) {

                if( (inputs[i].op == 'W') && (inputs[j].op == 'R' ) )
                    insereAresta((*grafo_p), inputs[i].id-1, inputs[j].id-1);

                if( (inputs[i].op == 'R') && (inputs[j].op == 'W' ) )
                    insereAresta((*grafo_p), inputs[i].id-1, inputs[j].id-1);

                if( (inputs[i].op == 'W') && (inputs[j].op == 'W' ) )
                    insereAresta((*grafo_p), inputs[i].id-1, inputs[j].id-1);

            }
            
        }
    }

    return !checkCiclo(*grafo_p);
}

static vector<int> converteVetor(vector<int> vetor, int tam, int num) {

    int k;

    vector<int> aux(tam, 0);
    
    k = 0;
    for (int i = 1; i < tam; i++) {
        if (vetor[i] == 1) {
            aux[k] = i;
            k++;
        }
    }
    
    return aux;
}

vector<escalonamento> separaInput(operacoes in, int tam) {

    vector<bool> vetor(tam, 0);
    vector<int> vetor_aux(tam, 0);

    vector<escalonamento> bloco; 
    escalonamento * temp = new escalonamento;

    int aux = 0;
    int abertos = 0;
    int i = 0;
    int j = 0;

    while (i < tam) {
        
        temp->num_opr = 0;
        temp->num_trans = 0;
        

        for (int v = 0; v < tam; v++) {
            vetor_aux[v] = 0;
        }
        
        do {
            
            temp->operacoes.push_back(in[i]);
            temp->num_opr++;
            
            if ( (vetor[in[i].id] != 1) && (in[i].op != 'C') ) {
                vetor[in[i].id] = 1;
                abertos++;
                vetor_aux[in[i].id] = 1;
                temp->num_trans++;
            }

            if ( (vetor[in[i].id] == 1) && (in[i].op == 'C')) {
                vetor[in[i].id] = 0;
                abertos--;
            }
            
            i++;

        } while ((abertos != 0) && (i < tam));

        bloco.push_back(*temp);
            
        bloco[j].id_trans = converteVetor(vetor_aux, tam, bloco[j].num_opr);

        j++;

        for (int w = 0; w < tam; w++) {
            aux += vetor[w];
        }
        
        if ( aux != 0) {
            perror("Transação não commitada");
            exit(NOT_COMMITED);
        }
    }

    return bloco;
}
