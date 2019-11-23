/*
    Universidade Federal de São Carlos – UFSCar
    Departamento de Computação

    1001525 - Projeto e Análise de Algoritmos – Trabalho 3
    Prof. Dr. Murilo Coelho Naldi

    Aluno: João Victor Mendes Freire
    RA: 758943
*/

#include <iostream>

#define MAX(x,y) ((x) > (y) ? (x) : (y))

typedef struct packet 
{
    int    weight; // Packet weight
    int ornaments; // Numeber of ornaments in packet
} Packet;

int mochila(Packet* p, int num_packets, int max_weight);

int main(int argc, char **argv)
{
    int num_branches, num_packets, max_weight;
    int o, w;
    Packet *packets;

    scanf("%d ", &num_branches);
    for (int i = 0; i < num_branches; i++)
    {
        scanf("%d ", &num_packets);
        scanf("%d ", &max_weight);

        packets = (Packet *)malloc(sizeof(Packet) * (num_packets + 1));

        for (int j = 1; j <= num_packets; j++)
        {
            scanf("%d %d ", &o, &w);
            packets[j].weight    = w;
            packets[j].ornaments = o;
        }

        std::cout << "Galho " << i + 1 << ":\n";
        std::cout << "Numero total de enfeites: " << mochila(packets, num_packets, max_weight) << "\n\n";
    } 

    return 0;
}

// Função que máximiza o valor (número de enfeites) dado uma lista de pacotes
// (com peso e qtd de enfeites de cada), rspeitando dado limite máximo.
int mochila(Packet* p, int num_packets, int max_weight)
{
    int A[num_packets + 1][max_weight + 1];

    // Casos base
    for (int j = 0; j < max_weight; j++)
        A[0][j] = 0;

    // Prenchendo matriz explorando a subestrutura ótima
    for (int i = 1; i <= num_packets; i++)
        for (int j = 0; j <= max_weight; j++)
        {
            if (j < p[i].weight)
                A[i][j] = A[i - 1][j];
            else
                A[i][j] = MAX(A[i - 1][j], A[i - 1][j - p[i].weight] + p[i].ornaments);
        }

    return A[num_packets][max_weight];
}
