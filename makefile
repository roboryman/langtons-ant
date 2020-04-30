main:
	g++ -c main.cpp Sim.cpp Square.cpp -std=c++11
	g++ main.o Sim.o Square.o -o ANT -lsfml-graphics -lsfml-window -lsfml-system -pthread
	rm main.o
	rm Sim.o
	rm Square.o