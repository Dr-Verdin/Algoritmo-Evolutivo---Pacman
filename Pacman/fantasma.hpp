#ifndef FANTASMA_HPP
    #define FANTASMA_HPP

    #include <iostream>
    #include <vector>
    #include "mapa.hpp"
    #include "pacman.hpp"

    class Mapa;
    class Pacman;  

    class Fantasma{ 
        public:
            int x;
            int y;
            int sX;
            int sY;

            Fantasma();
            Fantasma(int startX, int startY);
            void moveFantasma(Mapa& mapa, int pacmanY, int pacmanX);
            void reset();
    };


#endif