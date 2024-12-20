#include "feedforward.hpp"

// tranforma a informação de uma camada de neuronios para outra

FeedForward::FeedForward(const std::vector<std::vector<double>>& pesos_iniciais, const std::vector<double>& viés_iniciais)
    : W(pesos_iniciais), B(viés_iniciais) {} // ?

double gerarNumeroAleatorio(double min, double max) {
    return min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) / (max - min));
}

// Função para multiplicar o vetor X (1 x N) pela matriz W (N x P)
std::vector<double> FeedForward::multiplicarMatricial(const std::vector<double>& X) {
    size_t N = X.size();    // Número de características (dimensão de X)
    size_t P = W[0].size(); // Número de neurônios (dimensão de W)

    std::vector<double> resultado(P, 0); // Vetor para armazenar o resultado

    for (size_t j = 0; j < P; ++j) {  // Para cada neurônio
        for (size_t i = 0; i < N; ++i) {  // Para cada característica de X
            resultado[j] += X[i] * W[i][j]; // Multiplicação X * W
        }
    }
    return resultado;
}

// Função para somar o viés B ao vetor resultado
std::vector<double> FeedForward::adicionarViés(const std::vector<double>& resultado) {
    size_t P = resultado.size(); // Número de neurônios (dimensão de B)

    std::vector<double> finalResult(P);

    for (size_t j = 0; j < P; ++j) {
        finalResult[j] = resultado[j] + B[j]; // Soma do viés
    }

    return finalResult;
}

// Função de feedforward completa: X * W + B
std::vector<double> FeedForward::feedForward(const std::vector<double>& X) {
    // Passo 1: Multiplicação de X * W
    std::vector<double> produto = multiplicarMatricial(X);

    // Passo 2: Adição do viés B
    return adicionarViés(produto);
}

// Função para mutação dos pesos W e viés B
void FeedForward::mutar(double mutation_factor) {
    for (size_t i = 0; i < W.size(); ++i) {
        for (size_t j = 0; j < W[i].size(); ++j) {
            W[i][j] *= mutation_factor;
            W[i][j] += 2 * (rand() % 1000) / 1000.0 - 1;
        }
    }

    for (size_t i = 0; i < B.size(); ++i) {
        B[i] *= mutation_factor;
        B[i] += 2 * (rand() % 1000) / 1000.0 - 1;
    }
}

// Função de crossover entre duas camadas
FeedForward FeedForward::crossover(const FeedForward& outraCamada) const {
    size_t N = W.size();     // Número de entradas
    size_t P = W[0].size();  // Número de neurônios

    std::vector<std::vector<double>> novoW(N, std::vector<double>(P, 0.0));
    std::vector<double> novoB(P, 0.0);

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < P; ++j) {
            // Escolha aleatória (0 ou 1) para decidir a origem do peso
            novoW[i][j] = (rand() % 2 == 0) ? W[i][j] : outraCamada.W[i][j];
        }
    }

    for (size_t i = 0; i < P; ++i) {
        // Escolha aleatória (0 ou 1) para decidir a origem do viés
        novoB[i] = (rand() % 2 == 0) ? B[i] : outraCamada.B[i];
    }

    return FeedForward(novoW, novoB); // Retorna a nova camada resultante do crossover
}

// Função para acessar os pesos (para a classe RedeNeural)
const std::vector<std::vector<double>>& FeedForward::getPesos() const {
    return W;
}

// Função para acessar o viés (para a classe RedeNeural)
const std::vector<double>& FeedForward::getViés() const {
    return B;
}