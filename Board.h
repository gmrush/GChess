#pragma once
#ifndef BOARD
#define BOARD

#include "SDL.h"
#include "Piece.h"
#include <array>
#include <string>
#include <iostream>
#include <vector>

const int SQUARE_SIZE = 96;
const int spriteYOffset = 213;
const int spriteXOffset = 213;
const int LIGHT_COL[3] = { 245, 210, 175 };
const int DARK_COL[3] = { 140, 90, 70 };
const int knightOffset[8] = { -17, 17, -10, 10, -6, 6, -15, 15 }; //Knight move
const int kingOffset[8] = { -7, -8, -9, -1, 1, 7, 8, 9 }; //King move
const std::string startingFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w"; //"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

class Board {
public:
	Board(SDL_Renderer*); //Constructor
	~Board(); //Destructor
	void drawBoard(); //Draw board
	void drawSquare(int, int, int, int, int); //Draw new squares
	void drawSquareAtPos(int, int);
	void loadSprites(); //Load sprite clips
	void drawSprites(int, int, SDL_Rect*); //Draw sprite clips
	void setupBoard(); //Setup board on start up
	void updateBoard();
	void setClipFromType(Piece*); 
	void convertFEN(std::string); //Get board position from FEN string
	void playerMove(int, int); //Mouse click event
	void moveToEmpty();
	void moveToCapture();
	void shortCastle();
	void longCastle();
	void pawnPromote();
	void enPassant();
	void switchTurn(); //Switch turn
	Piece* pieceFromPos(int);

	//Piece move logic
	void generateMoves();
	void generateAttackedPositions();
	int validateMove();
	void pawnMove(Piece*);
	void bishopMove(Piece*);
	void rookMove(Piece*);
	void queenMove(Piece*);
	void knightMove(Piece*);
	void kingMove(Piece*);
	void castleCheck(Piece*);
	void offsetMove(Piece*, const int[8]);
	void diagMove(Piece*);
	void orthoMove(Piece*);
private:
	SDL_Renderer* m_renderer;
	SDL_Surface* m_piecesTexture = IMG_Load("pieces.png");
	SDL_Rect* m_spriteClips[12];
	Piece* m_pieceToMove = nullptr;
	int m_turn = White;
	int m_prevPos;
	int m_targetPos;
	int m_enpassant;
	int m_setup;
	float m_move = 1;
	std::vector<int> m_squaresToUpdate;
	std::vector<Move*> m_moves;
	std::vector<Piece*> m_pieces;
	std::vector<int> m_attackedPos;
};

#endif //BOARD