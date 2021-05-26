/* ---------------------------------------------------
   | Algoritmo de Kruskal em C++                      |   
   | Autor: Aristoteles Peixoto Barros                | 
   | Engenharia de Computação - UFAL                  |   
   | Data de publicação: 25-05-2021                   |   
    --------------------------------------------------
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>

using namespace std;

#define TAM 500

enum cores {BRANCO, CINZA, PRETO};

int vizin[TAM][TAM];
int pesos[TAM][TAM];
int numvizin[TAM];
int pi[TAM];
int rank[TAM];

void atribuir(int x);
void unir(int x, int y);
int encontrar(int x);
void unir_encontrar(int x, int y);
void mstKruskal(int n, int m);
int cmparestas(const void *p1, const void *p2);
void mostrarMatrizes(int n);

int main(int argc, char *argv[]) {
    int n, m;
    int de, para, peso;

    memset(numvizin, 0, sizeof(numvizin));

    //Leitura de arquivo (tutorial no readme, disponível no Github) 
    scanf("%d %d", &n, &m);

    for(int i=0; i<m; i++) {

        //Leitura de arquivo (tutorial no readme, disponível no Github) 
        scanf("%d %d %d", &de, &para, &peso);
        vizin[de][numvizin[de]] = para;
        pesos[de][numvizin[de]] = peso;
        numvizin[de]++;
    }

    mstKruskal(n, m);

    return EXIT_SUCCESS;
}

void atribuir(int x) {
    pi[x] = x;
    rank[x] = 0;
}

void unir(int x, int y) {
    if(rank[x] > rank[y]) {
        pi[y] = x;
    }
    else {
        pi[x] = y;
        if(rank[x] == rank[y]) {
            rank[y]++;
        }
    }
}

int encontrar(int x) {
    if(x != pi[x]) {
        pi[x] = encontrar(pi[x]);
    }

    return pi[x];
}

void unir_encontrar(int x, int y) {
    unir(encontrar(x), encontrar(y));
}

void mstKruskal(int n, int m) {
    int arestas[m][3], A[m][2];
    int peso=0, k=0, l=0;

    for(int i=0; i<n; i++) {
        atribuir(i);
        for(int j=0; j<numvizin[i]; j++) {
            arestas[k][0] = i;
            arestas[k][1] = vizin[i][j];
            arestas[k][2] = pesos[i][j];
            k++;
        }
    }

    qsort(arestas, k, 3*sizeof(int), cmparestas);

    printf("Kruskal\n");

    for(int i=0; i<k; i++) {
        if(encontrar(arestas[i][0]) != encontrar(arestas[i][1])) {
            A[l][0] = arestas[i][0];
            A[l][1] = arestas[i][1];
            l++;
            peso += arestas[i][2];
            unir_encontrar(arestas[i][0], arestas[i][1]);
        }
    }

    printf("Peso do grafo: %d\n", peso);

    for(int i=0; i<l; i++) {
        printf("%d<->%d\n", A[i][0], A[i][1]);
    }
}

int cmparestas(const void *p1, const void *p2) {
    int a = ((int *)p1)[2];
    int b = ((int *)p2)[2];

    return a - b;
}

void mostrarMatrizes(int n) {
    printf("Mostrar matrizes\n");

    for(int i=0; i<n; i++) {
        for(int j=0; j<numvizin[i]; j++) {
            printf("%d ", vizin[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for(int i=0; i<n; i++) {
        for(int j=0; j<numvizin[i]; j++) {
            printf("%d ", pesos[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}