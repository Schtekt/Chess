#include "ChessBoard.h"
#include "ChessPiece.h"
/*
      A|B|C|D|E|F|G|H
    8|_|_|_|_|_|_|_|_|8
    7|_|_|_|_|_|_|_|_|7
    6|_|_|_|_|_|_|_|_|6
    5|_|_|_|_|_|_|_|_|5
    4|_|_|_|_|_|_|_|_|4
    3|_|_|_|_|_|_|_|_|3
    2|_|_|_|_|_|_|_|_|2
    1|_|_|_|_|_|_|_|_|1
      A|B|C|D|E|F|G|H
*/

ChessBoard::ChessBoard()
{
    for(size_t i = 0; i < m_boardData.size(); i++)
    {
        m_boardData[i] = 0;
    }

    // Use default chess setup
    addPiece('A', 7, ChessPieceColor::BLACK | ChessPieceType::PAWN);
    addPiece('B', 7, ChessPieceColor::BLACK | ChessPieceType::PAWN);
    addPiece('C', 7, ChessPieceColor::BLACK | ChessPieceType::PAWN);
    addPiece('D', 7, ChessPieceColor::BLACK | ChessPieceType::PAWN);
    addPiece('E', 7, ChessPieceColor::BLACK | ChessPieceType::PAWN);
    addPiece('F', 7, ChessPieceColor::BLACK | ChessPieceType::PAWN);
    addPiece('G', 7, ChessPieceColor::BLACK | ChessPieceType::PAWN);
    addPiece('H', 7, ChessPieceColor::BLACK | ChessPieceType::PAWN);

    addPiece('A', 8, ChessPieceColor::BLACK | ChessPieceType::ROOK);
    addPiece('B', 8, ChessPieceColor::BLACK | ChessPieceType::KNIGHT);
    addPiece('C', 8, ChessPieceColor::BLACK | ChessPieceType::BISHOP);
    addPiece('D', 8, ChessPieceColor::BLACK | ChessPieceType::QUEEN);
    addPiece('E', 8, ChessPieceColor::BLACK | ChessPieceType::KING);
    addPiece('F', 8, ChessPieceColor::BLACK | ChessPieceType::BISHOP);
    addPiece('G', 8, ChessPieceColor::BLACK | ChessPieceType::KNIGHT);
    addPiece('H', 8, ChessPieceColor::BLACK | ChessPieceType::ROOK);

    addPiece('A', 2, ChessPieceColor::WHITE | ChessPieceType::PAWN);
    addPiece('B', 2, ChessPieceColor::WHITE | ChessPieceType::PAWN);
    addPiece('C', 2, ChessPieceColor::WHITE | ChessPieceType::PAWN);
    addPiece('D', 2, ChessPieceColor::WHITE | ChessPieceType::PAWN);
    addPiece('E', 2, ChessPieceColor::WHITE | ChessPieceType::PAWN);
    addPiece('F', 2, ChessPieceColor::WHITE | ChessPieceType::PAWN);
    addPiece('G', 2, ChessPieceColor::WHITE | ChessPieceType::PAWN);
    addPiece('H', 2, ChessPieceColor::WHITE | ChessPieceType::PAWN);

    addPiece('A', 1, ChessPieceColor::WHITE | ChessPieceType::ROOK);
    addPiece('B', 1, ChessPieceColor::WHITE | ChessPieceType::KNIGHT);
    addPiece('C', 1, ChessPieceColor::WHITE | ChessPieceType::BISHOP);
    addPiece('D', 1, ChessPieceColor::WHITE | ChessPieceType::QUEEN);
    addPiece('E', 1, ChessPieceColor::WHITE | ChessPieceType::KING);
    addPiece('F', 1, ChessPieceColor::WHITE | ChessPieceType::BISHOP);
    addPiece('G', 1, ChessPieceColor::WHITE | ChessPieceType::KNIGHT);
    addPiece('H', 1, ChessPieceColor::WHITE | ChessPieceType::ROOK);
}

std::string ChessBoard::PrintBoard() const
{
    std::string board;

    for(size_t i = m_boardData.size(); i > 0 ; i--)
    {
        uint8_t flags = m_boardData[i - 1];
        // Remove the color of the flag
        uint8_t pieceType = flags & ~ChessPieceColor::BLACK;

        if(i % 8 == 0 && i != m_boardData.size())
        {
            board += '\n';
        }

        switch(pieceType)
        {
            case ChessPieceType::KING:
                board += 'K';
            break;
            case ChessPieceType::QUEEN:
                board += 'Q';
            break;
            case ChessPieceType::BISHOP:
                board += 'B';
            break;
            case ChessPieceType::KNIGHT:
                board += 'N';
            break;
            case ChessPieceType::ROOK:
                board += 'R';
            break;
            case ChessPieceType::PAWN:
                board += 'p';
            break;
            default:
                board += ' ';
        }
    }
    return board;
}

bool ChessBoard::addPiece(uint8_t x, uint8_t y, uint8_t flags)
{
    uint8_t& piece = m_boardData[x - 'A' + 8 * (y - 1)];
    if(piece != 0)
    {
        return false;
    }

    piece = flags;
    return true;
}