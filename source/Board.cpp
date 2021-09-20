#include "Board.h"

Board::Board(SDL_Renderer* renderer) { //Constructor
	//int m_setup = rand() % 2; //Random number for sides
	//m_turn = (m_setup == 0) ? White : Black; //0 white goes first, 1 black goes first
	for (int i = 0; i < 12; i++) {
		m_spriteClips[i] = new SDL_Rect();
	}
	convertFEN(startingFEN);
	m_renderer = renderer;
}

Board::~Board() { //Destructor
	for (int i = 0; i < 12; i++) {
		delete m_spriteClips[i];
	}
	m_pieces.clear();
	m_moves.clear();
	m_squaresToUpdate.clear();
}

void Board::drawBoard() { //Initialize board
	for (int rank = 0; rank < 8; rank++) {
		for (int file = 0; file < 8; file++) {
			if ((file + rank) % 2 == 0) drawSquare(LIGHT_COL[0], LIGHT_COL[1], LIGHT_COL[2], file, rank); //Light square
			else drawSquare(DARK_COL[0], DARK_COL[1], DARK_COL[2], file, rank); //Dark square
		}
	}
}

void Board::drawSquare(int r, int g, int b, int x, int y) { //Initialize squares
	SDL_Rect rect;
	rect.x = x * SQUARE_SIZE;
	rect.y = y * SQUARE_SIZE;
	rect.w = SQUARE_SIZE;
	rect.h = SQUARE_SIZE;
	SDL_SetRenderDrawColor(m_renderer, r, g, b, 255);
	SDL_RenderFillRect(m_renderer, &rect);
}

void Board::drawSquareAtPos(int x, int y) {
	if ((x + y) % 2 == 0) drawSquare(LIGHT_COL[0], LIGHT_COL[1], LIGHT_COL[2], x, y); //Light square
	else drawSquare(DARK_COL[0], DARK_COL[1], DARK_COL[2], x, y);
}

void Board::loadSprites() { //Load sprite clips. This is hard coded for specific image file
	for (int i = 0; i < 12; i++) {
		if (i >= 6) { //Second row
			m_spriteClips[i]->x = (i - 6) * spriteXOffset;
			m_spriteClips[i]->y = spriteYOffset;
		}
		else { //First row
			m_spriteClips[i]->x = i * spriteXOffset;
			m_spriteClips[i]->y = 0;
		}
		m_spriteClips[i]->w = spriteXOffset;
		m_spriteClips[i]->h = spriteYOffset;
	}
}

void Board::drawSprites(int x, int y, SDL_Rect* clip) { //Draw sprites on screen
	SDL_Rect renderRect = { x, y, SQUARE_SIZE, SQUARE_SIZE };
	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(m_renderer, m_piecesTexture);
	SDL_RenderCopy(m_renderer, newTexture, clip, &renderRect);
	SDL_RenderPresent(m_renderer);
}

void Board::setupBoard() { //Loop through squares, starts in top left corner
	for (int i = 0; i < m_pieces.size(); i++) { //Rank
		int pos = m_pieces[i]->getPos();
		drawSprites(pos % 8 * SQUARE_SIZE, (int) floor(pos / 8) * SQUARE_SIZE, m_pieces[i]->getClip());
	}
}

void Board::updateBoard() {
	for (int i = 0; i < m_squaresToUpdate.size(); i++) {
		int pos = m_squaresToUpdate[i];
		drawSprites((pos % 8) * SQUARE_SIZE, (int) floor(pos / 8) * SQUARE_SIZE, pieceFromPos(pos)->getClip());
	}
	m_squaresToUpdate.clear();
}

