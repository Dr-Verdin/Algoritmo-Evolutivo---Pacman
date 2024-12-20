#ifndef REDE_NEURAL_HPP
#define REDE_NEURAL_HPP

#include <vector>
#include <iostream>
#include <cstdlib>  
#include <ctime>    
#include "feedforward.hpp"
using namespace std;

class RedeNeural {
private:
    vector<FeedForward> camadas;  // Vetor de objetos FeedForward, uma para cada camada
    vector<int> camadas_int;
public:
    // Construtor antigo que recebe diretamente um vetor de FeedForwards (camadas)
    RedeNeural(const std::vector<FeedForward>& camadas_iniciais);

    // Construtor que recebe um vetor de FeedForwards (cada camada)
    RedeNeural(const std::vector<int>& numNeuronsPorCamada);

    RedeNeural(const RedeNeural &rede_copiar);

    // Função de feedforward completo, passando X por todas as camadas
    vector<double> feedForwardCompleto(const std::vector<double>& X);

    // Função para crossover entre duas redes neurais
    static RedeNeural crossover(const RedeNeural& redeA, const RedeNeural& redeB);

    // Função para aplicar mutação em toda a rede neural
    void mutar(double mutation_factor);

    std::vector<int> getLayers();
};

#endif // REDE_NEURAL_HPP
