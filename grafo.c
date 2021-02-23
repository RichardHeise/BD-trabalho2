#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

// Implementação com base em: https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html


/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função MATRIXint() aloca uma matriz com linhas 0..r-1 e colunas 0..c-1. Cada elemento da matriz recebe valor val. */
static int **alocaMatriz( int lin, int col, int val) { 
   int **mat = malloc( lin * sizeof (int *));

   for (vertex i = 0; i < lin; ++i) 
      mat[i] = malloc( col * sizeof (int));

   for (vertex i = 0; i < lin; ++i)
      for (vertex j = 0; j < col; ++j)
         mat[i][j] = val;

   return mat;
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função Grafoinit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */
Grafo iniciaGrafo( int vertices) { 
   Grafo G = malloc( sizeof *G);
   G->V = vertices; 
   G->A = 0;
   G->matrix = alocaMatriz( vertices, vertices, 0);
   return G;
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GrafoinsertArc() insere um arco v-w no grafo G. A função supõe que v e w são distintos, positivos e menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */
void insereAresta( Grafo G, vertex i, vertex j) { 
   if (G->matrix[i][j] == 0) {
      G->matrix[i][j] = 1; 
      G->A++;
   }
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GraforemoveArc() remove do grafo G o arco v-w. A função supõe que v e w são distintos, positivos e menores que G->V. Se não existe arco v-w, a função não faz nada. */
void removeAresta( Grafo G, vertex i, vertex j) { 
   if (G->matrix[i][j] == 1) {
      G->matrix[i][j] = 0; 
      G->A--;
   }
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função Grafoshow() imprime, para cada vértice v do grafo G, em uma linha, todos os vértices adjacentes a v. */
void imprimeGrafo( Grafo G) { 
   for (vertex i = 0; i < G->V; ++i) {
      printf( "%2d:", i);

      for (vertex j = 0; j < G->V; ++j)
         if (G->matrix[i][j] == 1) 
            printf( " %2d", j);

      printf( "\n");
   }
}

/* utilidade para a função de detecção de ciclo */
int detectaCiclo_util(Grafo G, int* visitados, int atual) {
	if (visitados[atual])
		return 1;

	visitados[atual] = 1;
	int flag = 0;
	for (int i = 0; i < G->V; ++i) {
		if (G->matrix[atual][i] == 1) {
			flag = detectaCiclo_util(G, visitados, i);
			if (flag) {
				visitados[atual] = 0;
				return 1;
			}
		}
	}
	visitados[atual] = 0;
	return 0;
}
/* detecta ciclo no grafo */
int detectaCiclo(Grafo G) {
	int visitados[G->V];
	int flag = 0;
	for (int i = 0; i < G->V; ++i)
		visitados[i] = 0;

	for(int i = 0; i < G->V; ++i) {
		visitados[i] = 1;
		for (int j = 0; j < G->V; ++j) {
			if (G->matrix[i][j] == 1) {
				flag = detectaCiclo_util(G, visitados, j);
				if (flag)
					return 1;
			}
		}
		visitados[i] = 0;
	}
	return 0;
}