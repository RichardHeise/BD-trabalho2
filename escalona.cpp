#include <stdlib.h>
#include <stdio.h>
using namespace std;

#include "operacao.h"

int main() {

    operacoes inputs;

    int ver = 0;

    inputs = readOps(&ver);

    vector<escalonamento> escalonamentos;

    escalonamentos = separaInput(inputs, inputs.size());

    /*
    //começo de debbuger
    printf("estrutura de dados:\n");
    printf("ListaEscalonamentos(tamanho = %lud):\n", escalonamentos.size());
    
    for (int i = 0 ; i < escalonamentos.size(); i++) {
        printf("Escalonamento %d possui %d transacoes: ", i+1, escalonamentos[i].num_trans);
        for (int j = 0; j < escalonamentos[i].num_trans; j++)
            printf("%d, ", escalonamentos[i].id_trans[j]);


        printf("Com %d operacoes:\n", escalonamentos[i].num_opr);
        for (int j = 0; j < escalonamentos[i].num_opr; j++)
            printf("%d %d %c %c\n", i+1, escalonamentos[i].operacoes[j].id,
            escalonamentos[i].operacoes[j].op, escalonamentos[i].operacoes[j].val);

    }
    //fim do debugger
    */
    for (int i = 0; i < escalonamentos.size(); ++i) {

        int eh_serial = testaSeriabilidade(escalonamentos[i].operacoes, ver);
        int eh_equivalente = testaEquivalencia(escalonamentos[i].operacoes);
        /*
        printf("%d ", i+1);

        for (int j = 0; j < escalonamentos[i].num_trans; j++) {
            printf("%d%c", escalonamentos[i].id_trans[j], j+1 >= escalonamentos[i].num_trans ? ' ' : ',');
        }

        if ( eh_serial ) {
            printf("SS ");
        } else {
            printf("NS ");
        }

        if ( eh_equivalente ) {
            printf("SV");
        } else {
            printf("NV");
        }
        
        printf("\n");

    */
    }
    
    return 0;
}
