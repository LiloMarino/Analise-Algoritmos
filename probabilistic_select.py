import random

from classes.logger import LoggerFactory

logger = LoggerFactory.get_logger()


def main():
    vector = [3, 2, 9, 0, 7, 5, 4, 8, 6, 1]
    k = 4
    logger.info("K = %s", k)
    result = probabilistic_select(vector, 0, len(vector) - 1, k)
    logger.info("O %sº menor elemento é %s", k, vector[result])


def probabilistic_select(v: list[int], inicio: int, fim: int, k: int):
    if inicio == fim - 1:
        return inicio
    pivo = probabilistic_partition(v, inicio, fim)
    i = pivo - inicio + 1
    logger.info("%s %s %s", v[inicio:pivo], v[pivo], v[pivo + 1 : fim + 1])
    if k < i:
        logger.info("Subarray à esquerda: %s", v[inicio:pivo])
        return probabilistic_select(v, inicio, pivo, k)
    elif k == i:
        return pivo
    else:
        logger.info("Subarray à direita: %s", v[pivo + 1 : fim + 1])
        return probabilistic_select(v, pivo + 1, fim, k - i)


def probabilistic_partition(v: list[int], inicio: int, fim: int):
    # Random um pivô aleatório dentro do subarray
    pivo_index = random.randint(inicio, fim)
    logger.info("Pivô: %s", v[pivo_index])
    # Swap subarray[0] <-> pivô
    logger.info("%s", v[inicio : fim + 1])
    v[inicio], v[pivo_index] = v[pivo_index], v[inicio]
    logger.info("%s", v[inicio : fim + 1])
    return partition(v, inicio, fim)


def partition(v: list[int], inicio: int, fim: int):
    pivo = v[inicio]
    esquerda = inicio + 1
    direita = fim
    logger.info("%s", v[inicio : fim + 1])
    # Enquanto não se (cruzarem ou colidirem) faça
    while esquerda < direita:
        # Procure pela esquerda o primeiro elemento maior que o pivô
        while (v[esquerda] <= pivo) and (esquerda < fim):
            esquerda += 1
        # Procure pela direita o primeiro elemento menor que o pivô
        while (v[direita] > pivo) and (direita >= inicio):
            direita -= 1
        # Se não se cruzaram e não se colidiram então
        if esquerda < direita:
            # Swap maior <-> menor
            v[esquerda], v[direita] = v[direita], v[esquerda]
            logger.info("%s", v[inicio : fim + 1])
    # Swap pivô <-> menor
    v[inicio], v[direita] = v[direita], v[inicio]
    logger.info("%s", v[inicio : fim + 1])
    return direita


if __name__ == "__main__":
    main()
