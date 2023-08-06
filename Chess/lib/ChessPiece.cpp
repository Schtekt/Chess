#include "ChessPiece.h"

ChessPiece::ChessPiece(uint8_t flag): m_infoFlag(flag)
{

}

ChessPieceColor ChessPiece::GetColor() const
{
    return static_cast<ChessPieceColor>(m_infoFlag & ChessPieceColor::BLACK);
}

ChessPieceType ChessPiece::GetType() const
{
    return static_cast<ChessPieceType>(m_infoFlag & ~ChessPieceColor::BLACK);
}

char ChessPiece::GetNotation() const
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

uint8_t ChessPiece::GetFlag() const
{
    return m_infoFlag;
}
