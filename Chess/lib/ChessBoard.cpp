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

ChessBoard::ChessBoard(bool isWhiteTurn):
m_boardData({0}),
m_whiteTurn(isWhiteTurn)
{
}

uint8_t ChessBoard::GetNrOfPossibleMoves(uint8_t x, uint8_t y) const
{
    uint8_t count = 0;
    auto possibleMoves = GetPossibleMoves(x, y);
    for(bool move : possibleMoves)
    {
        count += move;
    }
    return count;
}

std::array<bool, 64> ChessBoard::GetPossibleMoves(uint8_t x, uint8_t y) const
{
    return getPossibleMoves(m_boardData, x, y);
}

std::array<bool, 64> ChessBoard::getPossibleMoves(const std::array<uint8_t, 64>& board, uint8_t x, uint8_t y, bool checkForCheck) const
{
    size_t pieceIndex = convertChessCoordinateToIndex(x, y);
    ChessPiece piece(board[pieceIndex]);
    ChessPieceType pieceType = piece.GetType();
    ChessPieceColor pieceColor = piece.GetColor();
    if(pieceType == ChessPieceType::NONE)
    {
        return {0};
    }

    std::array<bool, 64> possibleMoves = getSpecificPiecePossibleMoves(board, pieceType, x, y);
    if(checkForCheck)
    {
        for(uint8_t y = 1; y <= 8; y++)
        {
            for(uint8_t x = 'A'; x <= 'H'; x++)
            {
                size_t possibleMoveIndex = convertChessCoordinateToIndex(x,y);
                if(possibleMoves[possibleMoveIndex])
                {
                    std::array<uint8_t, 64> possibleBoard = m_boardData;
                    possibleBoard[pieceIndex] = 0;
                    possibleBoard[possibleMoveIndex] = piece.GetFlag();

                    if(colorInCheck(pieceColor, possibleBoard))
                    {
                        possibleMoves[possibleMoveIndex] = false;
                    }
                }
            }
        }
    }

    return possibleMoves;
}

bool ChessBoard::MakeMove(uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end)
{
    if((m_boardData[convertChessCoordinateToIndex(x_start, y_start)] & ChessPieceColor::BLACK) == m_whiteTurn * 8)
    {
        return false;
    }

    auto possibleMoves = GetPossibleMoves(x_start, y_start);

    size_t startCoordinate = x_start - 'A' + 8 * (y_start - 1);
    size_t endCoordinate = x_end - 'A' + 8 * (y_end - 1);
    if(possibleMoves[endCoordinate])
    {
        m_boardData[endCoordinate] = m_boardData[startCoordinate];
        m_boardData[startCoordinate] = 0;
        m_whiteTurn = !m_whiteTurn;
        return true;
    }
    else 
    {
        return false;
    }
}

