#include "escalona.h"
#include <algorithm>

bool testaSeriabilidade(operacoes entradas, int ver) {

    Grafo grafo_p = iniciaGrafo(ver);

    for(int i = 0; i < entradas.size(); i++) {
        for(int j = i+1; j < entradas.size(); j++) {

            if( (entradas[i].id != entradas[j].id) && (entradas[i].val == entradas[j].val) ) {

                if( (entradas[i].op == 'W') && (entradas[j].op == 'R' ) )
                    insereAresta(grafo_p, entradas[i].id-1, entradas[j].id-1);

                if( (entradas[i].op == 'R') && (entradas[j].op == 'W' ) )
                    insereAresta(grafo_p, entradas[i].id-1, entradas[j].id-1);

                if( (entradas[i].op == 'W') && (entradas[j].op == 'W' ) )
                    insereAresta(grafo_p, entradas[i].id-1, entradas[j].id-1);
            
            }
        }
    }

    return !checkCiclo(grafo_p);
}

static unsigned long long fat(int valor) {
    unsigned long long fatorial = 1;

    for(int i = 1; i <= valor; i++) {
        fatorial *= i;
    }

    return fatorial;
}

static vector<int> getIds(operacoes entradas) {

    vector<int> temp(entradas.size());

    for (int i = 0; i < entradas.size(); i++) {
        temp[i] = entradas[i].id;
    }

    sort(temp.begin(), temp.end());

    vector<int>::iterator it;
    it = unique(temp.begin(), temp.end());
    temp.resize(distance(temp.begin(), it));

    return temp;
}

ultima_escrita achaEscritaFinal(operacoes entradas) {
    ultima_escrita temp;

    for (int i = entradas.size()-1; i >= 0; i--) {
        if ((entradas[i].op == 'W') && (!temp.count(entradas[i].val))) {
            temp.insert(make_pair(entradas[i].val, entradas[i].id));
        }
    }

    return temp;
}

escritas achaDemaisEscritas(operacoes entradas) {
    escritas temp;

    for(int i = entradas.size()-1; i >= 0; i--) {
        if ((entradas[i].op == 'R') ) {
            pair<pair<int,int>,char> chave;

            chave = make_pair(make_pair(entradas[i].order, entradas[i].id), entradas[i].val);
            int j = i - 1;

            while ( j >= 0 ) {
                if ( (entradas[i].val == entradas[j].val) && 
                     (entradas[j].op == 'W') ) {
                        temp.insert(make_pair(chave, make_pair(entradas[j].id, entradas[j].order)));
                }
                j--;
            }

            if (temp.find(chave) == temp.end())
                temp.insert(make_pair(chave, make_pair(0, 0)));
        }
    }
    return temp;
}

bool testaEquivalencia(operacoes entradas) {

    vector<int> ids(entradas.size());
    ids = getIds(entradas);
    
    ultima_escrita escrita_final;
    escrita_final = achaEscritaFinal(entradas);
    
    escritas demais_escritas;
    demais_escritas = achaDemaisEscritas(entradas);
    
    unsigned long long fatorial = fat(ids.size());
    
    bool equivalente;

    for(int i = 0; i < fatorial; i++) {

        equivalente = true;
        operacoes visao;
        for(int j = 0; j < ids.size(); j++) {
            for(int k = 0; k < entradas.size(); k++) {
                if (entradas[k].id == ids[j]) {
                    visao.push_back(entradas[k]);
                }
            }
        }

        ultima_escrita escrita_final_visao = achaEscritaFinal(visao);

        for(ultima_escrita::iterator it = escrita_final.begin(); it != escrita_final.end(); it++) {
            ultima_escrita::iterator it_operacoes = escrita_final_visao.find(it->first);

            if ((it->first != it_operacoes->first) || (it->second != it_operacoes->second)) {
                equivalente = false;
            }
        }

        escritas demais_escritas_visao = achaDemaisEscritas(visao);

        for(escritas::iterator it = demais_escritas.begin(); it != demais_escritas.end(); it++) {
            escritas::iterator it_operacoes = demais_escritas_visao.find(it->first);

            if ((it->first != it_operacoes->first) || (it->second != it_operacoes->second)) {
                equivalente = false;
            }
        }

        if (equivalente) {
            return equivalente;
        }

        next_permutation(ids.begin(), ids.end());
    }
    
    return equivalente;
}
