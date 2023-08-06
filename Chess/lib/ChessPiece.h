#pragma once
#include <stdint.h>
#include <string>
#include <sstream>

enum ChessPieceColor
{
    WHITE = 0,
    BLACK = 8,
};

enum ChessPieceType
{
    NONE = 0,
    KING = 1,
    QUEEN = 2,
    BISHOP = 3,
    KNIGHT = 4,
    ROOK = 5,
    PAWN = 6,
};

class ChessPiece
{
public:
    ChessPiece(uint8_t flag);

    ChessPieceColor GetColor() const;
    ChessPieceType GetType() const;
    char GetNotation() const;
    uint8_t GetFlag() const;
private:
    uint8_t m_infoFlag;
};