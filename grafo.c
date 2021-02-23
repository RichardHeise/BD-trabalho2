#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

// Implementação com base em: https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html


/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função MATRIXint() aloca uma matriz com linhas 0..r-1 e colunas 0..c-1. Cada elemento da matriz recebe valor val. */
static int **alocaMatriz( int lin, int col, int val) { 
   int **mat = malloc( lin * sizeof (int *));

   for (vertice i = 0; i < lin; ++i) 
      mat[i] = malloc( col * sizeof (int));

   for (vertice i = 0; i < lin; ++i)
      for (vertice j = 0; j < col; ++j)
         mat[i][j] = val;

   return mat;
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função Grafoinit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */
Grafo iniciaGrafo( int vertices) { 
   Grafo grafo_p = malloc( sizeof *grafo_p);
   grafo_p->V = vertices; 
   grafo_p->A = 0;
   grafo_p->matrix = alocaMatriz( vertices, vertices, 0);
   return grafo_p;
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GrafoinsertArc() insere um arco v-w no grafo G. A função supõe que v e w são distintos, positivos e menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */
void insereAresta( Grafo grafo_p, vertice i, vertice j) { 
   if (grafo_p->matrix[i][j] == 0) {
      grafo_p->matrix[i][j] = 1; 
      grafo_p->A++;
   }
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função GraforemoveArc() remove do grafo G o arco v-w. A função supõe que v e w são distintos, positivos e menores que G->V. Se não existe arco v-w, a função não faz nada. */
void removeAresta( Grafo grafo_p, vertice i, vertice j) { 
   if (grafo_p->matrix[i][j] == 1) {
      grafo_p->matrix[i][j] = 0; 
      grafo_p->A--;
   }
}
/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A função Grafoshow() imprime, para cada vértice v do grafo G, em uma linha, todos os vértices adjacentes a v. */
void imprimeGrafo( Grafo grafo_p) { 
   for (vertice i = 0; i < grafo_p->V; ++i) {
      printf( "%2d:", i+1);

      for (vertice j = 0; j < grafo_p->V; ++j)
         if (grafo_p->matrix[i][j] == 1) 
            printf( " %2d", j+1);

      printf( "\n");
   }
}

int checkCiclo_aux(Grafo grafo_p, int* acessados, int atual) {
	if (acessados[atual])
		return 1;

	acessados[atual] = 1;
	int flag = 0;
	for (int i = 0; i < grafo_p->V; ++i) {
		if (grafo_p->matrix[atual][i] == 1) {
			flag = checkCiclo_aux(grafo_p, acessados, i);
			if (flag) {
				acessados[atual] = 0;
				return 1;
			}
		}
	}
	acessados[atual] = 0;
	return 0;
}
int checkCiclo(Grafo grafo_p) {
	int acessados[grafo_p->V];
	int flag = 0;
	for (int i = 0; i < grafo_p->V; ++i)
		acessados[i] = 0;

	for(int i = 0; i < grafo_p->V; ++i) {
		acessados[i] = 1;
		for (int j = 0; j < grafo_p->V; ++j) {
			if (grafo_p->matrix[i][j] == 1) {
				flag = checkCiclo_aux(grafo_p, acessados, j);
				if (flag)
					return 1;
			}
		}
		acessados[i] = 0;
	}
	return 0;
}