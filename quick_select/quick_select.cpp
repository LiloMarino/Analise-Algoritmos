#include <vector>
#include <random>
#include <algorithm>
#include <sstream>
#include "../classes/logger_factory.hpp"

auto logger = LoggerFactory::get_logger("Quick Select");

void main_function();
int probabilistic_select(std::vector<int>& v, int inicio, int fim, int k);
int probabilistic_partition(std::vector<int>& v, int inicio, int fim);
int partition(std::vector<int>& v, int inicio, int fim);
std::string vector_to_string(const std::vector<int>& v, int inicio, int fim);

int main() {
    main_function();
    return 0;
}

void main_function() {
    std::vector<int> vector = {3, 2, 9, 0, 7, 5, 4, 8, 6, 1};
    int k = 4;
    logger->info("K = {}", k);
    int result = probabilistic_select(vector, 0, vector.size() - 1, k);
    logger->info("O {}º menor elemento é {}", k, vector[result]);
}

int probabilistic_select(std::vector<int>& v, int inicio, int fim, int k) {
    if (inicio == fim - 1) {
        return inicio;
    }
    int pivo = probabilistic_partition(v, inicio, fim);
    int i = pivo - inicio + 1;
    logger->info("Subarrays: [{}] {} [{}]", vector_to_string(v, inicio, pivo - 1), v[pivo], vector_to_string(v, pivo + 1, fim));
    
    if (k < i) {
        logger->info("Subarray à esquerda: {}", vector_to_string(v, inicio, pivo - 1));
        return probabilistic_select(v, inicio, pivo, k);
    } else if (k == i) {
        return pivo;
    } else {
        logger->info("Subarray à direita: {}", vector_to_string(v, pivo + 1, fim));
        return probabilistic_select(v, pivo + 1, fim, k - i);
    }
}

int probabilistic_partition(std::vector<int>& v, int inicio, int fim) {
    // Random um pivô aleatório dentro do subarray
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(inicio, fim);
    int pivo_index = distrib(gen);
    logger->info("Pivô: {}", v[pivo_index]);
    
    // Swap subarray[0] <-> pivô
    logger->info("Antes do swap: {}", vector_to_string(v, inicio, fim));
    std::swap(v[inicio], v[pivo_index]);
    logger->info("Depois do swap: {}", vector_to_string(v, inicio, fim));
    
    return partition(v, inicio, fim);
}

int partition(std::vector<int>& v, int inicio, int fim) {
    int pivo = v[inicio];
    int esquerda = inicio + 1;
    int direita = fim;
    
    logger->info("Particionando: {}", vector_to_string(v, inicio, fim));
    
    // Enquanto não se (cruzarem ou colidirem) faça
    while (esquerda < direita) {
        // Procure pela esquerda o primeiro elemento maior que o pivô
        while (v[esquerda] <= pivo && esquerda < fim) {
            esquerda++;
        }
        // Procure pela direita o primeiro elemento menor que o pivô
        while (v[direita] > pivo && direita >= inicio) {
            direita--;
        }
        // Se não se cruzaram e não se colidiram então
        if (esquerda < direita) {
            // Swap maior <-> menor
            std::swap(v[esquerda], v[direita]);
            logger->info("Swap realizado: {}", vector_to_string(v, inicio, fim));
        }
    }
    // Swap pivô <-> menor
    std::swap(v[inicio], v[direita]);
    logger->info("Swap do pivô: {}", vector_to_string(v, inicio, fim));
    
    return direita;
}

// Função para converter o vetor em string no intervalo [inicio..fim]
std::string vector_to_string(const std::vector<int>& v, int inicio, int fim) {
    std::ostringstream oss;
    for (int i = inicio; i < fim; ++i) {
        oss << v[i] << " ";
    }
    oss << v[fim];
    return oss.str();
}
