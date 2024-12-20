#include "rede_neural.hpp"

// Construtor por camadas iniciais
RedeNeural::RedeNeural(const std::vector<FeedForward>& camadas_iniciais)
    : camadas(camadas_iniciais) {}

// construtor de copiar outra rede
RedeNeural::RedeNeural(const RedeNeural &rede_copiar) {
    // cópia profunda de camadas: cria novos objetos FeedForward
    for (const auto& camada : rede_copiar.camadas) {
        camadas.push_back(camada);  // supondo que FeedForward tenha um construtor de cópia
    }
    
    // Cópia superficial de camadas_int, que é um vetor de inteiros (não precisa de deep copy)
    camadas_int = rede_copiar.camadas_int;
}

// Construtor da RedeNeural
RedeNeural::RedeNeural(const std::vector<int>& numNeuronsPorCamada) {
    srand(static_cast<unsigned int>(time(0))); // inicializa o gerador de números aleatórios

    // Iterando sobre cada camada e criando a camada FeedForward
    for (int i = 0; i < (int)numNeuronsPorCamada.size() -1; ++i) {
        int numNeurons = numNeuronsPorCamada[i];  // número de neurônios para a camada i
        int numNeurons_nextLayer = numNeuronsPorCamada[i+1];

        // gerando pesos aleatórios para cada camada
        std::vector<std::vector<double>> pesos;
        for (int j = 0; j < numNeurons; ++j) {
            std::vector<double> linha;
            for (int k = 0; k < numNeurons_nextLayer; ++k) {
                linha.push_back(gerarNumeroAleatorio(-1.0, 1.0)); // Pesos aleatórios entre -1 e 1
            }
            pesos.push_back(linha);
        }

        // GErando viés aleatório para cada camada
        std::vector<double> viés;
        for (int j = 0; j < numNeurons; ++j) {
            viés.push_back(gerarNumeroAleatorio(-1.0, 1.0)); // Viés aleatório entre -1 e 1
        }

        // Criando a camada FeedForward com os pesos e viés gerados
        FeedForward camada(pesos, viés);
        camadas.push_back(camada); // adiciona a camada no vetor de camadas
    }

    // adiona a quant de neuronios por camada na lista de camadas_int
    for (int neurons : numNeuronsPorCamada) {
        this->camadas_int.push_back(neurons);
    }
}

// Função de feedforward, passando X por todas as camadas
std::vector<double> RedeNeural::feedForwardCompleto(const std::vector<double>& X) {
    std::vector<double> entrada = X;  // a entrada começa com o vetor X

    for (int i = 0; i < (int)camadas.size(); ++i) {
        
        entrada = camadas[i].feedForward(entrada);  // passa pela camada i
        
    }

    return entrada;  // A saída é a última camada
}

// função para crossover entre duas redes neurais
RedeNeural RedeNeural::crossover(const RedeNeural& redeA, const RedeNeural& redeB) {
    std::vector<FeedForward> novasCamadas;

    for (size_t i = 0; i < redeA.camadas.size(); ++i) {
        // REAliza o crossover entre as camadas correspondentes de redeA e redeB
        novasCamadas.push_back(redeA.camadas[i].crossover(redeB.camadas[i]));
    }

    return RedeNeural(novasCamadas);  // Retorna a nova rede gerada pelo crossover
}

// aplica mutação em toda a rede neural
void RedeNeural::mutar(double mutation_factor) {
    for (size_t i = 0; i < camadas.size(); ++i) {
        camadas[i].mutar(mutation_factor);  // aplica a mutação em cada camada
    }
}

// retornar o veotr camadas_int, numero de neuronio em cada camada da rede neural
std::vector<int> RedeNeural::getLayers(){
    return camadas_int;
}