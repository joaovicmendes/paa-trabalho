/*
    Universidade Federal de São Carlos – UFSCar
    Departamento de Computação

    1001525 - Projeto e Análise de Algoritmos – Trabalho 2
    Prof. Dr. Diego Furtado Silva

    Aluno: João Victor Mendes Freire
    RA: 758943
*/

#include <iostream>
#include <cstdlib>

class Quick
{
    public:
    static double Seleciona(double *arr, int ini, int fim, int k)
    {
        int pivo = Quick::Particiona(arr, ini, fim);

        if (pivo == k)
            return arr[pivo];
        else if (pivo > k)
            return Quick::Seleciona(arr, ini, pivo, k);
        else
            return Quick::Seleciona(arr, pivo + 1, fim, k);        
    }

    static void Sort(double *arr, int ini, int fim)
    {
        if (ini < fim)
        {
            int pivo = Quick::Particiona(arr, ini, fim);
            Quick::Sort(arr, ini, pivo);
            Quick::Sort(arr, pivo + 1, fim);
        }
    }

    private:
    // Troca o valor de dois indices de um vetor, não verifica tamanho
    static void troca(double *arr, int a, int b)
    {
        double aux = arr[a];
        arr[a] = arr[b];
        arr[b] = aux;
    }
    // Partição do QuickSort
    static int Particiona(double *arr, int ini, int fim)
    {
        int pivo = (ini + fim) / 2;
        Quick::troca(arr, ini, pivo);

        pivo = ini;
        int i = ini + 1;
        int j = fim - 1;

        while (i <= j)
        {
            while (i < fim && arr[i] <= arr[pivo])
                i++;
            while (arr[j] > arr[pivo])
                j--;

            if (i < j)
                Quick::troca(arr, i, j);
        }

        Quick::troca(arr, pivo, j);

        return j;
    }
};

int main(int argc, char **argv)
{
    int N, C, K;
    double *array = NULL;

    // Lendo N, k, L e alocando o espaço para a matriz
    scanf("%d ", &N);

    for (int i = 0; i < N; i++)
    {
        scanf("%d %d ", &K, &C);
        array = (double *) malloc(sizeof(double) * C);

        for (int j = 0; j < C; j++)
            scanf("%lf ", &array[j]);

        double kth = Quick::Seleciona(array, 0, C, C-K);
        printf("%.2lf\n", kth);
        free(array), array = NULL;
    }

    return 0;
}
