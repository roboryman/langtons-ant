main:
	g++ -c main.cpp Sim.cpp TileMap.cpp GUI.cpp -std=c++14
	g++ main.o Sim.o TileMap.o GUI.o -o ant -ltgui -lsfml-graphics -lsfml-window -lsfml-system -pthread
	rm main.o
	rm Sim.o
	rm TileMap.o
	rm GUI.o