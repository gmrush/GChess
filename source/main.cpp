// George Rush | May 2021 | Chess

#include "SDL.h"
#include "Game.h"

int main(int argc, char* argv[]) {
	Game chess = Game();
	chess.GameLoop();
	return 0;
}