void Board::setClipFromType(Piece* p) {
	int col = p->getColor();
	int type = p->getType();
	if (col == 8) { //white pieces
		switch (type)
		{
		case King:
			p->setClip(m_spriteClips[0]);
			break;
		case Queen:
			p->setClip(m_spriteClips[1]);
			break;
		case Bishop:
			p->setClip(m_spriteClips[2]);
			break;
		case Knight:
			p->setClip(m_spriteClips[3]);
			break;
		case Rook:
			p->setClip(m_spriteClips[4]);
			break;
		case Pawn:
			p->setClip(m_spriteClips[5]);
			break;
		default:
			p->setClip(nullptr);
			break;
		}
	}
	else { //black pieces
		switch (type)
		{
		case King:
			p->setClip(m_spriteClips[6]);
			break;
		case Queen:
			p->setClip(m_spriteClips[7]);
			break;
		case Bishop:
			p->setClip(m_spriteClips[8]);
			break;
		case Knight:
			p->setClip(m_spriteClips[9]);
			break;
		case Rook:
			p->setClip(m_spriteClips[10]);
			break;
		case Pawn:
			p->setClip(m_spriteClips[11]);
			break;
		default:
			p->setClip(nullptr);
			break;
		}
	}
}

void Board::convertFEN(std::string fen) { //TODO finish
	int pos = 0;
	int fenDataTrack = 0; //to determine logic for data at end of fen string
	for (int i = 0; i < fen.length(); i++) {
		if (isdigit(fen[i])) pos += (int) fen[i] - 48; //subtract 48 because of ASCII
		else if (fen[i] != '/' && fen[i] != ' ') {
			switch (fen[i])
			{
			case 'p':
				m_pieces.push_back(new Piece(Black + Pawn, m_spriteClips[11], pos));
				break;
			case 'r':
				m_pieces.push_back(new Piece(Black + Rook, m_spriteClips[10], pos));
				break;
			case 'n':
				m_pieces.push_back(new Piece(Black + Knight, m_spriteClips[9], pos));
				break;
			case 'b':
				m_pieces.push_back(new Piece(Black + Bishop, m_spriteClips[8], pos));
				break;
			case 'k':
				m_pieces.push_back(new Piece(Black + King, m_spriteClips[6], pos));
				break;
			case 'q':
				m_pieces.push_back(new Piece(Black + Queen, m_spriteClips[7], pos));
				break;
			case 'P':
				m_pieces.push_back(new Piece(White + Pawn, m_spriteClips[5], pos));
				break;
			case 'R':
				m_pieces.push_back(new Piece(White + Rook, m_spriteClips[4], pos));
				break;
			case 'N':
				m_pieces.push_back(new Piece(White + Knight, m_spriteClips[3], pos));
				break;
			case 'B':
				m_pieces.push_back(new Piece(White + Bishop, m_spriteClips[2], pos));
				break;
			case 'K':
				m_pieces.push_back(new Piece(White + King, m_spriteClips[0], pos));
				break;
			case 'Q':
				m_pieces.push_back(new Piece(White + Queen, m_spriteClips[1], pos));
				break;
			default:
				break;
			}
			pos++;
		}
		if (pos == 63 && fenDataTrack == 0) if (fen[i] == 'b') {
			m_turn = Black; //determine which color's turn
			fenDataTrack++;
		}
	}
	std::string result = (m_turn == 8) ? "White" : "Black";
	std::cout << "Turn: " << result << std::endl;
}

Piece* Board::pieceFromPos(int pos) {
	for (int i = 0; i < m_pieces.size(); i++) if (m_pieces[i]->getPos() == pos) return m_pieces[i];
	return nullptr;
}

void Board::playerMove(int mouseX, int mouseY) {
	m_targetPos = (int)floor(mouseX / SQUARE_SIZE) + ((int)floor(mouseY / SQUARE_SIZE) * 8); //convert pixel coords to useable number
	Piece* p = pieceFromPos(m_targetPos);
	std::cout << m_targetPos << " ";
	if (p && !m_pieceToMove) { //clicked piece exists and is not currently holding piece
		m_pieceToMove = p;
		m_prevPos = m_targetPos;
		return;
	}
	if (m_pieceToMove) { //If player has picked up piece
		int move = validateMove();
		if (move == 1) moveToCapture(); //Place piece on occupied square
		else if (move == 0) moveToEmpty(); //Place piece on empty square
		else if (move == 2) shortCastle(); //king side castle
		else if (move == 3) longCastle(); //queen side castle
		else if (move == 4) pawnPromote(); //promote pawn
		else if (move == 5) enPassant(); //en passant
		m_pieceToMove = nullptr; //clear picked up piece
	}
}

