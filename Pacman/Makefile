# Variáveis
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I/usr/local/include/opencv4
# LDFLAGS = -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgcodecs
LDFLAGS = -lncurses
TARGET = batata
SRC = main.cpp pacman.cpp mapa.cpp rede_neural.cpp feedforward.cpp popPacman.cpp fantasma.cpp

# Regra padrão
all: $(TARGET)

# Regra para construir o executável
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

# Regra para limpar os arquivos gerados
clean:
	rm -f $(TARGET)

test:
	clear
	make clean
	make
	./batata