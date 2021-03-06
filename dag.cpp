/* ---------------------------------------------------
   | Algoritmo de Grafo Acíclico Dirigido (DAG) em C++|   
   | Autor: Aristoteles Peixoto Barros                | 
   | Engenharia de Computação - UFAL                  |   
   | Data de publicação: 25-05-2021                   |   
    --------------------------------------------------
*/

#include <cstdio>
#include <cstdlib>
#include <climits>
#include <vector>
#include <list>

using namespace std;

#define START 1

typedef unsigned int uint;
enum cores {BRANCO, CINZA, PRETO};

vector< vector<int> > vizin;
vector< vector<int> > pesos;
vector<int> numvizin;

vector<int> dt;
vector<int> pi;

list<int> vlista;

void dagShortestPaths(int s);
void topologicalSort(void);
void depthFirstSearch(void); 
void depthFirstSearchVisit(int u, vector<int> *cor, vector<int> *pai);
void initialiseSingleSource(int s);
void comp(int u, int v, int w);

int main(int argc, char *argv[]) {
    int n, m;
    int de, para, peso;

    //Leitura de arquivo (tutorial no readme, disponível no Github) 
    if(scanf("%d %d", &n, &m) < 2) exit(1);

    vizin.resize(n, vector<int>(n, -1));
    pesos.resize(n, vector<int>(n, 0));
    numvizin.resize(n, 0);
    
    dt.resize(n);
    pi.resize(n);
    
    for(int i=0; i<m; i++) {

        //Leitura de arquivo (tutorial no readme, disponível no Github) 
        if(scanf("%d %d %d", &de, &para, &peso) < 3) exit(1);
        vizin[de][numvizin[de]] = para;
        pesos[de][numvizin[de]] = peso;
        numvizin[de]++;
    }

    dagShortestPaths(START);

    printf("Distâncias mínimas do vértice origem (%d)\n", START);
    for(uint i=0; i<dt.size(); i++) {
        if(dt[i] == INT_MAX) {
            printf("d[%d]: INFINITO\n", i);
        }
        else {
            printf("d[%d]: %d\n", i, dt[i]);
        }
    }
    printf("\nÁrvore de caminhos mínimos\n");
    for(uint i=0; i<pi.size(); i++) {
        if(pi[i] == -1) continue;
        printf("%d->%d\n", pi[i], i);
    }

    return EXIT_SUCCESS;
}

void dagShortestPaths(int s) {
    list<int>::iterator lit;
    int u;

    topologicalSort();
    initialiseSingleSource(s);
    for(lit=vlista.begin(); lit!=vlista.end(); ++lit) {
        u = *lit;
        for(int i=0; i<numvizin[u]; i++) {
            comp(u, vizin[u][i], pesos[u][i]);
        }
    }
}

void topologicalSort(void) {
    depthFirstSearch();
}

void depthFirstSearch(void) {
    vector<int> cor(vizin.size());
    vector<int> pai(vizin.size());

    for(uint u=0; u<vizin.size(); u++) {
        cor[u] = BRANCO;
        pai[u] = -1;
    }

    for(uint u=0; u<vizin.size(); u++) {
        if(cor[u] == BRANCO) {
            depthFirstSearchVisit(u, &cor, &pai);
        }
    }
}

void depthFirstSearchVisit(int u, vector<int> *cor, vector<int> *pai) {
    static vector<int> d(vizin.size());
    static vector<int> f(vizin.size());
    static int tempo = 0;
    int v;

    (*cor)[u] = CINZA;
    d[u] = ++tempo;

    for(int i=0; i<numvizin[u]; i++) {
        v = vizin[u][i];
        if((*cor)[v] == BRANCO) {
            (*pai)[v] = u;
            depthFirstSearchVisit(v, cor, pai);
        }
    }

    (*cor)[u] = PRETO;
    f[u] = ++tempo;
    vlista.push_front(u);
}

void initialiseSingleSource(int s) {
    for(uint v=0; v<vizin.size(); v++) {
        dt[v] = INT_MAX;
        pi[v] = -1;
    }
    dt[s] = 0;
}

void comp(int u, int v, int w) {
    if(dt[u] == INT_MAX) {
        return;
    }
    if(dt[v] > dt[u] + w) {
        dt[v] = dt[u] + w;
        pi[v] = u;
    }
}