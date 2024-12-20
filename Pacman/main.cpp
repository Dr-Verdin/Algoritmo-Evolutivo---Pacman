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
    /*1const std::vector<int> camadas = {11,6,2}; // camadas da rede neural*/
    const std::vector<int> camadas = {7,4,2}; // camadas da rede neural*/
    Population pop(1,5,camadas,17,1); // local que a população nasce
    
    // local onde os fantasmas nascem
    Fantasma fantasma1(9,4);
    Fantasma fantasma2(10,5);
    Fantasma fantasma3(8,5);
    Fantasma fantasma4(9,5);
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
                
                if(geracao>-1){
                    mapa.display(pop.individuos[i].y, pop.individuos[i].x, fantasmas); // desenha a grade atualizada
                    //std::cout << "\n----------------------------------------------\n" << std::endl;
                }

                // verifica se o pacman morreu (colidiu com um fantasma)
                morreu = mapa.tamorto(pop.individuos[i].y, pop.individuos[i].x, fantasmas);
                if(morreu){
                    //printf("Degustado saborosamente\n\n");
                    break;
                }
                //sleep(1);
            }
            //sleep(1);
        }
        // após todos os individuos da pop terem jogado passa para a proximo geração
        pop.nextGen();
        //sleep(3);
        // deppois que passa da geração 50 começa a impprimir o melhor pacman
        if(geracao>-1){
            printf("melhor da geração %d: %.2f\n", geracao, pop.history[geracao]);
            if(pop.history[geracao]<10){
                //sleep(15);
            }
            sleep(1);
        }
        geracao++;
    }

    return 0;
}
