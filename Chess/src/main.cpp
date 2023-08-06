#include <iostream>
#include "ChessBoard.h"
#include "ChessPiece.h"

int main()
{
    ChessBoard board;
    board.AddPiece('A', 7, ChessPieceColor::BLACK | ChessPieceType::PAWN);
    board.AddPiece('B', 7, ChessPieceColor::BLACK | ChessPieceType::PAWN);
    board.AddPiece('C', 7, ChessPieceColor::BLACK | ChessPieceType::PAWN);
    board.AddPiece('D', 7, ChessPieceColor::BLACK | ChessPieceType::PAWN);
    board.AddPiece('E', 7, ChessPieceColor::BLACK | ChessPieceType::PAWN);
    board.AddPiece('F', 7, ChessPieceColor::BLACK | ChessPieceType::PAWN);
    board.AddPiece('G', 7, ChessPieceColor::BLACK | ChessPieceType::PAWN);
    board.AddPiece('H', 7, ChessPieceColor::BLACK | ChessPieceType::PAWN);

    board.AddPiece('A', 8, ChessPieceColor::BLACK | ChessPieceType::ROOK);
    board.AddPiece('B', 8, ChessPieceColor::BLACK | ChessPieceType::KNIGHT);
    board.AddPiece('C', 8, ChessPieceColor::BLACK | ChessPieceType::BISHOP);
    board.AddPiece('D', 8, ChessPieceColor::BLACK | ChessPieceType::QUEEN);
    board.AddPiece('E', 8, ChessPieceColor::BLACK | ChessPieceType::KING);
    board.AddPiece('F', 8, ChessPieceColor::BLACK | ChessPieceType::BISHOP);
    board.AddPiece('G', 8, ChessPieceColor::BLACK | ChessPieceType::KNIGHT);
    board.AddPiece('H', 8, ChessPieceColor::BLACK | ChessPieceType::ROOK);

    board.AddPiece('A', 2, ChessPieceColor::WHITE | ChessPieceType::PAWN);
    board.AddPiece('B', 2, ChessPieceColor::WHITE | ChessPieceType::PAWN);
    board.AddPiece('C', 2, ChessPieceColor::WHITE | ChessPieceType::PAWN);
    board.AddPiece('D', 2, ChessPieceColor::WHITE | ChessPieceType::PAWN);
    board.AddPiece('E', 2, ChessPieceColor::WHITE | ChessPieceType::PAWN);
    board.AddPiece('F', 2, ChessPieceColor::WHITE | ChessPieceType::PAWN);
    board.AddPiece('G', 2, ChessPieceColor::WHITE | ChessPieceType::PAWN);
    board.AddPiece('H', 2, ChessPieceColor::WHITE | ChessPieceType::PAWN);

    board.AddPiece('A', 1, ChessPieceColor::WHITE | ChessPieceType::ROOK);
    board.AddPiece('B', 1, ChessPieceColor::WHITE | ChessPieceType::KNIGHT);
    board.AddPiece('C', 1, ChessPieceColor::WHITE | ChessPieceType::BISHOP);
    board.AddPiece('D', 1, ChessPieceColor::WHITE | ChessPieceType::QUEEN);
    board.AddPiece('E', 1, ChessPieceColor::WHITE | ChessPieceType::KING);
    board.AddPiece('F', 1, ChessPieceColor::WHITE | ChessPieceType::BISHOP);
    board.AddPiece('G', 1, ChessPieceColor::WHITE | ChessPieceType::KNIGHT);
    board.AddPiece('H', 1, ChessPieceColor::WHITE | ChessPieceType::ROOK);

    std::cout << board.PrintBoard() << '\n';
}