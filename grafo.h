/* Vértices de grafos são representados por objetos do tipo vertice. */
#define vertice int
#define NOT_COMMITED -1

#include <iostream>
#include <vector>

struct grafo {
   int V; 
   int A;
	std::vector<std::vector<int>> matrix;
};
/* Um Graph é um ponteiro para um graph, ou seja, um Graph contém o endereço de um graph. */
typedef struct grafo *Grafo;

Grafo iniciaGrafo( int V);

void insereAresta( Grafo grafo_p, vertice i, vertice j);

void removeAresta( Grafo grafo_p, vertice i, vertice j);

void imprimeGrafo( Grafo grafo_p);

bool checkCiclo_aux( Grafo grafo_p, std::vector<bool> acessados, int atual);

int checkCiclo( Grafo grafo_p);
