main:
	g++ -c main.cpp Sim.cpp TileMap.cpp -std=c++11
	g++ main.o Sim.o TileMap.o -o ant -lsfml-graphics -lsfml-window -lsfml-system -pthread
	rm main.o
	rm Sim.o
	rm TileMap.o