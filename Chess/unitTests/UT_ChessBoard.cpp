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

TEST(CHESSBOARD, MoveRookIllegal)
{
    ChessBoard board(false);
    board.AddPiece('A', 1, ChessPieceColor::BLACK | ChessPieceType::ROOK);

    ASSERT_FALSE(board.MakeMove('A', 1, 'B', 2));
}

TEST(CHESSBOARD, RookMayNotOpenForCheck)
{
    ChessBoard board(false);
    board.AddPiece('A', 1, ChessPieceColor::BLACK | ChessPieceType::KING);
    board.AddPiece('A', 2, ChessPieceColor::BLACK | ChessPieceType::ROOK);
    board.AddPiece('A', 7, ChessPieceColor::WHITE | ChessPieceType::ROOK);

    ASSERT_FALSE(board.MakeMove('A', 2, 'B', 2));
    ASSERT_TRUE(board.MakeMove('A', 2, 'A', 3));
}

TEST(CHESSBOARD, MoveBishop)
{
    ChessBoard board(true);
    board.AddPiece('D', 5, ChessPieceColor::WHITE | ChessPieceType::BISHOP);
    ASSERT_EQ(board.GetNrOfPossibleMoves('D', 5), 13);
}

TEST(CHESSBOARD, MoveBishopIllegal)
{
    ChessBoard board(false);
    board.AddPiece('A', 1, ChessPieceColor::BLACK | ChessPieceType::BISHOP);

    ASSERT_FALSE(board.MakeMove('A', 1, 'A', 2));
}

TEST(CHESSBOARD, BishopMayNotOpenForCheck)
{
    ChessBoard board(false);
    board.AddPiece('B', 1, ChessPieceColor::BLACK | ChessPieceType::KING);
    board.AddPiece('C', 2, ChessPieceColor::BLACK | ChessPieceType::BISHOP);
    board.AddPiece('E', 4, ChessPieceColor::WHITE | ChessPieceType::BISHOP);

    ASSERT_FALSE(board.MakeMove('C', 2, 'B', 3));
    ASSERT_TRUE(board.MakeMove('C', 2, 'D', 3));
}

TEST(CHESSBOARD, MoveKnight)
{
    ChessBoard board(true);
    board.AddPiece('D', 5, ChessPieceColor::WHITE | ChessPieceType::KNIGHT);
    ASSERT_EQ(board.GetNrOfPossibleMoves('D', 5), 8);
}

TEST(CHESSBOARD, MoveKnightIllegal)
{
    ChessBoard board(false);
    board.AddPiece('A', 1, ChessPieceColor::BLACK | ChessPieceType::KNIGHT);

    ASSERT_FALSE(board.MakeMove('A', 1, 'B', 1));
}

TEST(CHESSBOARD, KnightMustCaptureIfKingInCheck)
{
    ChessBoard board(false);
    board.AddPiece('A', 1, ChessPieceColor::BLACK | ChessPieceType::KING);
    board.AddPiece('B', 1, ChessPieceColor::BLACK | ChessPieceType::KNIGHT);
    board.AddPiece('A', 3, ChessPieceColor::WHITE | ChessPieceType::ROOK);

    ASSERT_FALSE(board.MakeMove('B', 1, 'C', 3));
    ASSERT_TRUE(board.MakeMove('B', 1, 'A', 3));
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
