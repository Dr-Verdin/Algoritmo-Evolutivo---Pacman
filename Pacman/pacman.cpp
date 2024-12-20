#include "pacman.hpp"

Pacman::Pacman():rede(PADRAO){}

Pacman::Pacman(int startX, int startY, const std::vector<int>& camadas, int objetivoX, int objetivoY)
    : x(startX), y(startY), sX(startX),sY(startY), objetivoX(objetivoX), objetivoY(objetivoY), rede(camadas), step_count(0), fitness(0) {  
}

void Pacman::movePacman(Mapa& mapa, int maxTime, std::vector<Fantasma> fantasmas){
    step_count += 1;

    std::vector<double> visao; // ou int

    /*// Tentativa 1 (11):
    int distUp = 0;
    for (int i = 0; (y - i) >= 0 && mapa.grid[y - i][x] == 0; ++i) { // Percorrer até o topo do mapa
        bool encontrouFantasma = false;

        // Verificar se há um fantasma nessa célula
        for (int j = 0; j < (int)fantasmas.size(); ++j) {
            if (mapa.grid[y - i][x] == 0 && y - i == fantasmas[j].y && x == fantasmas[j].x) {
                distUp = i;
                visao.push_back(distUp);
                visao.push_back(2); // 2 indica fantasma
                encontrouFantasma = true;
                break; // Encontrou um fantasma, pode sair do loop
            }
        }

        if (!encontrouFantasma) {
            // Se não for um fantasma, é uma parede (indicado por 1)
            if (mapa.grid[y - i][x] == 1) {
                distUp = i;
                visao.push_back(distUp);
                visao.push_back(1); // 1 indica parede
                break; // Encontrou a parede, pode sair do loop
            }
        }
    }

    int distDown = 0;
    for (int i = 0; (y + i) < ROWS && mapa.grid[y + i][x] == 0; ++i) { // Percorrer até o topo do mapa
        bool encontrouFantasma = false;

        // Verificar se há um fantasma nessa célula
        for (int j = 0; j < (int)fantasmas.size(); ++j) {
            if (mapa.grid[y + i][x] == 0 && y + i == fantasmas[j].y && x == fantasmas[j].x) {
                distUp = i;
                visao.push_back(distDown);
                visao.push_back(2); // 2 indica fantasma
                encontrouFantasma = true;
                break; // Encontrou um fantasma, pode sair do loop
            }
        }

        if (!encontrouFantasma) {
            // Se não for um fantasma, é uma parede (indicado por 1)
            if (mapa.grid[y + i][x] == 1) {
                distDown = i;
                visao.push_back(distDown);
                visao.push_back(1); // 1 indica parede
                break; // Encontrou a parede, pode sair do loop
            }
        }
    }

    int distLeft = 0;
    for (int i = 1; (x - i) >= 0 && mapa.grid[y][x - i] == 0; ++i) { // Percorrer até o topo do mapa
        bool encontrouFantasma = false;

        // Verificar se há um fantasma nessa célula
        for (int j = 0; j < (int)fantasmas.size(); ++j) {
            if (mapa.grid[y][x - i] == 0 && y == fantasmas[j].y && x - i == fantasmas[j].x) {
                distLeft = i;
                visao.push_back(distLeft);
                visao.push_back(2); // 2 indica fantasma
                encontrouFantasma = true;
                break; // Encontrou um fantasma, pode sair do loop
            }
        }

        if (!encontrouFantasma) {
            // Se não for um fantasma, é uma parede (indicado por 1)
            if (mapa.grid[y][x - i] == 1) {
                distLeft = i;
                visao.push_back(distLeft);
                visao.push_back(1); // 1 indica parede
                break; // Encontrou a parede, pode sair do loop
            }
        }
    }

    int distRight = 0;
    for (int i = 1; (x + i) < COLS && mapa.grid[y][x + i] == 0; ++i) { // Percorrer até o topo do mapa
        bool encontrouFantasma = false;

        // Verificar se há um fantasma nessa célula
        for (int j = 0; j < (int)fantasmas.size(); ++j) {
            if (mapa.grid[y][x + i] == 0 && y == fantasmas[j].y && x + i== fantasmas[j].x) {
                distRight = i;
                visao.push_back(distRight);
                visao.push_back(2); // 2 indica fantasma
                encontrouFantasma = true;
                break; // Encontrou um fantasma, pode sair do loop
            }
        }

        if (!encontrouFantasma) {
            // Se não for um fantasma, é uma parede (indicado por 1)
            if (mapa.grid[y][x + i] == 1) {
                distRight = i;
                visao.push_back(distRight);
                visao.push_back(1); // 1 indica parede
                break; // Encontrou a parede, pode sair do loop
            }
        }
    }

    double distanciaX = abs(objetivoX - x);
    double distanciaY = abs(objetivoY - y);

    std::vector<double> inRede;
    inRede.push_back((double)distanciaX);
    inRede.push_back((double)distanciaY);
    for(size_t i = 0; i < visao.size(); i++){
        inRede.push_back(visao[i]);
    }  
    inRede.push_back((double)step_count);
    // ----------------------------------------------------------------*/

    // Tentativa 2(7):
    for(int auxX = -1; auxX < 2; auxX++){
        for(int auxY = -1; auxY < 2; auxY++){
            int bloco = -1;
            bool skip = false;

            if (abs(auxX) == abs(auxY)) continue; // ignorar as diagonais

            if(auxX + x < 0 || auxY + y < 0 || auxX + x >= COLS || auxY + y >= ROWS) skip = true; // invalidos

            if(skip) bloco = 1;
            else{
                bool fantasma = false;

                for(int k = 0; k < (int)fantasmas.size(); k++){ 
                    if(auxX + x == fantasmas[k].x && auxY + y == fantasmas[k].y){
                        fantasma = true;
                        break;
                    }
                }

                if(fantasma)
                    bloco = 2;
                else
                    bloco = (double)mapa.grid[auxY+y][auxX+x];
            }

            visao.push_back(bloco);
        }
    }

    double distanciaX = abs(objetivoX - x);
    double distanciaY = abs(objetivoY - y);

    std::vector<double> inRede;
    inRede.push_back((double)distanciaX);
    inRede.push_back((double)distanciaY);
    for(size_t i = 0; i < visao.size(); i++){
        inRede.push_back(visao[i]);
    }
    inRede.push_back((double)step_count);
    // ---------------------------------------------------------------- */
    
    std::vector<double> resultado = rede.feedForwardCompleto(inRede); // não sei o que eu passo pra rede ainda 
    float dx = resultado[0];
    float dy = resultado[1];

    if(abs(dx) > abs(dy)){
        dy = 0;
        dx = (dx < 0) ? -1 : 1;
    } else {
        dx = 0;
        dy = (dy < 0) ? -1 : 1; 
    }

    mapa.feromoniosGrid[y][x] = step_count; // solta um feromonio (recebe o valor do step_count?)!?
    int newX = x + dx;
    int newY = y + dy;

    if (mapa.checkCollision(newX, newY)) {
        mapa.collisionGrid[newY][newX] = true;
    } else {
        x = newX;
        y = newY;
        mapa.collisionGrid[y][x] = false;
    }    
}

