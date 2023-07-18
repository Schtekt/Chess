#include <gtest/gtest.h>
#include "Pieces/BasePiece.h"

TEST(PAWN, MoveForward)
{
    uint8_t whiteX = 0;
    uint8_t whiteY = 4;

    uint8_t blackX = 5;
    uint8_t blackY = 5;

    Pawn pawnWhite(whiteX, whiteY, PieceColor::WHITE);
    Pawn pawnBlack(blackX, blackY, PieceColor::BLACK);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&pawnWhite);
    pieces.push_back(&pawnBlack);

    auto whiteMoves = pawnWhite.PossibleMoves(pieces);
    auto blackMoves = pawnBlack.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 1);
    ASSERT_EQ(whiteMoves.front().x, whiteX);
    ASSERT_EQ(whiteMoves.front().y, whiteY + 1);

    ASSERT_EQ(blackMoves.size(), 1);
    ASSERT_EQ(blackMoves.front().x, blackX);
    ASSERT_EQ(blackMoves.front().y, blackY - 1);
}

TEST(PAWN, blockedMove)
{
    uint8_t whiteX = 0;
    uint8_t whiteY = 1;

    uint8_t blackX = 0;
    uint8_t blackY = 2;

    Pawn pawnWhite(whiteX, whiteY, PieceColor::WHITE);
    Pawn pawnBlack(blackX, blackY, PieceColor::BLACK);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&pawnWhite);
    pieces.push_back(&pawnBlack);

    auto whiteMoves = pawnWhite.PossibleMoves(pieces);
    auto blackMoves = pawnBlack.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 0);
    ASSERT_EQ(blackMoves.size(), 0);
}

TEST(PAWN, Attack)
{
    uint8_t whiteX = 0;
    uint8_t whiteY = 4;

    uint8_t blackX = 1;
    uint8_t blackY = 5;

    Pawn pawnWhite(whiteX, whiteY, PieceColor::WHITE);
    Pawn pawnBlack(blackX, blackY, PieceColor::BLACK);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&pawnWhite);
    pieces.push_back(&pawnBlack);

    auto whiteMoves = pawnWhite.PossibleMoves(pieces);
    auto blackMoves = pawnBlack.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 2);
    bool whiteMayAttack = false;
    for (auto move : whiteMoves)
    {
        if (move.x == blackX && move.y == blackY)
        {
            whiteMayAttack = true;
            break;
        }
    }

    bool blackMayAttack = false;
    ASSERT_EQ(blackMoves.size(), 2);
    for (auto move : blackMoves)
    {
        if (move.x == whiteX && move.y == whiteY)
        {
            blackMayAttack = true;
            break;
        }
    }

    ASSERT_TRUE(whiteMayAttack && blackMayAttack);
}

TEST(PAWN, DoNotAttackFriendly)
{
    uint8_t attackerX = 0;
    uint8_t attackerY = 4;

    uint8_t friendlyX = 1;
    uint8_t friendlyY = 5;

    Pawn pawnAttacker(attackerX, attackerY, PieceColor::WHITE);
    Pawn pawnFriendly(friendlyX, friendlyY, PieceColor::WHITE);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&pawnAttacker);
    pieces.push_back(&pawnFriendly);

    auto attackerMoves = pawnAttacker.PossibleMoves(pieces);

    ASSERT_EQ(attackerMoves.size(), 1);
    bool whiteMayAttack = false;
    for (auto move : attackerMoves)
    {
        if (move.x == friendlyX && move.y == friendlyY)
        {
            whiteMayAttack = true;
            break;
        }
    }

    ASSERT_FALSE(whiteMayAttack);
}

TEST(PAWN, FirstMoveDouble)
{
    uint8_t whiteX = 0;
    uint8_t whiteY = 1;

    uint8_t blackX = 1;
    uint8_t blackY = 6;

    Pawn pawnWhite(whiteX, whiteY, PieceColor::WHITE);
    Pawn pawnBlack(blackX, blackY, PieceColor::BLACK);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&pawnWhite);
    pieces.push_back(&pawnBlack);

    auto whiteMoves = pawnWhite.PossibleMoves(pieces);
    auto blackMoves = pawnBlack.PossibleMoves(pieces);

    ASSERT_EQ(whiteMoves.size(), 2);
    bool whiteMayMoveDouble = false;
    for (auto move : whiteMoves)
    {
        if (move.x == whiteX && move.y == whiteY + 2)
        {
            whiteMayMoveDouble = true;
            break;
        }
    }

    bool blackMayMoveDouble = false;
    ASSERT_EQ(blackMoves.size(), 2);
    for (auto move : blackMoves)
    {
        if (move.x == blackX && move.y == blackY - 2)
        {
            blackMayMoveDouble = true;
            break;
        }
    }

    ASSERT_TRUE(whiteMayMoveDouble && blackMayMoveDouble);
}

TEST(PAWN, FirstMoveDoubleNotAllowed)
{
    uint8_t whiteX = 0;
    uint8_t whiteY = 1;

    uint8_t blackX = 0;
    uint8_t blackY = 3;

    Pawn pawnWhite(whiteX, whiteY, PieceColor::WHITE);
    Pawn pawnBlack(blackX, blackY, PieceColor::BLACK);

    std::vector<BasePiece*> pieces;
    pieces.push_back(&pawnWhite);
    pieces.push_back(&pawnBlack);

    auto whiteMoves = pawnWhite.PossibleMoves(pieces);
    ASSERT_EQ(whiteMoves.size(), 1);
    ASSERT_EQ(whiteMoves.front().x, whiteX);
    ASSERT_EQ(whiteMoves.front().y, whiteY + 1);
}