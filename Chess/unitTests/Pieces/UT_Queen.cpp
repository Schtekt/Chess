#include <gtest/gtest.h>
#include "Pieces/BasePiece.h"

TEST(QUEEN, BasicMove)
{
    uint8_t x = 4;
    uint8_t y = 4;

    Queen queen(x, y, PieceColor::WHITE);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&queen);

    auto whiteMoves = queen.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 27);
}

TEST(QUEEN, CornerMove)
{
    uint8_t x = 0;
    uint8_t y = 0;

    Queen queen(x, y, PieceColor::WHITE);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&queen);

    auto whiteMoves = queen.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 21);
}

TEST(QUEEN, BlockedInCorner)
{
    uint8_t x = 0;
    uint8_t y = 0;

    Queen queen(x, y, PieceColor::WHITE);
    Pawn pawnDiagonal(x + 1, y + 1, PieceColor::WHITE);
    Pawn pawnVertical(x, y + 1, PieceColor::WHITE);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&queen);
    pieces.push_back(&pawnDiagonal);
    pieces.push_back(&pawnVertical);

    auto whiteMoves = queen.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 7);
}

TEST(QUEEN, AttackDiagonal)
{
    uint8_t x = 4;
    uint8_t y = 4;

    Queen whiteQueen(x, y, PieceColor::WHITE);
    Queen blackQueen(x - 2, y - 2, PieceColor::BLACK);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&whiteQueen);
    pieces.push_back(&blackQueen);

    auto whiteMoves = whiteQueen.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 25);
}

TEST(QUEEN, AttackHorisontal)
{
    uint8_t x = 4;
    uint8_t y = 4;

    Queen whiteQueen(x, y, PieceColor::WHITE);
    Queen blackQueen(x, y - 2, PieceColor::BLACK);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&whiteQueen);
    pieces.push_back(&blackQueen);

    auto whiteMoves = whiteQueen.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 25);
}