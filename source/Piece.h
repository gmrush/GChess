#pragma once
#ifndef PIECE
#define PIECE

#include "SDL.h"
#include "SDL_image.h"
#include "Move.h"

const int None = 0;
const int King = 1;
const int Pawn = 2;
const int Knight = 3;
const int Bishop = 4;
const int Rook = 5;
const int Queen = 6;
const int White = 8;
const int Black = 16;

class Piece {
public:
	Piece();
	Piece(int);
	Piece(int, SDL_Rect*);
	Piece(int, SDL_Rect*, int);
	~Piece();
	void setType(int);
	int getColor();
	int getType();
	void setClip(SDL_Rect*);
	SDL_Rect* getClip();
	bool getHasMoved();
	void setHasMoved();
	int getPos();
	void setPos(int);
private:
	int m_color = 0;
	int m_type = 0;
	bool m_hasMoved = false;
	int m_pos;
	SDL_Rect* m_clip = NULL;
};

#endif PIECE //PIECE