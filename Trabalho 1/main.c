/*
    Universidade Federal de São Carlos – UFSCar
    Departamento de Computação

    1001525 - Projeto e Análise de Algoritmos – Trabalho 1
    Prof. Dr. Murilo Coelho Naldi

    Aluno: João Victor Mendes Freire
    RA: 758943
*/

#include <stdio.h>
#include <stdlib.h>

void mergesortR(int *vetor, int ini, int fim);

int num_inversoes;

int main(int argc, char **argv)
{
    int num_casos;
    int num_vagoes;
    int *vetor = NULL;

    scanf("%d ", &num_casos); 

    for (int i = 0; i < num_casos; i++)
    {
        scanf("%d ", &num_vagoes);

        vetor = malloc(sizeof(int) * num_vagoes);

        for (int j = 0; j < num_vagoes; j++)
            scanf("%d ", &vetor[j]);  

        num_inversoes = 0;
        mergesortR(vetor, 0, num_vagoes);

        printf("Optimal train swapping takes %d swaps.\n", num_inversoes);

        free(vetor);
        vetor = NULL;
    }

    return 0;
}

// Função auxiliar da mergesort(int *, int, int). Não deve ser usada por 
// conta própria.
void static merge(int *vetor, int ini, int fim)
{
    int meio = ini + (fim - ini) / 2;

    int i = ini;
    int j = meio;
    int k = 0;

    // Vetor auxiliar
    int aux[fim - ini];

    // Intercalando os subvetores
    while(i < meio && j < fim)
    {
        if (vetor[i] < vetor[j])
            aux[k++] = vetor[i++];
        else
        {
            aux[k++] = vetor[j++];
            num_inversoes += meio - i;
        }
    }

    // Colocando os que restaram no subvetor da esquerda
    while(i < meio)
        aux[k++] = vetor[i++];
    // Colocando os que restaram no subvetor da direita
    while(j < fim)
        aux[k++] = vetor[j++];

    // Passando para o vetor original
    for (k = 0; k < (fim - ini); k++)
        vetor[ini + k] = aux[k];
}


// Função que ordena um vetor [ini .. fim - 1] de inteiros, dada uma posição 
// inicial e final. Conta os pares invertidos usando a variável global (int)
// num_inversões.
void mergesortR(int *vetor, int ini, int fim)
{
    if (ini + 1 < fim)
    {
        int m = ini + (fim - ini) / 2;

        mergesortR(vetor, ini, m);
        mergesortR(vetor, m, fim);
        merge(vetor, ini, fim);
    }
}
