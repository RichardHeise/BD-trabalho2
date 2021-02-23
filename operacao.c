#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operacao.h"

int readOps(operacoes *input) {
    int max = 64;
    (*input) = (operacoes) malloc(sizeof(operacao)*max);
    int n = 0;

    while( scanf("%d %d %c %c\n",&(*input)[n].order,
                                 &(*input)[n].id,
                                 &(*input)[n].op,
                                 &(*input)[n].val) == 4 ) {

        n++;

        if(n >= max) {
            max+=10;
            (*input) = (operacoes) realloc((*input), sizeof(operacao)*max);
        }
    }
    (*input) = (operacoes) realloc((*input), sizeof(operacao)*n);

    return n;
}

void printEscalonamento(int *out, int n) {
    for(int i = 0; i < n; i++)
        printf("%d%c", out[i]+1, i+1 >= n ? ' ' : ',');
}

void parseGrafo(operacoes inputs, int input_size, Grafo *graph_p) {

    for(int i = 0; i < input_size; i++) { 
        for(int j = i+1; j < input_size; j++) {
            if( (inputs[i].id != inputs[j].id) && (inputs[i].val == inputs[j].val) ){
                if( (inputs[i].op == 'W') && ( inputs[j].op == 'R' ) )
                    insereAresta((*graph_p), i, j);
                if( (inputs[i].op == 'R') && ( inputs[j].op == 'W' ) )
                    insereAresta((*graph_p), i, j); 
                if( (inputs[i].op == 'W') && ( inputs[j].op == 'W' ) )
                    insereAresta((*graph_p), i, j); 
            }
        }
    }
}

