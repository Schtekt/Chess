#include <gtest/gtest.h>
#include "ChessPiece.h"


TEST(CHESSPIECE, Color)
{
    ChessPiece plainBlack(ChessPieceColor::BLACK);
    ChessPiece kingBlack(ChessPieceColor::BLACK | ChessPieceType::KING);
    ChessPiece plainWhite(ChessPieceColor::WHITE);
    ChessPiece kingWhite(ChessPieceColor::WHITE | ChessPieceType::KING);

    ASSERT_EQ(plainBlack.GetColor(), ChessPieceColor::BLACK);
    ASSERT_EQ(kingBlack.GetColor(), ChessPieceColor::BLACK);
    ASSERT_EQ(plainWhite.GetColor(), ChessPieceColor::WHITE);
    ASSERT_EQ(kingWhite.GetColor(), ChessPieceColor::WHITE);
}


class ChessPieceTypeTestsFixture : public ::testing::TestWithParam<std::tuple<ChessPieceType, char>>
{
};

TEST_P(ChessPieceTypeTestsFixture, Type)
{
    auto param = GetParam();
    ChessPiece piece(std::get<0>(param) | ChessPieceColor::BLACK);
    ASSERT_EQ(piece.GetType(), std::get<0>(param));
}

TEST_P(ChessPieceTypeTestsFixture, Notation)
{
    auto param = GetParam();
    ChessPiece piece(std::get<0>(param) | ChessPieceColor::WHITE);
    ASSERT_EQ(piece.GetNotation(), std::get<1>(param));
}

TEST_P(ChessPieceTypeTestsFixture, Flag)
{
    auto param = GetParam();
    uint8_t expectedFlag = std::get<0>(param) | ChessPieceColor::BLACK;
    ChessPiece piece(expectedFlag);
    ASSERT_EQ(piece.GetFlag(), expectedFlag);
}

INSTANTIATE_TEST_SUITE_P(Notation, ChessPieceTypeTestsFixture,
                        ::testing::Values(std::make_tuple(ChessPieceType::KING, 'K'),
                                          std::make_tuple(ChessPieceType::QUEEN, 'Q'),
                                          std::make_tuple(ChessPieceType::BISHOP, 'B'),
                                          std::make_tuple(ChessPieceType::KNIGHT, 'N'),
                                          std::make_tuple(ChessPieceType::ROOK, 'R'),
                                          std::make_tuple(ChessPieceType::PAWN, 'p')));