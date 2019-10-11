/*
    Universidade Federal de São Carlos – UFSCar
    Departamento de Computação

    1001525 - Projeto e Análise de Algoritmos – Trabalho 1
    Prof. Dr. Murilo Coelho Naldi

    Aluno: João Victor Mendes Freire
    RA: 758943
*/

#include <iostream>

class Merge
{
    public:
    // Função que ordena um vetor [ini .. fim - 1] de inteiros, dada uma posição 
    // inicial e final. Retorna o número de pares invertidos
    static int Sort(int *arr, int ini, int fim)
    {
        int num_inversoes = 0;

        if (ini + 1 < fim)
        {
            int m = ini + (fim - ini) / 2;

            num_inversoes += Merge::Sort(arr, ini, m);
            num_inversoes += Merge::Sort(arr, m, fim);

            num_inversoes += Merge::merge(arr, ini, m, fim);
        }

        return num_inversoes;
    }

    private:
    // Função auxiliar da Sort(). Não deve ser usada por conta própria.
    static int merge(int *arr, int ini, int meio, int fim)
    {
        int i = ini;
        int j = meio;
        int k = 0;
        int num_inversoes = 0;

        int *aux = (int *) malloc((fim - ini) * sizeof(int));

        while(i < meio && j < fim)
        {
            if (arr[i] < arr[j])
                aux[k++] = arr[i++];
            else
            {
                aux[k++] = arr[j++];
                num_inversoes += meio - i;
            }
        }

        while(i < meio)
            aux[k++] = arr[i++];
        while(j < fim)
            aux[k++] = arr[j++];

        for (k = 0; k < (fim - ini); k++)
            arr[ini + k] = aux[k];

        free(aux);
        return num_inversoes;
    }
};

int main(int argc, char **argv)
{
    int N; // Número de casos a serem rodados
    int L; // Número de vagões do trem
    int num_inv;
    int *vetor = NULL;

    scanf("%d ", &N); 

    for (int i = 0; i < N; i++)
    {
        scanf("%d ", &L);

        vetor = (int *) malloc(sizeof(int) * L);

        for (int j = 0; j < L; j++)
            scanf("%d ", &vetor[j]);  

        num_inv = Merge::Sort(vetor, 0, L);

        printf("Optimal train swapping takes %d swaps.\n", num_inv);

        free(vetor);
        vetor = NULL;
    }

    return 0;
}
