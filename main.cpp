/**
 * @file  main.cpp
 * @brief Arquivo principal com a solução do software.
 * @date 27/02/2021
 * @author Richard Fernando Heise Ferreira (GRR20191053)
 * @author Mônica Ludmila Hintz de Oliveira (GRR20159417)
 **/

#include "escalona.h"
using namespace std;

int main() {

    // entradas é um vetor de operacao
    operacoes entradas;

    // quantidade de vértices do grafo
    int ver = 0;

    // escreve a quantidade de vértices em ver
    entradas = leEntrada(&ver);

    // escalonamentos é um vetor de escalonamento
    vector<escalonamento> escalonamentos;

    // separa por commits cada escalonamento
    escalonamentos = separaEntradas(entradas);

    // percorre o vetor de escalonamento
    for (int i = 0; i < escalonamentos.size(); ++i) {

        // verificações
        bool eh_serial = testaSeriabilidade(escalonamentos[i].operacoes, ver);
        bool eh_equivalente = testaEquivalencia(escalonamentos[i].operacoes);
        
        // prints de saída
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
    }
    
    return 0;
}
