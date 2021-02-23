#include <stdlib.h>
#include <stdio.h>

#include "operacao.h"

int main() {

    operacoes inputs = NULL;

    int ver = 0;
    int inputs_size = readOps(&inputs, &ver);
    
    Grafo grafo = iniciaGrafo(ver);

    separaInput(&inputs, inputs_size);

    imprimeGrafo(grafo);


    return 0;
}
