#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#include "operacao.h"

operacoes readOps(int *v) {

    int reads = 0;  

    operacoes inputs;
    operacao * temp = new operacao;

    reads = scanf("%d %d %c %c\n",&temp->order,
                                  &temp->id,
                                  &temp->op,
                                  &temp->val);


    while( reads == 4) {

        inputs.push_back(*temp);

        reads = scanf("%d %d %c %c\n", &temp->order,
                                       &temp->id,
                                       &temp->op,
                                       &temp->val); 
        

    }


    for (int i = 0; i < inputs.size(); i++) {
        if (inputs[i].id > (*v)) {
            (*v) = inputs[i].id;
        }
    }


    return inputs;
}

int testaSeriabilidade(operacoes inputs, int ver) {

    Grafo grafo_p = iniciaGrafo(ver);

    for(int i = 0; i < inputs.size(); i++) {
        for(int j = i+1; j < inputs.size(); j++) {

            if( (inputs[i].id != inputs[j].id) && (inputs[i].val == inputs[j].val) ) {

                if( (inputs[i].op == 'W') && (inputs[j].op == 'R' ) )
                    insereAresta(grafo_p, inputs[i].id-1, inputs[j].id-1);

                if( (inputs[i].op == 'R') && (inputs[j].op == 'W' ) )
                    insereAresta(grafo_p, inputs[i].id-1, inputs[j].id-1);

                if( (inputs[i].op == 'W') && (inputs[j].op == 'W' ) )
                    insereAresta(grafo_p, inputs[i].id-1, inputs[j].id-1);
            
            }
        }
    }

    return !checkCiclo(grafo_p);
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

vector<escalonamento> separaInput(operacoes inputs, int tam) {

    vector<bool> vetor(tam, 0);
    vector<int> vetor_aux(tam, 0);

    vector<escalonamento> bloco; 

    int aux = 0;
    int abertos = 0;
    int i = 0;
    int j = 0;

    while (i < tam) {
        
        escalonamento * temp = new escalonamento;
        temp->num_opr = 0;
        temp->num_trans = 0;

        for (int v = 0; v < tam; v++) {
            vetor_aux[v] = 0;
        }
        
        do {
            
            temp->operacoes.push_back(inputs[i]);
            temp->num_opr++;
            
            if ( (vetor[inputs[i].id] != 1) && (inputs[i].op != 'C') ) {
                vetor[inputs[i].id] = 1;
                abertos++;
                vetor_aux[inputs[i].id] = 1;
                temp->num_trans++;
            }

            if ( (vetor[inputs[i].id] == 1) && (inputs[i].op == 'C')) {
                vetor[inputs[i].id] = 0;
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

static unsigned long long fat(int val) {
    unsigned long long fatorial = 1;

    for(int i = 1; i <= val; i++) {
        fatorial *= i;
    }

    return fatorial;
}

static vector<int> removeDuplicatas(vector<int> vetor)  { 
    if (vetor.size() == 0 || vetor.size() == 1) {
        return vetor; 
    }
  
    vector<int> temp(vetor.size()); 
    
    for(int i = 0; vetor.size(); i++) {
        
    }

    for(int i = 0; i < temp.size(); i++) {
        printf("%d\n", temp[i]);
    }
    return temp; 
} 

static vector<int> getIds(operacoes inputs) {

    vector<int> temp(inputs.size());

    for (int i = 0; i < inputs.size(); i++) {
        temp[i] = inputs[i].id;
    }

    return temp;
}

int testaEquivalencia(operacoes inputs) {

    vector<int> ids(inputs.size());
    ids = getIds(inputs);

    int equivalente;

    unsigned long long fatorial = fat(ids.size());
    ids = removeDuplicatas(ids);

    /*
    for(int i = 0; i < fatorial; i++) {
        operacoes visao;
        for(int j = 0; j < ids.size(); j++) {
            for(int k = 0; k < inputs.size(); k++) {
                if (inputs[k].id == ids[j]) {
                    visao.push_back(inputs[k]);
                    printf("%d ", visao[k].id);
                }
            }
        }

        for(int j = 0; j < ids.size(); j++) {
            
        }

        next_permutation(ids.begin(), ids.end());
    }
    */
    return equivalente;
}