void Board::moveToEmpty() {
	int cover = (m_turn == White) ? 8 : -8;
	m_pieceToMove->setHasMoved(); //Piece has now moved from original square
	drawSquareAtPos(m_prevPos % 8, floor(m_prevPos / 8)); //Cover previous location
	m_pieceToMove->setPos(m_targetPos);
	m_squaresToUpdate.push_back(m_targetPos);
	if (m_pieceToMove->getType() == Pawn && abs(m_prevPos - m_targetPos) == 16) m_enpassant = m_targetPos + cover; //determine en passant
	switchTurn(); //Change turns
}

void Board::moveToCapture() {
	m_pieceToMove->setHasMoved();
	drawSquareAtPos(m_targetPos % 8, floor(m_targetPos / 8)); //Cover sprite at target location, cover with current piece
	drawSquareAtPos(m_prevPos % 8, floor(m_prevPos / 8));
	for (int i = 0; i < m_pieces.size(); i++) if (m_pieces[i]->getPos() == m_targetPos) m_pieces.erase(m_pieces.begin() + i); //delete piece at target square
	m_pieceToMove->setPos(m_targetPos);
	m_squaresToUpdate.push_back(m_targetPos);
	switchTurn(); //Change turns
}

void Board::shortCastle() {
	m_pieceToMove->setPos(m_targetPos);
	Piece* r = pieceFromPos(m_targetPos + 1);
	r->setPos(m_targetPos - 1);

	drawSquareAtPos(m_prevPos % 8, floor(m_prevPos / 8));
	drawSquareAtPos((m_targetPos % 8) + 1, floor(m_prevPos / 8));
	m_squaresToUpdate.push_back(m_targetPos);
	m_squaresToUpdate.push_back(m_targetPos - 1);

	m_pieceToMove->setHasMoved();
	r->setHasMoved();
	switchTurn();
}

void Board::longCastle() {
	m_pieceToMove->setPos(m_targetPos);
	Piece* r = pieceFromPos(m_targetPos - 2);
	r->setPos(m_targetPos + 1);

	drawSquareAtPos(m_prevPos % 8, floor(m_prevPos / 8));
	drawSquareAtPos((m_targetPos % 8) - 2, floor(m_prevPos / 8));
	m_squaresToUpdate.push_back(m_targetPos);
	m_squaresToUpdate.push_back(m_targetPos + 1);

	m_pieceToMove->setHasMoved();
	r->setHasMoved();
	switchTurn();
}

void Board::pawnPromote() {
	std::string input;
	std::cout << "Enter piece to promote pawn to (n, b, q, r): ";
	std::cin >> input;
	int col = m_pieceToMove->getColor();
	if (input == "n") m_pieceToMove->setType(Knight + col);
	else if (input == "b") m_pieceToMove->setType(Bishop + col);
	else if (input == "q") m_pieceToMove->setType(Queen + col);
	else if (input == "r") m_pieceToMove->setType(Rook + col);

	drawSquareAtPos(m_prevPos % 8, floor(m_prevPos / 8));
	m_pieceToMove->setPos(m_targetPos);
	drawSquareAtPos(m_targetPos % 8, floor(m_targetPos / 8)); //cover sprite
	setClipFromType(m_pieceToMove); //update sprite clip
	m_squaresToUpdate.push_back(m_targetPos); //update board
	switchTurn();
}

