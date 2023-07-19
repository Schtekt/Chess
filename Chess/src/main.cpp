#include <iostream>
#include "Board.h"
int main()
{
    ChessBoard board;

    board.PerformMove(Move(PiecePos(0,1), PiecePos(0,3)));
    std::cout << board.GetBoard() << "\n";
}