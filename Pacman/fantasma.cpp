#include "fantasma.hpp"

Fantasma::Fantasma(){}

Fantasma::Fantasma(int startX, int startY)
    : x(startX), y(startY), sX(startX), sY(startY)/*Posição inicial do fantasma*/{}

void Fantasma::moveFantasma(Mapa& mapa, int pacmanY, int pacmanX){
    float max_feromonio = 0;
    float feromonio;
    int xadd = 0;
    int yadd = 0;

    // buscar o maximo feromonio
    for(int auxX = -1; auxX < 2; auxX++){
        for(int auxY = -1; auxY < 2; auxY++){
            if (abs(auxX) == abs(auxY)) continue;

            if(auxX + x < 0 || auxY + y < 0 || auxX + x >= COLS || auxY + y >= ROWS) continue;

            feromonio = mapa.feromoniosGrid[auxY+y][auxX+x];
            if(feromonio > max_feromonio){
                max_feromonio = feromonio;
                xadd = auxX;
                yadd = auxY;
            }
        }
    }

    if (max_feromonio == 0) {
        xadd = 0;
        yadd = 0;

        // Direita
        for (int i = 0; (y + i < ROWS) && mapa.grid[y + i][x] == 0; i++) {
            if (y + i == pacmanY && x == pacmanX) {
                xadd = 0;
                yadd = 1;
                break;
            }
        }

        // Esquerda
        for (int i = 0; (y - i >= 0) && mapa.grid[y - i][x] == 0; i++) {
            if (y - i == pacmanY && x == pacmanX) {
                xadd = 0;
                yadd = -1;
                break;
            }
        }

        // Cima
        for (int i = 0; (x + i < COLS) && mapa.grid[y][x + i] == 0; i++) {
            if (y == pacmanY && x + i == pacmanX) {
                xadd = 1;
                yadd = 0;
                break;
            }
        }

        // Baixo
        for (int i = 0; (x - i >= 0) && mapa.grid[y][x - i] == 0; i++) {
            if (y == pacmanY && x - i == pacmanX) {
                xadd = -1;
                yadd = 0;
                break;
            }
        }

        // Se não encontrou o Pac-Man, move aleatoriamente
        if (xadd == 0 && yadd == 0) {
            if (rand() % 2 == 0) {
                xadd = (rand() % 2) * 2 - 1; // Aleatório -1 ou 1
                yadd = 0;
            } else {
                xadd = 0;
                yadd = (rand() % 2) * 2 - 1; // Aleatório -1 ou 1
            }
        }
    }

    int newX = x + xadd;
    int newY = y + yadd;

    if(mapa.checkCollision(newX, newY)){
        mapa.collisionGrid[newY][newX] = true;
    } else {
        x = newX; 
        y = newY;
        mapa.collisionGrid[newY][newX] = false;
    }
}

// reseta o fantasma
void Fantasma::reset(){
    x = sX;
    y = sY;
}
