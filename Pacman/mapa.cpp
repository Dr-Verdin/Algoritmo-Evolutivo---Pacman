#include "mapa.hpp"
#include "pacman.hpp"  // Para exibir a posição do Player (caso necessário em algum método)
#include <iostream>



// verificar se houver uma colisão
bool Mapa::checkCollision(int x, int y) {
    if(x < 0 || x >= COLS || y < 0 || y >= ROWS) {
        return true; // Fora dos limites, é tratado como colisão mesmo assim
    }
    return grid[y][x] == 1; // Há uma parede
}

// Exibir o estado atual do mapa (incluindo as paredes, os fantasmas e o pacman)
void Mapa::display(int playerY, int playerX, std::vector<Fantasma> fantasmas)  { 
    for (int i = 0; i < ROWS; i++) { // linhas
        for (int j = 0; j < COLS; j++) { // coluna
            if (i == playerY && j == playerX){ // verifica se as coord correspondem as posições do personagens
                if(geracao2 > 100)
                    std::cout << "P "; // Desenha o player na posição atual
            } else if (collisionGrid[i][j]){
                if(geracao2 > 100)
                    std::cout << "X "; // Exibe "X" se houve colisão
                collisionGrid[i][j] = false;
            }else{
                bool tem_fantasma_aqui = false;

                for(int f=0;f<(int)fantasmas.size();f++){
                    if (i == fantasmas[f].y && j == fantasmas[f].x){ // verifica se as coord correspondem as posições do personagens
                        tem_fantasma_aqui=true;
                    } // Desenha o fantasma na posição atual
                }
                
                if(tem_fantasma_aqui){
                    if(geracao2 > 100)
                        std::cout << "F ";
                }else{
                    if(geracao2 > 100)
                        std::cout << (grid[i][j] == 1 ? "1 " : "0 ");
                }
                
            }
        }
        if(geracao2 > 100)
            std::cout << std::endl; // nova linha da matriz
    }
}

// verifica se o pacman morreu
bool Mapa::tamorto(int playerY, int playerX, std::vector<Fantasma> fantasmas){
    for(int f=0;f<(int)fantasmas.size();f++){
        if (playerX == fantasmas[f].x && playerY == fantasmas[f].y){ // verifica se as coord correspondem as posições do personagens
            return true;
        } // Desenha o fantasma na posição atual
    }
    return false;
}

// reseta a grade de feromonios
void Mapa::reset(){
    feromoniosGrid[ROWS][COLS] = { 0 };
}