#ifndef __grafo__
#define __grafo__

#define NOT_COMMITED -1

#include <iostream>
#include <vector>

struct grafo {
   int V; 
   int A;
	std::vector<std::vector<int>> matrix;
};

typedef struct grafo *Grafo;

Grafo iniciaGrafo( int V);

void insereAresta( Grafo grafo_p, int i, int j);

void removeAresta( Grafo grafo_p, int i, int j);

void imprimeGrafo( Grafo grafo_p);

bool checkCiclo_aux( Grafo grafo_p, std::vector<bool> acessados, int atual);

bool checkCiclo( Grafo grafo_p);

#endif 