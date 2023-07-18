#include "Pieces/BasePiece.h"

class ChessBoard
{
public:
    ChessBoard();
private:
    std::vector<BasePiece*> m_vecPieces;
};