#include <gtest/gtest.h>
#include "Pieces/BasePiece.h"

TEST(BISHOP, BasicMove)
{
    uint8_t x = 4;
    uint8_t y = 4;

    Bishop bishop(x, y, PieceColor::WHITE);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&bishop);

    auto whiteMoves = bishop.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 13);
}

TEST(BISHOP, CornerMove)
{
    uint8_t x = 0;
    uint8_t y = 0;

    Bishop bishop(x, y, PieceColor::WHITE);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&bishop);

    auto whiteMoves = bishop.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 7);
}

TEST(BISHOP, BlockedInCorner)
{
    uint8_t x = 0;
    uint8_t y = 0;

    Bishop bishop(x, y, PieceColor::WHITE);
    Pawn pawn(x + 1, y + 1, PieceColor::WHITE);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&bishop);
    pieces.push_back(&pawn);

    auto whiteMoves = bishop.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 0);
}

TEST(BISHOP, AttackDiagonal)
{
    uint8_t x = 4;
    uint8_t y = 4;

    Bishop whiteBishop(x, y, PieceColor::WHITE);
    Bishop blackBishop(x - 2, y - 2, PieceColor::BLACK);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&whiteBishop);
    pieces.push_back(&blackBishop);

    auto whiteMoves = whiteBishop.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 11);
}