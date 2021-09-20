#include "Game.h"

Game::Game() { //Constructor
	SDL_Init(SDL_INIT_VIDEO); //Initialize video
	IMG_Init(IMG_INIT_PNG);
	m_window = SDL_CreateWindow("GChess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 768, 768, NULL); //Create window
	m_renderer = SDL_CreateRenderer(m_window, -1, 0); //Create renderer
	m_board = new Board(m_renderer);
	m_board->drawBoard(); //Draw checkerboard pattern
	m_board->loadSprites(); //Assigned sprites to pieces
	SDL_RenderPresent(m_renderer);
}

Game::~Game() { //Destructor
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	IMG_Quit();
	SDL_Quit();
	delete m_board;
}

void Game::Update() { //Update game state
	int mouseX, mouseY;
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) { //Exit button
			exit(0);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
			if (e.button.button == SDL_BUTTON_LEFT) { //Left click
				SDL_GetMouseState(&mouseX, &mouseY); //Set coordinates to current mouse pos
				m_board->playerMove(mouseX, mouseY); //Pass mouse coordinates to board
				m_board->updateBoard();
			}
	} 
}

void Game::GameLoop() { //Main loop, should be fixed ticks per second
	std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now(); //Get current clock time
	m_board->setupBoard();
	m_board->generateMoves();
	while (true) {
		Update();
		t += std::chrono::milliseconds(DELAY);
		std::this_thread::sleep_until(t); //Sleep until desired time has passed
	}
}
