#include "popPacman.hpp"

// inicializa a população
Population::Population(int spawnX,int spawnY,const std::vector<int> camadas, int objetivoX, int objetivoY) : gen_atual(0), spawn(spawnX,spawnY), objetivo(objetivoX, objetivoY){
    for (int i = 0; i < NUM_INDIVIDUOS; ++i) {
        // Cria o jogador com a posição de spawn e a rede neural
        // O vetor 'camadas' define a arquitetura da rede neural do jogador
        individuos.emplace_back(spawnX, spawnY, camadas, objetivoX, objetivoY);
    }
}

void Population::EvaluateSort(){
    int cont = 0;
    for(size_t i = 0; i < individuos.size(); i++){
        double distancia = std::sqrt((individuos[i].x - objetivo.x)*(individuos[i].x - objetivo.x) + (individuos[i].y - objetivo.y)*(individuos[i].y - objetivo.y));
        
        if(distancia == 0){
            cont++;
            individuos[i].fitness = 101.0; 
        } else {
            individuos[i].fitness = (100.0 / distancia);
        }
    }
    printf("\nChegou ao objetivo: %d\n", cont);

    // Ordenar a população pela distância (fitness) - menor distância é melhor
    std::sort(individuos.begin(), individuos.end(), [](const Pacman& a, const Pacman& b){
        return a.fitness > b.fitness;
    });
}

// Função para encontrar os 5 melhores individuos
std::vector<Pacman> Population::getTopK(){
    return std::vector<Pacman>(individuos.begin(), individuos.begin() + std::min(TOP_K, NUM_INDIVIDUOS));
}

// Função para gerar a próxima geração
void Population::nextGen(){ 
    // Ordena pelos melhores
    EvaluateSort();

    std::vector<Pacman> newPop(NUM_INDIVIDUOS);

    // Obtém os K melhores indivíduos da geração anterior
    std::vector<Pacman> melhores = getTopK();
    history.push_back(melhores[0].fitness);

    // Crossover (cruzar os individuos da geração anterior com os melhores) e mutação 
    // Os K melhores são passados para frente automaticamente
    // Ou acontece crossover, ou acontece mutação
    int j1, j2;    
    for (size_t i = TOP_K; i < NUM_INDIVIDUOS; i++) {
        if(std::rand() % 2){
            // Crossover (entre diferentes)
            do{
                j1 = std::rand() % TOP_K;
                j2 = std::rand() % TOP_K;
            } while(j1==j2);
            
            newPop[i] = melhores[j1].crossover(melhores[j2]);
        }else{
            // Mutação
            j1 = std::rand() % TOP_K;
            newPop[i] = melhores[j1].mutate(MUTATE_POWER);
        }
    }

    // passar os melhores para a próxima geração
    for(size_t i = 0; i < TOP_K; i++){
        newPop[i] = melhores[i];
    }
    // Atualiza a população
    individuos = std::move(newPop);
}
