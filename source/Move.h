#pragma once
#ifndef MOVE
#define MOVE

// Move "types"
//0 for standard move
//1 for capture
//2 for short castle
//3 for long castle
//4 for promotion
//5 for en passant

class Move {
public:
	Move(int, int);
	Move(int, int, int);
	int prev;
	int target;
	int type;
};

#endif MOVE //MOVE