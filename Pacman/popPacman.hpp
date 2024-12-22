#ifndef POPULACAO_HPP
    #define POPULACAO_HPP

    #include <vector>
    #include <iostream>
    #include <stdio.h>
    #include <stdlib.h>
    #include <cmath>
    #include <algorithm>  
    #include "pacman.hpp" 

    #define NUM_INDIVIDUOS 100
    #define TOP_K 5
    #define MAXTIME 100
    #define MUTATE_POWER 0.1 // potência da mutação 

    class Pacman;

    struct Ponto {
        int x, y;
        Ponto(int x, int y) : x(x), y(y) {}
    };

    class Population {
        public:
            std::vector<Pacman> individuos; 
            std::vector<float> history; // histórico de evolução dos scores (numero de passos)
            int gen_atual;
            Ponto spawn; // ?!
            Ponto objetivo;

            Population(int spawnx, int spawny, const std::vector<int> camadas, int objetivoX, int objetivoY);
            void EvaluateSort();
            std::vector<Pacman> getTopK();
            void nextGen();
    };

#endif