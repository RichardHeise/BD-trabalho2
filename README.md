# BD-trabalho2

Trabalho para banco de dados feito em 2021 via ERE.

Link do trabalho: https://www.inf.ufpr.br/eduardo/ensino/ci218/trabalhos/escalona/escalona.html

## Instrução:

### Objetivo:
- Implementar dois algoritmos de detecção de conflitos de escalonamento de transações concorrentes. Estes algoritmos permitem o aluno compreender gargalos no processamento de transações.

## Algoritmo de teste de seriabilidade quanto ao conflito:
- Crie um nó para cada T do escalonamento S
- Aresta Ti -> Tj para cada r(x) em Tj depois de w(x) em Ti
- Aresta Ti -> Tj para cada w(x) em Tj depois de r(x) em Ti
- Aresta Ti -> Tj para cada w(x) em Tj depois de w(x) em Ti
- S é serial se não existe ciclo no grafo

## Algoritmo de visão equivalente
- Dois agendamentos S e S' são ditos visão equivalentes, se atenderem as seguintes condições:
- O mesmo conjunto de transações e operações participam em S e S'
- Para cada r(x) de Ti, se o valor de x lido for escrito por w(x) de Tj, o mesmo deve permanecer para r(x) de Ti em S'
- Se o operador w(y) em Tk é a ultima escrita de y em S, então w(y) em Tk deve ser a última escrita em S'
