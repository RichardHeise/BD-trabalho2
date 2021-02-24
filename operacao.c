#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operacao.h"

int readOps(operacoes *input, int *v) {
    int max = 64;
    (*input) = (operacoes) malloc(sizeof(operacao)*max);
    int numInputs = 0;

    while( scanf("%d %d %c %c\n",&(*input)[numInputs].order,
                                 &(*input)[numInputs].id,
                                 &(*input)[numInputs].op,
                                 &(*input)[numInputs].val) == 4 ) {

        numInputs++;

        if(numInputs >= max) {
            max+=10;
            (*input) = (operacoes) realloc((*input), sizeof(operacao)*max);
        }
    }

    for (int i = 0; i < numInputs; i++) {
        if ((*input)[i].id > (*v)) {
            (*v) = (*input)[i].id;
        }
    }

    (*input) = (operacoes) realloc((*input), sizeof(operacao)*numInputs);

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

int *converteVetor(int *vetor, int tam, int num) {

    int *aux, k;

    aux = (int *)malloc(num*(sizeof(int)));

    k = 0;
    for (int i = 1; i <= tam; i++) {
        if (vetor[i] == 1) {
            aux[k] = i;
            k++;
        }
    }
    return aux;
}

lista_esc separaInput(operacao *in, int tam) {

    int *vetor;

    int abertos = 0;
    vetor = malloc(tam * sizeof(int));

    int aux, *vetor_aux;

    for (int i = 0; i < tam; i++) {
        vetor[i] = 0;
    }

    lista_esc escal;

    escal.lista = malloc(tam * sizeof(lista_esc));
    escal.tam = 0;

    int i = 0;
    int j = 0;
    vetor_aux = malloc(tam * sizeof(int));

    while (i < tam) {

        escal.lista[j].num_trans = 0;
        escal.lista[j].num_opr = 0;
        escal.lista[j].operacoes = malloc(tam * sizeof(lista_esc));

        escal.tam += 1;

        for (int v = 0; v < tam; v++) {
            vetor_aux[v] = 0;
        }

        do {

            escal.lista[j].operacoes[escal.lista[j].num_opr] = in[i];
            escal.lista[j].num_opr++;

            if ( (vetor[in[i].id] != 1) && (in[i].op != 'C') ) {
                vetor[in[i].id] = 1;
                abertos++;
                vetor_aux[in[i].id] = 1;
                escal.lista[j].num_trans++;
            }

            if ( (vetor[in[i].id] == 1) && (in[i].op == 'C')) {
                vetor[in[i].id] = 0;
                abertos--;
            }

            i++;

        } while ((abertos != 0) && (i < tam));

        escal.lista[j].id_trans = converteVetor(vetor_aux, tam, escal.lista[j].num_opr);

        j++;

        aux=0;
        for (int w = 0; w < tam; w++) {
            aux += vetor[w];
        }
        
        if ( aux != 0) {
            perror("Transação não commitada");
        }
    }

    return escal;
}
