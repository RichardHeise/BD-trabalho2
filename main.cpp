#include "escalona.h"
using namespace std;

int main() {

    operacoes entradas;

    int ver = 0;

    entradas = leEntrada(&ver);

    vector<escalonamento> escalonamentos;

    escalonamentos = separaEntradas(entradas);

    for (int i = 0; i < escalonamentos.size(); ++i) {

        bool eh_serial = testaSeriabilidade(escalonamentos[i].operacoes, ver);
        bool eh_equivalente = testaEquivalencia(escalonamentos[i].operacoes);
        
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
