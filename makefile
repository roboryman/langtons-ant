main:
	g++ -c main.cpp Sim.cpp -std=c++11
	g++ main.o Sim.o -o ant -lsfml-graphics -lsfml-window -lsfml-system -pthread
	rm main.o
	rm Sim.o