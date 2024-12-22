// Bibliotecas:
#include "pacman.hpp"
#include "mapa.hpp"
#include "rede_neural.hpp"
#include "popPacman.hpp"
#include "fantasma.hpp"
#include <iostream>
#include <vector>
#include <unistd.h>

int main() {
    Mapa mapa; // criação do mapa
    const std::vector<int> camadas = {7,4,2}; // camadas da rede neural*/
    Population pop(1,5,camadas,17,1); // local que a população nasce
    
    // local onde os fantasmas nascem
    Fantasma fantasma1(9,4);
    Fantasma fantasma2(10,5);
    Fantasma fantasma3(9,9);
    Fantasma fantasma4(4,1);
    std::vector<Fantasma> fantasmas = {fantasma1,fantasma2,fantasma3,fantasma4}; // armazenados nesse vetor

    int geracao = 0; // inicializa um contador de gerações
    while (true) { // loop infinito de gerações

        for(int i = 0; i < NUM_INDIVIDUOS; i++){ // executa para cada individu
            
            //reseta os fantasmas antes de cada episodio
            for(int f=0;f<(int)fantasmas.size();f++){
                fantasmas[f].reset();
            }

            bool morreu = false;

            for(int step = 0; step < MAXTIME; step++){ // numero de passos máximos 
                //printf("Rodando indivíduo %d da geração %d:\n",i, geracao);
                pop.individuos[i].movePacman(mapa, MAXTIME, fantasmas); // fantasmas no mapa

                //move os fantasmas
                for(int k = 0; k < (int)fantasmas.size(); k++){
                    fantasmas[k].moveFantasma(mapa, pop.individuos[i].y, pop.individuos[i].x);
                }
                
                if(geracao>0 && i == 0 && pop.history[geracao-1] == 101){
                    printf("melhor da geração %d: %.2f\n", geracao-1, pop.history[geracao-1]);
                    mapa.display(pop.individuos[i].y, pop.individuos[i].x, fantasmas); // desenha a grade atualizada
                    std::cout << "\n----------------------------------------------\n" << std::endl;
                }

                // verifica se o pacman morreu (colidiu com um fantasma)
                morreu = mapa.tamorto(pop.individuos[i].y, pop.individuos[i].x, fantasmas);
                if(morreu){
                    if(i == 0 && geracao>0 && pop.history[geracao-1] == 101)
                        printf("Degustado saborosamente\n\n");
                    pop.individuos[i].reset();
                    break;
                }

                if(i == 0 && geracao > 0 && pop.history[geracao-1] == 101)
                    sleep(1);
            }
            if(i == 0)
                sleep(1);
            mapa.reset(); // reseta o mapa para o próximo episódio
        }
        // após todos os individuos da pop terem jogado passa para a proximo geração
        pop.nextGen();
        sleep(3);
        
        pop.history[geracao] = pop.individuos[0].fitness;
        geracao++;

        printf("\nHistorico de fitness:\n");
        for(size_t j = 0; j < pop.history.size(); j++){
            printf("%ld - %.2f\n", j, pop.history[j]);
        }
        sleep(3);
    }

    return 0;
}
