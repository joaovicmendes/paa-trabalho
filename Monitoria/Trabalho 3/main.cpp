/*
    Universidade Federal de São Carlos – UFSCar
    Departamento de Computação
    1001525 - Projeto e Análise de Algoritmos – Trabalho 3
    Prof. Dr. Diego Furtado Silva
    Aluno: João Victor Mendes Freire
    RA: 758943
*/

#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f
#define iPair std::pair<int, double>
#define dPair std::pair<double, int>

class Grafo
{
public:
    Grafo(int n);
    ~Grafo();

    void add_edge(int v, int u, double w) const;

    double Dijkstra(int ori, int dest) const;
private:
    int n;                    // No. de vértices
    std::vector<iPair > *adj; // Lista de adjacencias
};

int main()
{
    int M, E, N, C; // No. de vértices, arestas, tubulações e consultas
    scanf("%d %d %d %d ", &M, &E, &N, &C);
    
    Grafo inocente(M), impostor(M);

    // Adicionando arestas de corredor em ambos
    for (int i = 0; i < E; i++)
    {
        int v, u;
        double w;
        scanf("%d %d %lf ", &v, &u, &w);

        inocente.add_edge(v, u, w);
        impostor.add_edge(v, u, w);
    }

    // Adicionando arestas de tubulação (para o impostor apenas)
    for (int i = 0; i < N; i++)
    {
        int v, u;
        scanf("%d %d ", &v, &u);
        impostor.add_edge(v, u, 1.0);
    }

    // Consultas
    for (int i = 0; i < C; i++)
    {
        int origin;
        scanf("%d ", &origin);

        if (inocente.Dijkstra(origin, 0) <= impostor.Dijkstra(origin, 0) + 0.01)
            printf("victory\n");
        else
            printf("defeat\n");
    }

    return 0;
}

Grafo::Grafo(int n)
{
    if (n <= 0)
    {
        std::cout << "Erro: número de índices negativo\n";
        exit(1);
    }

    this->n = n;
    this->adj = new std::vector<iPair >[n];
}

Grafo::~Grafo()
{
    delete [] adj;
}

void Grafo::add_edge(int v, int u, double w) const
{
    if (v < 0 || v >= n || u < 0 || u >= n)
    {
        std::cout << "Erro: índice inexistente\n";
        exit(1);
    }

    this->adj[v].push_back(std::make_pair(u, w));
    this->adj[u].push_back(std::make_pair(v, w));
}

double Grafo::Dijkstra(int ori, int dest) const
{
    std::priority_queue<dPair, std::vector<dPair >, std::greater<dPair > > pq;
    bool visitado[this->n];
    // int prev[this->n]; // Para poder reconstruir o caminho
    double dist[this->n];
    int u, v;
    double w;

    // Inicializando com valores apropriados
    for (int i = 0; i < this->n; i++)
    {
        visitado[i] = false;
        // prev[i] = -1;
        dist[i] = INF;
    }

    // Colocando origem na pq
    dist[ori] = 0;
    pq.push(std::make_pair(0, ori));

    while (!visitado[dest] && !pq.empty())
    {
        // Retirando o elemento com menor distância
        v = pq.top().second;
        pq.pop();
        visitado[v] = true;

        // Iterando sobre suas arestas
        for (unsigned int i = 0; i < this->adj[v].size(); i++)
        {
            u = this->adj[v].at(i).first;
            w = this->adj[v].at(i).second;

            if (!visitado[u])
                if (dist[u] > dist[v] + w)
                {
                    dist[u] = dist[v] + w;
                    pq.push(std::make_pair(dist[u], u));
                    // prev[u] = v;
                }
        }
    }

    return dist[dest];
}
