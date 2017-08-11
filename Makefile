game: main.cpp
	g++ -std=c++11 -o game main.cpp board.cpp util.cpp
clean:
	rm game
