#include <gtest/gtest.h>
#include "ChessPiece.h"

TEST(CHESSPIECE, Notation)
{
    ChessPiece whitePiece(ChessPieceType::KING | ChessPieceColor::WHITE, ChessPiecePos(0,0));
    ChessPiece blackPiece(ChessPieceType::PAWN | ChessPieceColor::BLACK, ChessPiecePos(0,0));

    ASSERT_EQ(whitePiece.GetNotation(), 'K');
    ASSERT_TRUE(whitePiece.IsWhite());

    ASSERT_EQ(blackPiece.GetNotation(), 'p');
    ASSERT_FALSE(blackPiece.IsWhite());
}