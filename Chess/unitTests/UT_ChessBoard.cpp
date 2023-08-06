#include <gtest/gtest.h>
#include "ChessPiece.h"
#include "ChessBoard.h"

TEST(CHESSBOARD, MoveKing)
{
    ChessBoard board(false);
    board.AddPiece('A', 1, ChessPieceColor::BLACK | ChessPieceType::KING);

    ASSERT_EQ(board.GetNrOfPossibleMoves('A', 1), 3);
    ASSERT_TRUE(board.MakeMove('A', 1, 'A', 2));
}

TEST(CHESSBOARD, MoveKingIllegal)
{
    ChessBoard board(false);
    board.AddPiece('A', 1, ChessPieceColor::BLACK | ChessPieceType::KING);

    ASSERT_FALSE(board.MakeMove('A', 1, 'A', 3));
}

TEST(CHESSBOARD, KingMayNotMoveIntoCheck)
{
    ChessBoard board(false);
    board.AddPiece('A', 1, ChessPieceColor::BLACK | ChessPieceType::KING);
    board.AddPiece('A', 3, ChessPieceColor::WHITE | ChessPieceType::KING);

    ASSERT_FALSE(board.MakeMove('A', 1, 'A', 2));
    ASSERT_TRUE(board.MakeMove('A', 1, 'B', 1));
}

TEST(CHESSBOARD, MoveRook)
{
    ChessBoard board(true);
    board.AddPiece('A', 1, ChessPieceColor::WHITE | ChessPieceType::ROOK);
    ASSERT_EQ(board.GetNrOfPossibleMoves('A', 1), 14);
}


TEST(CHESSBOARD, TurnChange)
{
    ChessBoard board(false);
    board.AddPiece('A', 1, ChessPieceColor::BLACK | ChessPieceType::KING);
    board.AddPiece('A', 3, ChessPieceColor::WHITE | ChessPieceType::KING);

    ASSERT_TRUE(board.MakeMove('A', 1, 'B', 1));
    ASSERT_FALSE(board.MakeMove('B', 1, 'C', 1));
    ASSERT_FALSE(board.MakeMove('B', 1, 'A', 1));
    ASSERT_TRUE(board.MakeMove('A', 3, 'B', 3));
}
