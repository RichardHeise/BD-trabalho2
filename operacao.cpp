#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

#include "operacao.h"

operacoes readOps(int *v) {

    int reads = 0;  

    operacoes inputs;
    operacao * temp = new operacao;

    reads = scanf("%d %d %c %c\n",&temp->order,
                                  &temp->id,
                                  &temp->op,
                                  &temp->val);


    while( reads == 4) {

        inputs.push_back(*temp);

        reads = scanf("%d %d %c %c\n", &temp->order,
                                       &temp->id,
                                       &temp->op,
                                       &temp->val); 
        

    }


    for (int i = 0; i < inputs.size(); i++) {
        if (inputs[i].id > (*v)) {
            (*v) = inputs[i].id;
        }
    }


    return inputs;
}

int testaSeriabilidade(operacoes inputs, int ver) {

    Grafo grafo_p = iniciaGrafo(ver);

    for(int i = 0; i < inputs.size(); i++) {
        for(int j = i+1; j < inputs.size(); j++) {

            if( (inputs[i].id != inputs[j].id) && (inputs[i].val == inputs[j].val) ) {

                if( (inputs[i].op == 'W') && (inputs[j].op == 'R' ) )
                    insereAresta(grafo_p, inputs[i].id-1, inputs[j].id-1);

                if( (inputs[i].op == 'R') && (inputs[j].op == 'W' ) )
                    insereAresta(grafo_p, inputs[i].id-1, inputs[j].id-1);

                if( (inputs[i].op == 'W') && (inputs[j].op == 'W' ) )
                    insereAresta(grafo_p, inputs[i].id-1, inputs[j].id-1);
            
            }
        }
    }

    return !checkCiclo(grafo_p);
}

static vector<int> converteVetor(vector<int> vetor, int tam, int num) {

    int k;

    vector<int> aux(tam, 0);
    
    k = 0;
    for (int i = 1; i < tam; i++) {
        if (vetor[i] == 1) {
            aux[k] = i;
            k++;
        }
    }
    aux.resize(k);
    sort(aux.begin(), aux.end());    
    return aux;
}

vector<escalonamento> separaInput(operacoes inputs, int tam) {

    vector<bool> vetor(tam, 0);
    vector<int> vetor_aux(tam, 0);

    vector<escalonamento> bloco; 

    int aux = 0;
    int abertos = 0;
    int i = 0;
    int j = 0;

    while (i < tam) {
        
        escalonamento * temp = new escalonamento;
        temp->num_opr = 0;
        temp->num_trans = 0;

        for (int v = 0; v < tam; v++) {
            vetor_aux[v] = 0;
        }
        
        do {
            
            temp->operacoes.push_back(inputs[i]);
            temp->num_opr++;
            
            if ( (vetor[inputs[i].id] != 1) && (inputs[i].op != 'C') ) {
                vetor[inputs[i].id] = 1;
                abertos++;
                vetor_aux[inputs[i].id] = 1;
                temp->num_trans++;
            }

            if ( (vetor[inputs[i].id] == 1) && (inputs[i].op == 'C')) {
                vetor[inputs[i].id] = 0;
                abertos--;
            }
            
            i++;

        } while ((abertos != 0) && (i < tam));

        bloco.push_back(*temp);
            
        bloco[j].id_trans = converteVetor(vetor_aux, tam, bloco[j].num_opr);

        j++;

        for (int w = 0; w < tam; w++) {
            aux += vetor[w];
        }
        
        if ( aux != 0) {
            perror("Transação não commitada");
            exit(NOT_COMMITED);
        }
    }

    return bloco;
}

static unsigned long long fat(int val) {
    unsigned long long fatorial = 1;

    for(int i = 1; i <= val; i++) {
        fatorial *= i;
    }

    return fatorial;
}

static vector<int> getIds(operacoes inputs) {

    vector<int> temp(inputs.size());

    for (int i = 0; i < inputs.size(); i++) {
        temp[i] = inputs[i].id;
    }

    sort(temp.begin(), temp.end());

    vector<int>::iterator it;
    it = unique(temp.begin(), temp.end());
    temp.resize(distance(temp.begin(), it));

    return temp;
}

map<char, int> achaEscritaFinal(operacoes inputs) {
    map<char, int> temp;

    for (int i = inputs.size()-1; i >= 0; i--) {
        if ((inputs[i].op == 'W') && (!temp.count(inputs[i].val))) {
            temp.insert(make_pair(inputs[i].val, inputs[i].id));
        }
    }

    return temp;
}

map<pair<pair<int,int>,char>,pair<int,int>> achaDemaisEscritas(operacoes inputs) {
    map<pair<pair<int,int>,char>,pair<int,int>> temp;

    for(int i = inputs.size()-1; i >= 0; i--) {
        if ((inputs[i].op == 'R') ) {
            pair<pair<int,int>,char> chave;

            chave = make_pair(make_pair(inputs[i].order, inputs[i].id), inputs[i].val);
            int j = i - 1;

            while ( j >= 0 ) {
                if ( (inputs[i].val == inputs[j].val) && 
                     (inputs[j].op == 'W') ) {
                        temp.insert(make_pair(chave, make_pair(inputs[j].id, inputs[j].order)));
                }
                j--;
            }

            if (temp.find(chave) == temp.end())
                temp.insert(make_pair(chave, make_pair(0, 0)));
        }
    }
    return temp;
}

int testaEquivalencia(operacoes inputs) {

    vector<int> ids(inputs.size());
    ids = getIds(inputs);
    
    map<char, int> escrita_final;
    escrita_final = achaEscritaFinal(inputs);
    
    map<pair<pair<int,int>,char>,pair<int,int>> demais_escritas;
    demais_escritas = achaDemaisEscritas(inputs);
    
    unsigned long long fatorial = fat(ids.size());
    
    int equivalente;

    for(int i = 0; i < fatorial; i++) {

        equivalente = 1;
        operacoes visao;
        for(int j = 0; j < ids.size(); j++) {
            for(int k = 0; k < inputs.size(); k++) {
                if (inputs[k].id == ids[j]) {
                    visao.push_back(inputs[k]);
                }
            }
        }

        map<char, int> escrita_final_visao = achaEscritaFinal(visao);

        for(map<char, int>::iterator it = escrita_final.begin(); it != escrita_final.end(); it++) {
            map<char, int>::iterator it_operacoes = escrita_final_visao.find(it->first);

            if ((it->first != it_operacoes->first) || (it->second != it_operacoes->second)) {
                equivalente = 0;
            }
        }

        map<pair<pair<int,int>,char>,pair<int,int>> demais_escritas_visao = achaDemaisEscritas(visao);
        
        for(map<pair<pair<int,int>,char>,pair<int,int>>::iterator it = demais_escritas.begin(); it != demais_escritas.end(); it++) {
            map<pair<pair<int,int>,char>,pair<int,int>>::iterator it_operacoes = demais_escritas_visao.find(it->first);

            if ((it->first != it_operacoes->first) || (it->second != it_operacoes->second)) {
                equivalente = 0;
            }
        }

        if (equivalente) {
            return equivalente;
        }

        next_permutation(ids.begin(), ids.end());
    }
    
    return equivalente;
}
