/**
 * @file  escalona.h
 * @brief Arquivo com os cabeçalhos das funções de escalona.cpp
 * @date 27/02/2021
 * @author Richard Fernando Heise Ferreira (GRR20191053)
 * @author Monica Ludmila Hintz de Oliveira (GRR20159417)
 **/

#ifndef __escalona__
#define __escalona__
#include "operacao.h"

/**
 * @param operacoes entradas
 * @param int ver
 * @brief Função para testar a seriabilidade do das entradas
 * @return Retorna true se é serial ou false caso não seja
 */
bool testaSeriabilidade(operacoes entradas, int ver);

/**
 * @param operacoes entradas
 * @brief Função que encontra a últimas escrita em uma sequência
 * de operações
 * @return Retorna um mapa com o atributo da última escrita 
 * relacionado ao id da transação que realizou a última escrita.
 */
ultima_escrita achaEscritaFinal(operacoes entradas);

/**
 * @param operacoes entradas
 * @brief Função para retornar as demais escritas além da última.
 * @return Retorna um mapa com tempo, id, atributo relacionado com
 * o tempo e o id de cada escrita.
 */
escritas achaDemaisEscritas(operacoes entradas);

/**
 * @param operacoes entradas
 * @brief Função que testa a equivalencia de uma 
 * sequência de transações
 * @return Retorna true se é a equivalência existe e
 * retorna falso caso não seja equivalente.
 */
bool testaEquivalencia(operacoes entradas);

#endif