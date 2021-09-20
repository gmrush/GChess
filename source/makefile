CXX = g++
CXXFLAGS = 

GChess: main.o Game.o Move.o Piece.o Board.o
	$(CXX) $(CXXFLAGS) main.o Game.o Move.o Piece.o Board.o -o GChess

main.o: Game.h SDL.h main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Game.o: Game.h Game.cpp
	$(CXX) $(CXXFLAGS) -c Game.cpp

Move.o: Move.h Move.cpp
	$(CXX) $(CXXFLAGS) -c Move.cpp

Piece.o: Piece.h Piece.cpp
	$(CXX) $(CXXFLAGS) -c Piece.cpp

Board.o: Board.h Board.cpp
	$(CXX) $(CXXFLAGS) -c Board.cpp