std::string ChessBoard::PrintBoard() const
{
    std::string board;
    // Go by coordinates instead of index!
    for(uint8_t y = 8; y > 0; y--)
    {
        for(uint8_t x = 'A'; x <= 'H'; x++)
        {
            size_t index = convertChessCoordinateToIndex(x,y);
            uint8_t flags = m_boardData[index];
            uint8_t pieceType = flags & ~ChessPieceColor::BLACK;
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
        board += '\n';
    }

    return board;
}

bool ChessBoard::AddPiece(uint8_t x, uint8_t y, uint8_t flags)
{
    uint8_t& piece = m_boardData[convertChessCoordinateToIndex(x, y)];
    if(piece != 0)
    {
        return false;
    }

    piece = flags;
    return true;
}

size_t ChessBoard::convertChessCoordinateToIndex(uint8_t x, uint8_t y) const
{
    return x - 'A' + 8 * (y - 1);
}

bool ChessBoard::spotIsEligible(uint8_t sourceFlag, uint8_t targetFlag) const
{
    return targetFlag == ChessPieceType::NONE || 
           (sourceFlag & ChessPieceColor::BLACK) != (targetFlag & ChessPieceColor::BLACK);
}

bool ChessBoard::colorInCheck(ChessPieceColor color, std::array<uint8_t, 64> boardData) const
{
    // Find the king
    uint8_t king_x = 0;
    uint8_t king_y = 0;

    for(uint8_t x = 'A'; x <= 'H'; x++)
    {
        for(uint8_t y = 1; y <= 8; y++)
        {
            size_t boardPosIndex = convertChessCoordinateToIndex(x, y);
            if((boardData[boardPosIndex] & ChessPieceColor::BLACK) == (color & ChessPieceColor::BLACK)
                && (boardData[boardPosIndex] & ChessPieceType::KING))
            {
                king_x = x;
                king_y = y;
            }
        }
    }

    if(king_x == 0 || king_y == 0)
    {
        // No king of the specified color found
        return false;
    }

    for(uint8_t x = 'A'; x <= 'H'; x++)
    {
        for(uint8_t y = 1; y <= 8; y++)
        {
            size_t boardPosIndex = convertChessCoordinateToIndex(x, y);
            if(boardData[boardPosIndex] == ChessPieceType::NONE)
            {
                continue;
            }

            if((boardData[boardPosIndex] & ChessPieceColor::BLACK) == (color & ChessPieceColor::BLACK))
            {
                continue;
            }

            auto possibleMoves = getPossibleMoves(boardData, x, y, false);
            if(possibleMoves[convertChessCoordinateToIndex(king_x, king_y)])
            {
                return true;
            }
        }
    }

    return false;
}

std::array<bool, 64> ChessBoard::getSpecificPiecePossibleMoves(const std::array<uint8_t, 64>& board, ChessPieceType pieceType, uint8_t x, uint8_t y) const
{
    std::array<bool, 64> possibleMoves = {0};
    switch (pieceType)
    {
    case ChessPieceType::KING:
        possibleMoves = getPossibleKingMoves(board, x, y);
        break;
    case ChessPieceType::ROOK:
        possibleMoves = getPossibleRookMoves(board, x, y);
    default:
        // do nothing
        break;
    }
    return possibleMoves;
}

std::array<bool, 64> ChessBoard::getPossibleKingMoves(const std::array<uint8_t, 64>& board, uint8_t x, uint8_t y) const
{
    // King is allowed to move one step in any direction, so long as it remains on the board.
    // If a friendly piece occupies an eligible position, the king may not move there.
    // If a hostile piece occupies an eligible position, the king may capture it.
    // The king must not move into check

    std::array<bool, 64> possibleMoves = {0};
    size_t currentIndex = convertChessCoordinateToIndex(x, y);
    if(x > 'A')
    {
        size_t possibleIndex = convertChessCoordinateToIndex(x - 1, y);
        if(spotIsEligible(board[currentIndex], board[possibleIndex]))
        {
            possibleMoves[possibleIndex] = true;
        }
    }

    if(x < 'H')
    {
        size_t possibleIndex = convertChessCoordinateToIndex(x + 1, y);
        if(spotIsEligible(board[currentIndex], board[possibleIndex]))
        {
            possibleMoves[possibleIndex] = true;
        }
    }

    if(y > 1)
    {
        size_t possibleIndex = convertChessCoordinateToIndex(x, y - 1);
        if(spotIsEligible(board[currentIndex], board[possibleIndex]))
        {
            possibleMoves[possibleIndex] = true;
        }
    }

    if(y < 8)
    {
        size_t possibleIndex = convertChessCoordinateToIndex(x, y + 1);
        if(spotIsEligible(board[currentIndex], board[possibleIndex]))
        {
            possibleMoves[possibleIndex] = true;
        }
    }

    if(x > 'A' && y > 1)
    {
        size_t possibleIndex = convertChessCoordinateToIndex(x - 1, y - 1);
        if(spotIsEligible(board[currentIndex], board[possibleIndex]))
        {
            possibleMoves[possibleIndex] = true;
        }
    }

    if(x > 'A' && y < 8)
    {
        size_t possibleIndex = convertChessCoordinateToIndex(x - 1, y + 1);
        if(spotIsEligible(board[currentIndex], board[possibleIndex]))
        {
            possibleMoves[possibleIndex] = true;
        }
    }

    if(x < 'H' && y > 1)
    {
        size_t possibleIndex = convertChessCoordinateToIndex(x + 1, y - 1);
        if(spotIsEligible(board[currentIndex], board[possibleIndex]))
        {
            possibleMoves[possibleIndex] = true;
        }
    }

    if(x < 'H' && y < 8)
    {
        size_t possibleIndex = convertChessCoordinateToIndex(x + 1, y + 1);
        if(spotIsEligible(board[currentIndex], board[possibleIndex]))
        {
            possibleMoves[possibleIndex] = true;
        }
    }

    return possibleMoves;
}

std::array<bool, 64> ChessBoard::getPossibleRookMoves(const std::array<uint8_t, 64>& board, uint8_t x, uint8_t y) const
{
    std::array<bool, 64> possibleMoves = {0};
    size_t currentIndex = convertChessCoordinateToIndex(x, y);
    uint8_t sourceFlag = board[currentIndex];

    auto spotIsNotOccupied = [this, sourceFlag, board, &possibleMoves](uint8_t x, uint8_t y)
    {
        size_t targetIndex = convertChessCoordinateToIndex(x, y);

        if(spotIsEligible(sourceFlag, board[targetIndex]))
        {
            possibleMoves[targetIndex] = true;
        }
        else
        {
            // The rook may not move past friendly pieces.
            return false;
        }

        if(board[targetIndex] != 0)
        {
            // Since the spot is elligible, but not empty, it must be occupied by an enemy piece.
            // The rook may capture this piece, but may not move past it.
            return false;
        }

        return true;
    };

    // Up
    for(uint8_t targetY = y + 1; targetY <= 8; targetY++)
    {
        if(!spotIsNotOccupied(x, targetY))
        {
            break;
        }
    }

    // Down
    for(uint8_t targetY = y - 1; targetY > 0; targetY--)
    {
        if(!spotIsNotOccupied(x, targetY))
        {
            break;
        }
    }

    // Right
    for(uint8_t targetX = x + 1; targetX <= 'H'; targetX++)
    {
        if(!spotIsNotOccupied(targetX, y))
        {
            break;
        }
    }

    // Left
    for(uint8_t targetX = x - 1; targetX >= 'A'; targetX--)
    {
        if(!spotIsNotOccupied(targetX, y))
        {
            break;
        }
    }

    return possibleMoves;
}