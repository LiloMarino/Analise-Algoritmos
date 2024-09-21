import random


def main():
    vector = [3, 2, 9, 0, 7, 5, 4, 8, 6, 1]
    k = 4  # Exemplo: encontrar o 4º menor elemento
    result = probabilistic_select(vector, 0, len(vector) - 1, k)
    print(f"O {k}º menor elemento é {vector[result]}")


def probabilistic_select(v: list[int], inicio: int, fim: int, k: int):
    if inicio == fim:
        return inicio
    pivo = probabilistic_partition(v, inicio, fim)
    i = pivo - inicio + 1
    if k < i:
        return probabilistic_select(v, inicio, pivo, k)
    else:
        return probabilistic_select(v, pivo + 1, fim, k - i)


def probabilistic_partition(v: list[int], inicio: int, fim: int):
    pivo_index = random.randint(inicio, fim)
    v[inicio], v[pivo_index] = v[pivo_index], v[inicio]  # Move o pivô para o início
    pivo = v[inicio]
    i = inicio + 1
    for j in range(inicio + 1, fim + 1):
        if v[j] < pivo:
            v[i], v[j] = v[j], v[i]
            i += 1
    v[inicio], v[i - 1] = v[i - 1], v[inicio]  # Move o pivô para a posição correta
    return i - 1


if __name__ == "__main__":
    main()
