/**
 * @file  operacao.h
 * @brief Arquivo com os cabeçalhos das funções de operacao.cpp
 * @date 27/02/2021
 * @author Richard Fernando Heise Ferreira (GRR20191053)
 * @author Monica Ludmila Hintz de Oliveira (GRR20159417)
 **/

#ifndef __operacao__
#define __operacao__

#include "grafo.h"
#include <map>

using namespace std;

/** @struct operacao
 *  @brief Estrutura para armazenar dados de uma operacao
 *  @var operacao::order
 *      Tempo de entrada da operacao
 *  @var operacao::id
 *      Identificador da transação 
 *  @var operacao::op
 *      Tipo de operação realizada durante a transação
 *  @var operacao::val
 *      Atributo operado na operação
 */
typedef struct {
    int order;
    int id;
    char op;
    char val;
} operacao;

/** @struct escalonamento
 *  @brief Estrutura para manter os dados de um escalonamento
 *  @var escalonamento::id_trans
 *      Vetor de ids de transação
 *  @var escalonamento::num_trans
 *      Valor inteiro para o num total de transações
 *  @var escalonamento::operacoes
 *      Vetor que guarda as operações
 *  @var escalonamento::num_opr
 *      Valor inteiro para o num total de operações
 */
typedef struct {
    vector<int> id_trans;
    int num_trans;
    vector<operacao> operacoes;
    int num_opr;
} escalonamento;

/** @type vector<operacao> 
 *  @brief Operacoes é um vetor de operacao
 */
typedef vector<operacao> operacoes;

/** @type pair<pair<int,int>,char>
 *  @brief chave de uma escrita genérica
 */
typedef pair<pair<int,int>,char> chave;

/** @type map<char, int>
 *  @brief Mapa de uma operacão para uma transação
 *  especificamente usado como última escrita de uma
 *  visão.
 */
typedef map<char, int> ultima_escrita;

/** @type map<chave,pair<int,int>>
 *  @brief Mapa para uma escrita genérica
 */ 
typedef map<chave,pair<int,int>> escritas;

/**
 * @param int *v
 * @brief Recebe um ponteiro para vértices
 * que será alterado por referência
 * @return Retorna um vetor com as operacoes
 */
operacoes leEntrada(int *v);

/** @param operacoes entradas
 *  @brief Função que separa as entradas em um
 *  escalonamento individual
 *  @return Retorna um vetor de escalonameto
 */
vector<escalonamento> separaEntradas(operacoes entradas);

#endif