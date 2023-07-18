#pragma once
#include <stdint.h>
#include <vector>
#include <string>
#include <sstream>

const uint8_t BOARDLENGTH = 8;
// The board will be imagined as 0,0 (A,1) being the lower left corner, and 7,7 (H,8) in the upper right.
// White pieces are assumed to start at the bottom and Black at the top.
// Pawns will only be able to move one direction, up if they are White and down if they are Black.

/*
    --------
      A|B|C|D|E|F|G|H
    8|_|_|_|_|_|_|_|_|8
    7|_|_|_|_|_|_|_|_|7
    6|_|_|_|_|_|_|_|_|6
    5|_|_|_|_|_|_|_|_|5
    4|_|_|_|_|_|_|_|_|4
    3|_|_|_|_|_|_|_|_|3
    2|_|_|_|_|_|_|_|_|2
    1|_|_|_|_|_|_|_|_|1
      A|B|C|D|E|F|G|H
*/


enum PieceColor
{
    WHITE,
    BLACK
};

struct PiecePos
{
    PiecePos(uint8_t x, uint8_t y): x(x), y(y) {};
    uint8_t x;
    uint8_t y;

    std::string chessPos() 
    {
        std::ostringstream out;
        out << (uint8_t)('A' + x) << ", " << (uint32_t)y;
        return out.str();
    }
};

class BasePiece
{
public:
    BasePiece(uint8_t x, uint8_t y, PieceColor color): m_pos(x,y), m_color(color) {};

    virtual std::vector<PiecePos> PossibleMoves(std::vector<BasePiece*> piecesOnBoard) = 0;
    PiecePos m_pos;
    PieceColor m_color;
};

class King : public BasePiece
{
public:
    King(uint8_t x, uint8_t y, PieceColor color): BasePiece(x,y,color){};
    virtual std::vector<PiecePos> PossibleMoves(std::vector<BasePiece*> piecesOnBoard);
private:
};

class Queen : public BasePiece
{
public:
    Queen(uint8_t x, uint8_t y, PieceColor color): BasePiece(x,y,color){};
    virtual std::vector<PiecePos> PossibleMoves(std::vector<BasePiece*> piecesOnBoard);
private:
};

class Bishop : public BasePiece
{
public:
    Bishop(uint8_t x, uint8_t y, PieceColor color): BasePiece(x,y,color){};
    virtual std::vector<PiecePos> PossibleMoves(std::vector<BasePiece*> piecesOnBoard);
private:
};

class Knight : public BasePiece
{
public:
    Knight(uint8_t x, uint8_t y, PieceColor color): BasePiece(x,y,color){};
    virtual std::vector<PiecePos> PossibleMoves(std::vector<BasePiece*> piecesOnBoard);
private:
};

class Rook : public BasePiece
{
public:
    Rook(uint8_t x, uint8_t y, PieceColor color): BasePiece(x,y,color){};
    virtual std::vector<PiecePos> PossibleMoves(std::vector<BasePiece*> piecesOnBoard);
private:
};

class Pawn : public BasePiece
{
public:
    Pawn(uint8_t x, uint8_t y, PieceColor color): BasePiece(x,y,color){};
    virtual std::vector<PiecePos> PossibleMoves(std::vector<BasePiece*> piecesOnBoard);
private:
};