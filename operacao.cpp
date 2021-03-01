/**
 * @file  operacao.cpp
 * @brief Arquivo com as implementações de operação.
 * @date 27/02/2021
 * @author Richard Fernando Heise Ferreira (GRR20191053)
 * @author Monica Ludmila Hintz de Oliveira (GRR20159417)
 **/

#include "operacao.h"
#include <algorithm>

using namespace std;

operacoes leEntrada(int *v) {

    int lidos = 0;  

    operacoes inputs;
    operacao * temp = new operacao;

    // le a entrada
    lidos = scanf("%d %d %c %c\n",&temp->order,
                                  &temp->id,
                                  &temp->op,
                                  &temp->val);


    // le as entradas e as coloca em um vetor
    while( lidos == 4) {

        inputs.push_back(*temp);

        lidos = scanf("%d %d %c %c\n", &temp->order,
                                       &temp->id,
                                       &temp->op,
                                       &temp->val); 
        

    }

    // o maior id é o número de vértices do grafo
    for (int i = 0; i < inputs.size(); i++) {
        if (inputs[i].id > (*v)) {
            (*v) = inputs[i].id;
        }
    }


    return inputs;
}

/* =============================================================================================== */

static vector<int> converteVetor(vector<int> vetor) {

    int k;

    vector<int> aux(vetor.size(), 0);
    
    k = 0;

    // pega os ids das transações
    for (int i = 1; i < vetor.size(); i++) {
        if (vetor[i] == 1) {
            aux[k] = i;
            k++;
        }
    }
    // reorganiza o aux[]
    aux.resize(k);
    sort(aux.begin(), aux.end());    
    return aux;
}

/* =============================================================================================== */

vector<escalonamento> separaEntradas(operacoes entradas) {

    // declarações
    vector<bool> vetor(entradas.size(), 0);
    vector<int> vetor_aux(entradas.size(), 0);
    vector<escalonamento> bloco; 

    int countCommitados = 0;
    int abertos = 0;
    int i = 0;
    int j = 0;

    while (i < entradas.size()) {
        
        escalonamento * temp = new escalonamento;
        temp->num_opr = 0;
        temp->num_trans = 0;

        // zera um vetor
        for (int k = 0; k < vetor_aux.size(); k++) {
            vetor_aux[k] = 0;
        }
        
        do {

            temp->operacoes.push_back(entradas[i]);
            temp->num_opr++;

            // abre uma transação      
            if ( (vetor[entradas[i].id] != 1) && (entradas[i].op != 'C') ) {

                vetor[entradas[i].id] = 1;
                abertos++;
                vetor_aux[entradas[i].id] = 1;
                temp->num_trans++;
            }

            // fecha uma transação
            if ( (vetor[entradas[i].id] == 1) && (entradas[i].op == 'C')) {
                vetor[entradas[i].id] = 0;
                abertos--;
            }
            
            i++;

        } while ((abertos != 0) && (i < entradas.size()));

        // coloca temp no bloco
        bloco.push_back(*temp);
            
        // armazena vetor de ids
        bloco[j].id_trans = converteVetor(vetor_aux);

        j++;

        // conta se passamos por todas as trasações
        for (int k = 0; k < vetor.size(); k++) {
            countCommitados += vetor[k];
        }
        
        if ( countCommitados != 0) {
            perror("Transação não commitada");
            exit(NOT_COMMITED);
        }
    }

    return bloco;
}

/* =============================================================================================== */
