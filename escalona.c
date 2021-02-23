#include <stdlib.h>
#include <stdio.h>

#include "operacao.h"

int main() {

    operacoes inputs = NULL;
    int inputs_size = readOps(&inputs);
     
    Grafo grafo = iniciaGrafo(inputs_size);
    parseGrafo(inputs, inputs_size, &grafo);

    imprimeGrafo(grafo);


    return 0;
}
