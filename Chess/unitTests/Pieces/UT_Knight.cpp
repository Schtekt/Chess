#include <gtest/gtest.h>
#include "Pieces/BasePiece.h"

TEST(KNIGHT, BasicMove)
{
    uint8_t x = 4;
    uint8_t y = 4;

    Knight knight(x, y, PieceColor::WHITE);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&knight);

    auto knightMoves = knight.PossibleMoves(pieces);

    ASSERT_EQ(knightMoves.size(), 8);
}

TEST(KNIGHT, cornerMove)
{
    uint8_t x = 0;
    uint8_t y = 0;

    Knight knight(x, y, PieceColor::WHITE);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&knight);

    auto knightMoves = knight.PossibleMoves(pieces);

    ASSERT_EQ(knightMoves.size(), 2);
}

TEST(KNIGHT, BlockedByFriendlyPiece)
{
    uint8_t x = 4;
    uint8_t y = 4;

    Knight knight(x, y, PieceColor::WHITE);
    Pawn pawn(x + 2, y + 1, PieceColor::WHITE);
    std::vector<BasePiece*> pieces;
    pieces.push_back(&knight);
    pieces.push_back(&pawn);

    auto knightMoves = knight.PossibleMoves(pieces);

    ASSERT_EQ(knightMoves.size(), 7);
}

TEST(KNIGHT, Attack)
{
    uint8_t x = 0;
    uint8_t y = 0;

    Knight knight(x, y, PieceColor::WHITE);
    Pawn pawn(x + 2, y + 1, PieceColor::BLACK);
    std::vector<BasePiece*> pieces;
    pieces.push_back(&knight);
    pieces.push_back(&pawn);

    auto knightMoves = knight.PossibleMoves(pieces);

    ASSERT_EQ(knightMoves.size(), 2);
}

TEST(KNIGHT, Jump)
{
    uint8_t x = 0;
    uint8_t y = 0;

    Knight knight(x, y, PieceColor::WHITE);
    Pawn pawn(x, y + 1, PieceColor::WHITE);
    Pawn pawn1(x + 1, y + 1, PieceColor::WHITE);
    Pawn pawn2(x + 2, y + 1, PieceColor::WHITE);
    std::vector<BasePiece*> pieces;
    pieces.push_back(&knight);
    pieces.push_back(&pawn);
    pieces.push_back(&pawn1);
    pieces.push_back(&pawn2);

    auto knightMoves = knight.PossibleMoves(pieces);

    ASSERT_EQ(knightMoves.size(), 1);
}