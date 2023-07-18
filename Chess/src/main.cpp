#include <iostream>
#include "Board.h"
int main()
{
    King king(0,0,PieceColor::WHITE);
    std::vector<BasePiece*> vec;
    vec.push_back(&king);
    auto moves = king.PossibleMoves(vec);

    for(auto move : moves)
    {
        std::cout << move.chessPos() + "\n";
    }
}