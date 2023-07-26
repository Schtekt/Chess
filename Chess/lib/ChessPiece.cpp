#include "ChessPiece.h"

ChessPiece::ChessPiece(unsigned int flag, ChessPiecePos pos): m_infoFlag(flag), m_pos(pos)
{

}

bool ChessPiece::IsWhite()
{
    return !(m_infoFlag & ChessPieceColor::BLACK);
}


char ChessPiece::GetNotation()
{
    ChessPieceType type = static_cast<ChessPieceType>(m_infoFlag & ~ChessPieceColor::BLACK);

    switch(type)
    {
        case ChessPieceType::KING:
            return 'K';
        break;
        case ChessPieceType::QUEEN:
            return 'Q';
        break;
        case ChessPieceType::BISHOP:
            return 'B';
        break;
        case ChessPieceType::KNIGHT:
            return 'N';
        break;
        case ChessPieceType::ROOK:
            return 'R';
        break;
        case ChessPieceType::PAWN:
            return 'p';
        break;
        default:
            return ' ';
    }
}