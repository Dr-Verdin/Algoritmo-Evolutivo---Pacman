#ifndef FEEDFORWARD_HPP
#define FEEDFORWARD_HPP

#include <vector>
#include <iostream>
using namespace std;


double gerarNumeroAleatorio(double min, double max);

class FeedForward {
private:
    std::vector<std::vector<double>> W;  // Matriz de pesos (N x P)
    std::vector<double> B;               // Vetor de viés (1 x P)

public:
    // Construtor da classe, recebendo W (pesos) e B (viés)
    FeedForward(const std::vector<std::vector<double>>& pesos, const std::vector<double>& viés);

    // Função para multiplicar o vetor X (1 x N) pela matriz W (N x P)
    std::vector<double> multiplicarMatricial(const std::vector<double>& X);

    // Função para somar o viés B ao vetor resultado
    std::vector<double> adicionarViés(const std::vector<double>& resultado);

    // Função de feedforward completa: X * W + B
    std::vector<double> feedForward(const std::vector<double>& X);

    // Função para mutação dos pesos W e viés B
    void mutar(double mutation_factor);

    // Função de crossover entre duas camadas
    FeedForward crossover(const FeedForward& outraCamada) const;

    // Funções para acessar os pesos e o viés (necessário para a classe RedeNeural)
    const std::vector<std::vector<double>>& getPesos() const;
    const std::vector<double>& getViés() const;
};

#endif