#include <stdlib.h>
#include <stdio.h>

#include "operacao.h"

int main() {

    operacoes inputs = NULL;

    int ver = 0;
    int inputs_size = readOps(&inputs, &ver);
    
    Grafo grafo = iniciaGrafo(ver);

    lista_esc e;
    e = separaInput(inputs, inputs_size);
    /*
    //começo de debbuger
    printf("estrutura de dados:\n");
    printf("ListaEscalonamentos(tamanho = %d):\n", e.tam);
    
    for (int i = 0 ; i < e.tam; i++) {
        printf("Escalonamento %d possui %d transacoes: ", i+1, e.lista[i].num_trans);
        for (int j = 0; j < e.lista[i].num_trans; j++)
            printf("%d, ", e.lista[i].id_trans[j]);


        printf("Com %d operacoes:\n", e.lista[i].num_opr);
        for (int j = 0; j < e.lista[i].num_opr; j++)
            printf("%d %d %c %c\n", i+1, e.lista[i].operacoes[j].id,
            e.lista[i].operacoes[j].op, e.lista[i].operacoes[j].val);

    }*/
    //fim do debugger

    for (int i = 0; i < e.tam; i++) {
        int eh_serial = testaSeriabilidade(e.lista[i].operacoes, inputs_size, &grafo);

        printf("%d ", i+1);

        for (int j = 0; j < e.lista[i].num_trans; j++) {
            printf("%d%c", e.lista[i].id_trans[j], j+1 >= e.lista[i].num_trans ? ' ' : ',');
        }

        if ( eh_serial ) {
            printf("SS ");
        } else {
            printf("NS ");
        }

        printf("\n");

        grafo = iniciaGrafo(ver);

    }


    return 0;
}
