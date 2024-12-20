#ifndef PACMAN_HPP
    #define PACMAN_HPP

    #include <vector>
    #include <iostream>
    #include <cmath>
    #include "rede_neural.hpp"  // Certifique-se de que a classe RedeNeural está definida aqui
    #include "fantasma.hpp"
    #include "mapa.hpp"

    class Mapa;
    class Fantasma;

    const std::vector<int> PADRAO = {3,3,2};

    class Pacman {
    public:
        int x;                // Posição X do Pacman
        int y;                // Posição Y do Pacman
        int sX;               // Posição X do spawn
        int sY;               // Posição Y do spawn
        int objetivoX;
        int objetivoY;
        RedeNeural rede;      // A rede neural associada ao Pacman
        int step_count;
        double fitness; // Aptidão do indivíduo.

        Pacman();
        // Construtor que recebe a posição inicial e as camadas da rede neural
        Pacman(int startX, int startY, const std::vector<int> &camadas, int objetivoX, int objetivoY);
        
        void reset();

        // Método para mover o Pacman
        void movePacman(Mapa& mapa, int maxTime,std::vector<Fantasma> fantasmas);

        Pacman mutate(double factor);
        Pacman crossover(Pacman &amiguinho); // brotheragem :3
    };

#endif 