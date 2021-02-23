/* Vértices de grafos são representados por objetos do tipo vertex. */
#define vertex int

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A estrutura graph representa um grafo. O campo adj é um ponteiro para a matriz de adjacências do grafo. O campo V contém o número de vértices e o campo A contém o número de arcos do grafo. */
struct grafo {
   int V; 
   int A; 
   int **matrix; 
};
/* Um Graph é um ponteiro para um graph, ou seja, um Graph contém o endereço de um graph. */
typedef struct grafo *Grafo;

Grafo iniciaGrafo( int V);

void insereAresta( Grafo G, vertex v, vertex w);

void removeAresta( Grafo G, vertex v, vertex w);

void imprimeGrafo( Grafo G);

int detectaCiclo_util(Grafo G, int* visitados, int atual);

int detectaCiclo(Grafo G);