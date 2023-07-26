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

struct ChessPiecePos
{
    ChessPiecePos(uint8_t x, uint8_t y): x(x), y(y) {};
    uint8_t x;
    uint8_t y;

    bool operator==(const ChessPiecePos& other) const
    {
        return x == other.x && y == other.y;
    }

    std::string chessPos() 
    {
        std::ostringstream out;
        out << (uint8_t)('A' + x) << ", " << (uint32_t)y;
        return out.str();
    }
};

class ChessPiece
{
public:
    ChessPiece(unsigned int flag, ChessPiecePos pos);

    bool IsWhite();
    char GetNotation();
private:
    unsigned int m_infoFlag;
    ChessPiecePos m_pos;
};