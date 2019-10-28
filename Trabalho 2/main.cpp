/*
    Universidade Federal de São Carlos – UFSCar
    Departamento de Computação

    1001525 - Projeto e Análise de Algoritmos – Trabalho 2
    Prof. Dr. Murilo Coelho Naldi

    Aluno: João Victor Mendes Freire
    RA: 758943

    Resolução inspirada nas notas de aula do Prof. Mario San Felice:
    - http://www2.dc.ufscar.br/~mario/ensino/2018s2/paa/aula16/algoritmoPrim.txt
    E no site GeeksForGeeks:
    - https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/
*/

#include <iostream>
#include <list>
#include <queue>
#include <cstdlib>

#define INF 0x3f3f3f3f 

class Graph
{
    public:
    // Construtor
    Graph(int n);

    // Cria uma aresta entre dois vértices v, u pertencentes à [0..n]
    void add_edge(int u, int v, int peso);

    // Retorna o peso dos vértices da Árvore Geradora Mínima
    int MST();

    private:
    int n;                                   // Número de vértices
    std::list< std::pair<int, int> > *adj;   // Lista de adjacências
};

int main(int argc, char **argv)
{
    int num_routers, num_cables;
    int v, w, price;

    scanf("%d %d ", &num_routers, &num_cables);
    Graph G(num_routers);

    // Definindo as arestas do grafo G (cabos de internet)
    for (int i = 0; i < num_cables; i++)
    {
        scanf("%d %d %d ", &v, &w, &price);
        G.add_edge(v - 1, w - 1, price);
    }

    // Custo total minímo é o peso da Árvore Geradora Mínima
    int total_price = G.MST();
    printf("%d\n", total_price);

    return 0;
}

Graph::Graph(int n)
{
    this->n = n;
    this->adj = new std::list<std::pair<int, int> >[n];
}

void Graph::add_edge(int u, int v, int peso)
{
    // Colocando (v, peso) na lista de adjacência de u
    adj[u].push_back(std::make_pair(v, peso));
    // Colocando (u, peso) na lista de adjacência de v
    adj[v].push_back(std::make_pair(u, peso));
}

int Graph::MST()
{
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int> >,
                        std::greater<std::pair<int, int> > > heap;

    int d[n];                   // Chaves, começam com infinito
    int aresta[n];              // Armazena qual aresta chegou em cada uma
    int na_MST[this->n];        // Quais vertices estão na MST
    int peso_MST = 0;           // Peso total da MST

    for (int i = 0; i < n; i++)
    {
             d[i] = INF;
        na_MST[i] = false;
        aresta[i] = -1;
    }

    int s = 0;
    heap.push(std::make_pair(0, s));
    d[s] = 0;

    while (!heap.empty())
    {
        // Pegando nó no topo da min heap
        int u = heap.top().second;
        heap.pop();
        na_MST[u] = true;

        // Para cada aresta (u, v)
        std::list<std::pair<int, int> >::iterator it;
        for (it = adj[u].begin(); it != adj[u].end(); it++)
        {
            int v = it->first;
            int peso = it->second;

            // Se v não foi adicionado à MST e se o peso da aresta (u, v) é menor que d[v]
            if (na_MST[v] == false && d[v] > peso)
            {
                d[v] = peso;
                heap.push(std::make_pair(peso, v));
                aresta[v] = u;
            }
        }
    }

    // Computando peso total a partir da solução final
    for (int i = 0; i < n; i++)
        peso_MST += d[i];

    return peso_MST;
}
