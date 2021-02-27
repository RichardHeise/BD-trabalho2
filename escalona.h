#ifndef __escalona__
#define __escalona__
#include "operacao.h"

bool testaSeriabilidade(operacoes entradas, int ver);

ultima_escrita achaEscritaFinal(operacoes entradas);

escritas achaDemaisEscritas(operacoes entradas);

bool testaEquivalencia(operacoes entradas);

#endif