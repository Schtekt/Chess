#include <gtest/gtest.h>
#include "Pieces/BasePiece.h"

TEST(ROOK, BasicMove)
{
    uint8_t x = 4;
    uint8_t y = 4;

    Rook rook(x, y, PieceColor::WHITE);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&rook);

    auto whiteMoves = rook.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 14);
}

TEST(ROOK, CornerMove)
{
    uint8_t x = 0;
    uint8_t y = 0;

    Rook rook(x, y, PieceColor::WHITE);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&rook);

    auto whiteMoves = rook.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 14);
}

TEST(ROOK, BlockedInCorner)
{
    uint8_t x = 0;
    uint8_t y = 0;

    Rook rook(x, y, PieceColor::WHITE);
    Pawn pawnVertical(x, y + 1, PieceColor::WHITE);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&rook);
    pieces.push_back(&pawnVertical);

    auto whiteMoves = rook.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 7);
}

TEST(ROOK, AttackHorisontal)
{
    uint8_t x = 4;
    uint8_t y = 4;

    Rook whiteRook(x, y, PieceColor::WHITE);
    Rook blackRook(x, y - 2, PieceColor::BLACK);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&whiteRook);
    pieces.push_back(&blackRook);

    auto whiteMoves = whiteRook.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 12);
}