void Board::enPassant() {
	int cover = m_turn == White ? 8 : -8;
	drawSquareAtPos(m_prevPos % 8, floor(m_prevPos / 8)); //cover previous square
	drawSquareAtPos(m_enpassant % 8, floor((m_enpassant + cover) / 8)); //cover previous square
	for (int i = 0; i < m_pieces.size(); i++) if (m_pieces[i]->getPos() == m_enpassant + cover) m_pieces.erase(m_pieces.begin() + i);
	m_pieceToMove->setPos(m_enpassant);
	m_squaresToUpdate.push_back(m_targetPos);
	switchTurn();
}

void Board::switchTurn() {
	m_move += 0.5f;
	m_turn == White ? m_turn = Black : m_turn = White;
	generateAttackedPositions();
	generateMoves(); //generate all possible moves for player
}

// == MOVE LOGIC == 

void Board::generateMoves() {
	m_moves.clear();
	std::cout << "\nClearing moves";
	for (int i = 0; i < m_pieces.size(); i++) { //generate moves
		if (m_pieces[i]->getColor() == m_turn) {
			switch (m_pieces[i]->getType()) { //Piece type
				case Pawn:
					pawnMove(m_pieces[i]);
					break;
				case Knight:
					knightMove(m_pieces[i]);
					break;
				case Bishop:
					bishopMove(m_pieces[i]);
					break;
				case Rook:
					rookMove(m_pieces[i]);
					break;
				case Queen:
					queenMove(m_pieces[i]);
					break;
				case King:
					kingMove(m_pieces[i]);
					break;
			}
		}
	}
	std::cout << "\nGenerated moves";
	m_attackedPos.clear();
	std::cout << "\nClearing attacked positions\n";
}

void Board::generateAttackedPositions() {
	for (int i = 0; i < m_moves.size(); i++) { //create vector of attacked squares from possible moves	
		if (m_moves[i]->type == 0) m_attackedPos.push_back(m_moves[i]->target);
	}
	std::cout << "\nGenerated attacked positions";
}

int Board::validateMove() {
	for (int i = 0; i < m_moves.size(); i++) if (m_prevPos == m_moves[i]->prev && m_targetPos == m_moves[i]->target) return m_moves[i]->type; //valid move, return move type
	return -1;
}

void Board::pawnMove(Piece* p) {
	int moveDirection = 1;
	int captureColor = White;
	if (m_turn == White) { // Change parameters for each colors turn
		moveDirection = -1;
		captureColor = Black;
	}

	int pos = p->getPos();
	int onceForward = pos + (moveDirection * 8);
	int twiceForward = pos + (moveDirection * 16);
	int captureLeft = pos + (moveDirection * 7);
	int captureRight = pos + (moveDirection * 9);
	if (!pieceFromPos(onceForward) && 0 <= onceForward && onceForward < 64) {
		if (onceForward < 8 || onceForward > 55) m_moves.push_back(new Move(pos, onceForward, 4)); //promote move
		else m_moves.push_back(new Move(pos, onceForward, 0)); //move forward once
		if (!pieceFromPos(twiceForward) && 0 <= twiceForward && twiceForward < 64 && !p->getHasMoved()) m_moves.push_back(new Move(pos, twiceForward, 0)); //move forward twice
	}
	if (captureLeft == m_enpassant || captureRight == m_enpassant) m_moves.push_back(new Move(pos, m_enpassant, 5)); //en passant check
	if (pieceFromPos(captureLeft) && 0 <= captureLeft && captureLeft < 64) 
		if (pieceFromPos(captureLeft)->getColor() == captureColor) m_moves.push_back(new Move(pos, captureLeft, 1)); //capture left
	if (pieceFromPos(captureRight) && 0 <= captureRight && captureRight < 64) 
		if (pieceFromPos(captureRight)->getColor() == captureColor) m_moves.push_back(new Move(pos, captureRight, 1)); //capture right
}

void Board::bishopMove(Piece* p) { //Bishop moves
	diagMove(p);
}
 
void Board::rookMove(Piece* p) { //Rook moves
	orthoMove(p);
}