/*void Pacman::movePacman(Mapa& mapa, int maxTime, std::vector<Fantasma> fantasmas){
    step_count += 1;

    std::vector<double> visao;
    int bloco = -1;
    bool skip = false;

    for(int auxX = -1; auxX < 2; auxX++){
        for(int auxY = -1; auxY < 2; auxY++){
            skip = false;

            if((auxX == 0 && auxY == 0) || (auxX != 0 && auxY != 0)) continue;

            if(auxX + x < 0 || auxY + y < 0 || auxX + x >= COLS || auxY + y >= ROWS) skip = true;

            if(skip) bloco = 1.0;
            else{
                bool fantasma = false;

                for(int k = 0; k < (int)fantasmas.size(); k++){ 
                    if(auxX + x == fantasmas[k].x && auxY + y == fantasmas[k].y){
                        fantasma = true;
                        break;
                    }
                }

                if(fantasma)
                    bloco = 2.0;
                else
                    bloco = (double)mapa.grid[auxY+y][auxX+x];
            }

            visao.push_back(bloco);
        }
    }

    // !(confirir a rede neural e o que ela retorna)
    std::vector<double> resultado = rede.feedForwardCompleto(visao); 
    float dx = resultado[0];
    float dy = resultado[1];

    // !(confirir esse abs)
    if(abs(dx) > abs(dy)){
        dy = 0;
        dx = (dx < 0) ? -1 : 1;
    } else {
        dx = 0;
        dy = (dy < 0) ? -1 : 1; 
    }

    mapa.feromoniosGrid[y][x] = step_count; // solta um feromonio (recebe o valor do step_count?)!?
    int newX = x + dx;
    int newY = y + dy;

    if (mapa.colisao(newX, newY)) {
        mapa.collisionGrid[newY][newX] = true;
    } else {
        x = newX;
        y = newY;
        mapa.collisionGrid[y][x] = false;
    }
}*/

Pacman Pacman::crossover(Pacman &amiguinho){
    Pacman filho(x, y, rede.getLayers(), objetivoX, objetivoY);

    filho.rede = RedeNeural::crossover(this->rede, amiguinho.rede);

    return filho;
}

Pacman Pacman::mutate(double factor){
    Pacman filho(x, y, rede.getLayers(), objetivoX, objetivoY);  

    RedeNeural rede_copia = RedeNeural(rede);
    rede_copia.mutar(factor);
    filho.rede = rede_copia;

    return filho;
}

void Pacman::reset(){
    x = sX;
    y = sY;
    step_count = 0;
    fitness = 0;
}