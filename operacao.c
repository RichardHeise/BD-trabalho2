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

void parseGrafo(operacoes inputs, int input_size, Grafo *grafo_p) {

    for(int i = 0; i < input_size; i++) {
        for(int j = i+1; j < input_size; j++) {
            if( (inputs[i].id != inputs[j].id) && (inputs[i].val == inputs[j].val) ) {

                if( (inputs[i].op == 'W') && (inputs[j].op == 'R' ) )
                    insereAresta((*grafo_p), inputs[i].id-1, inputs[j].id-1);

                if( (inputs[i].op == 'R') && (inputs[j].op == 'W' ) )
                    insereAresta((*grafo_p), inputs[i].id-1, inputs[j].id-1);

                if( (inputs[i].op == 'W') && (inputs[j].op == 'W' ) )
                    insereAresta((*grafo_p), inputs[i].id-1, inputs[j].id-1);

                //if ( (inputs[i].id == inputs[j].id) && inputs[j].op == 'C') {
                //    break;
                //}
            }
        }
    }
}

