/**
 * @file  grafo.h
 * @brief Arquivo com os cabeçalhos das funções de grafo.cpp
 * @date 27/02/2021
 * @author Richard Fernando Heise Ferreira (GRR20191053)
 * @author Monica Ludmila Hintz de Oliveira (GRR20159417)
 **/
 
#ifndef __grafo__
#define __grafo__

#include <iostream>
#include <vector>

// Error code
#define NOT_COMMITED -1


/** @struct grafo
 *  @brief Struct do grafo usado com os vertices das transações
 *  @var grafo::matrix
 *      Matriz de Adjacencia para inserir arcos no grafo
 *  @var grafo::V
 *      Número de vértices
 */
struct grafo {
   int V; 
	std::vector<std::vector<int>> matrix;
};

/** @type Grafo
 *  @brief Ponteiro para a struct de um grafo
 */
typedef struct grafo *Grafo;

// Cabeçalhos

/**  
 * @param int V
 * @brief Inicia um grafo com V vértices
 * @return Grafo inicializado
 */
Grafo iniciaGrafo(int V);

/**
 * @param Grafo grafo_p
 * @param int i
 * @param int j
 * @brief Função que insere aresta em um grafo.
 * i pode ser interpretado como origem e
 * j como seu destino da aresta.
 */
void insereAresta(Grafo grafo_p, int i, int j);

/**
 * @param Grafo grafo_p
 * @param int i
 * @param int j
 * @brief Função que remove aresta em um grafo.
 * i pode ser interpretado como origem e
 * j como seu destino da aresta.
 */
void removeAresta(Grafo grafo_p, int i, int j);

/**
 * @param Grafo grafo_p
 * @brief Função que imprime um grafo.
 */
void imprimeGrafo(Grafo grafo_p);

/**
 * @param Grafo grafo_p
 * @param std::vector<bool> acessados 
 * @brief Função útil para checar ciclos.
 * @return valor booleano útil para função de checar ciclos.
 */
bool checkCiclo_aux(Grafo grafo_p, std::vector<bool> acessados, int atual);

/**
 * @param Grafo grafo_p
 * @brief Função que checa um ciclo em um grafo.
 * @return Retorna se encontrou ou não um ciclo.
 */
bool checkCiclo(Grafo grafo_p);

#endif 