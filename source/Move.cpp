#include "Move.h"

Move::Move(int p, int t) {
	prev = p;
	target = t;
	type = 0;
}

Move::Move(int p, int t, int ty) {
	prev = p;
	target = t;
	type = ty;
}
