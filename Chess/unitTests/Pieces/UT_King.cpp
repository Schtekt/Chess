#include <gtest/gtest.h>
#include "Pieces/BasePiece.h"

TEST(KING, BasicMove)
{
    uint8_t x = 4;
    uint8_t y = 4;

    King king(x, y, PieceColor::WHITE);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&king);

    auto kingMoves = king.PossibleMoves(pieces);

    ASSERT_EQ(kingMoves.size(), 8);
}

TEST(KING, cornerMove)
{
    uint8_t x = 0;
    uint8_t y = 0;

    King king(x, y, PieceColor::WHITE);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&king);

    auto kingMoves = king.PossibleMoves(pieces);

    ASSERT_EQ(kingMoves.size(), 3);
}

TEST(KING, blockedByFriendlyPiece)
{
    uint8_t x = 0;
    uint8_t y = 0;

    King king(x, y, PieceColor::WHITE);
    Pawn pawn(x, y + 1, PieceColor::WHITE);
    std::vector<BasePiece*> pieces;
    pieces.push_back(&king);
    pieces.push_back(&pawn);

    auto kingMoves = king.PossibleMoves(pieces);

    ASSERT_EQ(kingMoves.size(), 2);
}