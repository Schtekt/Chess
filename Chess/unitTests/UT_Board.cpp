#include <gtest/gtest.h>
#include "Board.h"

TEST(BOARD, TurnSwitchAfterWhite)
{
    // Use default setup
    ChessBoard board;

    // Make sure that white always starts
    EXPECT_EQ(board.GetColorTurn(), PieceColor::WHITE);

    // Move leftmost white pawn one step forward
    EXPECT_TRUE(board.PerformMove(Move(PiecePos(0,1), PiecePos(0,2))));

    EXPECT_EQ(board.GetColorTurn(), PieceColor::BLACK);
}

TEST(BOARD, TurnSwitchAfterBlack)
{
    // Use default setup
    ChessBoard board;

    // Perform move with white
    EXPECT_TRUE(board.PerformMove(Move(PiecePos(0,1), PiecePos(0,2))));

    // Verify that it is now blacks turn
    EXPECT_EQ(board.GetColorTurn(), PieceColor::BLACK);

    // Perfrom a mirrored move
    EXPECT_TRUE(board.PerformMove(Move(PiecePos(0, BOARDLENGTH - 2), PiecePos(0, BOARDLENGTH - 3))));

    // Verify that it is now Whites turn again
    EXPECT_EQ(board.GetColorTurn(), PieceColor::WHITE);
}

TEST(BOARD, BasicHistory)
{
    // Use default setup
    ChessBoard board;
    // Move leftmost white pawn two steps forward
    Move moveToPerform(PiecePos(0,1), PiecePos(0,3));

    EXPECT_EQ(board.GetHistory().size(), 0);
    EXPECT_TRUE(board.PerformMove(moveToPerform));

    auto histAfterMove = board.GetHistory();

    EXPECT_EQ(histAfterMove.size(), 1);
    EXPECT_EQ(histAfterMove[0], moveToPerform);
}

TEST(BOARD, DenyMove)
{
    // Use default setup
    ChessBoard board;

    // Move leftmost black pawn one step forward
    Move moveToPerform(PiecePos(0, BOARDLENGTH - 2), PiecePos(0, BOARDLENGTH - 3));

    EXPECT_EQ(board.GetHistory().size(), 0);
    EXPECT_FALSE(board.PerformMove(moveToPerform));
    EXPECT_EQ(board.GetHistory().size(), 0);
}