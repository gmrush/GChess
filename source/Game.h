#pragma once
#ifndef GAME
#define GAME

#include "SDL.h"
#include "Board.h"
#include <stdlib.h>
#include <crtdbg.h>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <random>

const int DELAY = 17; //33 for 30fps, 17 is ~59fps

class Game {
public:
	Game(); //Constructor
	~Game(); //Destructor
	void Update(); //Update game state
	void GameLoop(); //Main loop
private:
	SDL_Window* m_window = NULL;
	SDL_Renderer* m_renderer = NULL;
	Board* m_board;
};

#endif GAME //GAME