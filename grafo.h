/* Vértices de grafos são representados por objetos do tipo vertice. */
#define vertice int

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS: A estrutura graph representa um grafo. O campo adj é um ponteiro para a matriz de adjacências do grafo. O campo V contém o número de vértices e o campo A contém o número de arcos do grafo. */
struct grafo {
   int V; 
   int A; 
   int **matrix; 
};
/* Um Graph é um ponteiro para um graph, ou seja, um Graph contém o endereço de um graph. */
typedef struct grafo *Grafo;

Grafo iniciaGrafo( int V);

void insereAresta( Grafo grafo_p, vertice i, vertice j);

void removeAresta( Grafo grafo_p, vertice i, vertice j);

void imprimeGrafo( Grafo grafo_p);

int checkCiclo_aux(Grafo grafo_p, int* acessados, int atual);

int checkCiclo(Grafo grafo_p);