void Board::queenMove(Piece* p) { //Queen moves, aka rook and bishop combined
	diagMove(p);
	orthoMove(p);
}

void Board::knightMove(Piece* p) { //Knight moves
	offsetMove(p, knightOffset);
}

void Board::kingMove(Piece* p) { //King moves, same logic as knights, with different offsets
	offsetMove(p, kingOffset);
	castleCheck(p);
	for (int i = 0; i < m_moves.size(); i++) { //clean moves list of moves that put king in check
		if (m_moves[i]->target == p->getPos()) std::cout << "Check ";
		if (m_moves[i]->prev == p->getPos()) {
			for (int n = 0; n < m_attackedPos.size(); n++)
				if (m_moves[i]->target == m_attackedPos[n]) m_moves.erase(m_moves.begin() + i);
		}
	}
}

void Board::castleCheck(Piece* p) {
	if (p->getHasMoved()) return; //king has moved, castling is not possible
	int kPos = p->getPos();
	Piece* kRook = pieceFromPos(kPos + 3);
	Piece* qRook = pieceFromPos(kPos - 4);
	if (!pieceFromPos(kPos + 1) && !pieceFromPos(kPos + 2) && kRook)
		if (!kRook->getHasMoved()) m_moves.push_back(new Move(kPos, kPos + 2, 2)); //short castle
	if (!pieceFromPos(kPos - 1) && !pieceFromPos(kPos - 2) && !pieceFromPos(kPos - 3) && qRook)
		if (!qRook->getHasMoved()) m_moves.push_back(new Move(kPos, kPos - 2, 3)); //long castle
}

void Board::offsetMove(Piece* p, const int off[8]) {
	int captureColor = (m_turn == White) ? Black : White;
	for (int i = 0; i < 8; i++) { //Loop through offsets
		int newPos = p->getPos() + off[i];
		if (0 <= newPos && newPos < 64) { //Check move is on board
			Piece* otherPiece = pieceFromPos(newPos);
			if (otherPiece) { //Check if square has piece
				if (otherPiece->getColor() == captureColor) //Check piece color
					m_moves.push_back(new Move(p->getPos(), newPos, 1)); //Capture
				else continue;
			}
			m_moves.push_back(new Move(p->getPos(), newPos, 0)); //In range and open square
		}
	}
}

void Board::diagMove(Piece* p) { //Move on diagonal
	int captureColor = (m_turn == White) ? Black : White;
	int offset[4] = { -7, 7, -9, 9 };

	for (int i = 0; i < 4; i++) {
		int newPos = p->getPos() + offset[i];
		while (0 <= newPos && newPos < 64) {
			Piece* otherPiece = pieceFromPos(newPos);
			if (otherPiece) { //Check if square has piece
				if (otherPiece->getColor() == captureColor) { //Check piece color
					m_moves.push_back(new Move(p->getPos(), newPos, 1)); //Capture
					break;
				}
				else break;
			}
			m_moves.push_back(new Move(p->getPos(), newPos, 0)); //In range and open square
			newPos += offset[i];
		}
	}
}

void Board::orthoMove(Piece* p) { //Move orthoganally
	int captureColor = (m_turn == White) ? Black : White;
	int offset[4] = { -8, 8, -1, 1 };

	for (int i = 0; i < 4; i++) {
		int newPos = p->getPos() + offset[i];
		while (0 <= newPos && newPos < 64 && (newPos % 8) + 1 != 0) { //no idea why the modulo check works
			Piece* otherPiece = pieceFromPos(newPos);
			if (otherPiece) { //Check if square has piece
				if (otherPiece->getColor() == captureColor) { //Check piece color
					m_moves.push_back(new Move(p->getPos(), newPos, 1)); //Capture
					break; //Cant go further, break
				}
				else break; //Friendly piece, break
			}
			m_moves.push_back(new Move(p->getPos(), newPos, 0)); //In range and open square
			newPos += offset[i];
		}
	}
}
