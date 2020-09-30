# Universidade Federal de São Carlos – UFSCar
# Departamento de Computação
# 1001525 - Projeto e Análise de Algoritmos – Trabalho 1
# Prof. Dr. Diego Furtado Silva
# Aluno: João Victor Mendes Freire
# RA: 758943

from math import ceil

def is_there_sum(items, n, sum):
    # Criando tabela A[i][j], em que i representa o sub conjunto de itens 
    # que estão sendo considerados items[0:i], e j a soma desejada
    A = [[False] * (sum+1)] * (n+1)

    ## Casos Base
    # Somas com zero itens são impossíveis (esta parte é opcional pois 
    # começamos todas as posições da matriz com False)
    for j in range(sum+1):
        A[0][j] = False

    # Soma igual a zero é possível independente do número de itens
    for i in range(n+1):
        A[i][0] = True

    ## Preenchimento da tabela
    for i in range(1, n+1):
        for j in range(1, sum+1):
            if (items[i-1] > j):
                A[i][j] = A[i-1][j]
            else:
                A[i][j] = A[i-1][j] or A[i-1][j - items[i-1]]

    return A[n][sum]

def min_difference(coins, n):
    # Se a divisão das moedas fossem iguais
    s_max = ceil(sum(coins)/2)
    s = sum(coins)//2
    diff = -1

    # Tentando encontrar a maior soma menor que s_max
    while s >= 1 and diff == -1:
        if is_there_sum(coins, n, s):
            diff = (s_max - s)
        else:
            s -= 1
    return diff


# Leitura dos valores na entrada
n = int(input())
coins = list(map(int, input().split()))

diff = min_difference(coins, n)
print(diff)
