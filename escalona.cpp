#include <stdlib.h>
#include <stdio.h>
using namespace std;

#include "operacao.h"

int main() {

    operacoes inputs = NULL;

    int ver = 0;
    int inputs_size = readOps(&inputs, &ver);
    
    Grafo grafo = iniciaGrafo(ver);

    vector<escalonamento> escalonamentos;

    escalonamentos = separaInput(inputs, inputs_size);
    /*
    //começo de debbuger
    printf("estrutura de dados:\n");
    printf("ListaEscalonamentos(tamanho = %d):\n", escalonamentos.tam);
    
    for (int i = 0 ; i < escalonamentos.tam; i++) {
        printf("Escalonamento %d possui %d transacoes: ", i+1, escalonamentos.lista[i].num_trans);
        for (int j = 0; j < escalonamentos.lista[i].num_trans; j++)
            printf("%d, ", escalonamentos.lista[i].id_trans[j]);


        printf("Com %d operacoes:\n", escalonamentos.lista[i].num_opr);
        for (int j = 0; j < escalonamentos.lista[i].num_opr; j++)
            printf("%d %d %c %c\n", i+1, escalonamentos.lista[i].operacoes[j].id,
            escalonamentos.lista[i].operacoes[j].op, escalonamentos.lista[i].operacoes[j].val);

    }*/
    //fim do debugger

    for (int i = 0; i < escalonamentos.size(); i++) {
        int eh_serial = testaSeriabilidade(escalonamentos[i].operacoes, inputs_size, &grafo);

        printf("%d ", i+1);

        for (int j = 0; j < escalonamentos[i].num_trans; j++) {
            printf("%d%c", escalonamentos[i].id_trans[j], j+1 >= escalonamentos[i].num_trans ? ' ' : ',');
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
