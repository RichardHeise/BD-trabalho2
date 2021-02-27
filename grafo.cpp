#include "grafo.h"
using namespace std;

// Implementação com base em: https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html

Grafo iniciaGrafo(int V) { 
	Grafo grafo_p = new grafo;
	grafo_p->V = V;
	grafo_p->A = 0;
	vector<int> linha(V, 0);
	for (int i = 0; i < V; ++i)
		grafo_p->matrix.push_back(linha);
	return grafo_p;
}

void insereAresta(Grafo grafo_p, int i, int j) {
	grafo_p->matrix[i][j] = 1;
}

void removeAresta(Grafo grafo_p, int i, int j) {
	grafo_p->matrix[i][j] = 0;
}

void imprimeGrafo(Grafo grafo_p) {
	for (int i = 0; i < grafo_p->V; ++i) {
		cout << i << ": ";
		for (int j = 0; j < grafo_p->V; ++j)
			if (grafo_p->matrix[i][j])
				cout << j << " ";
		cout << endl;
	}
}

bool checkCiclo_aux(Grafo grafo_p, vector<bool> acessados, int atual) {
	if (acessados[atual])
		return true;

	acessados[atual] = true;
	bool flag = false;
	for (int i = 0; i < grafo_p->V; ++i) {
		if (grafo_p->matrix[atual][i] == 1) {
			flag = checkCiclo_aux(grafo_p, acessados, i);
			if (flag) {
				acessados[atual] = false;
				return true;
			}
		}
	}
	acessados[atual] = false;
	return false;
}

bool checkCiclo(Grafo grafo_p) {
	vector<bool> acessados(grafo_p->V, 0);
	bool flag = false;

	for(int i = 0; i < grafo_p->V; ++i) {
		acessados[i] = true;
		for (int j = 0; j < grafo_p->V; ++j) {
			if (grafo_p->matrix[i][j] == 1) {
				flag = checkCiclo_aux(grafo_p, acessados, j);
				if (flag)
					return true;
			}
		}
		acessados[i] = false;
	}
	return false;
}
