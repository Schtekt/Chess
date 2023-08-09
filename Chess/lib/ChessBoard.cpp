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
    size_t pieceIndex = convertChessCoordinateToIndex(x,y);
    return getPossibleMoves(m_boardData, pieceIndex);
}

std::array<bool, 64> ChessBoard::getPossibleMoves(const std::array<uint8_t, 64>& board, size_t pieceIndex, bool checkForCheck) const
{
    ChessPiece piece(board[pieceIndex]);
    ChessPieceType pieceType = piece.GetType();
    ChessPieceColor pieceColor = piece.GetColor();
    if(pieceType == ChessPieceType::NONE)
    {
        return {0};
    }

    // For easier human calcs, the x and y coordinates are used in the specific piece calculations.
    auto coordinate = convertIndexToChessCoordinate(pieceIndex);
    std::array<bool, 64> possibleMoves = getSpecificPiecePossibleMoves(board, pieceType, std::get<0>(coordinate), std::get<1>(coordinate));
    
    // Pieces may not move so that they place their color into check, as this would result in an instant loss.
    if(checkForCheck)
    {
        for(size_t i = 0; i < possibleMoves.size(); i++)
        {
            if(possibleMoves[i])
            {
                std::array<uint8_t, 64> possibleBoard = m_boardData;
                possibleBoard[pieceIndex] = 0;
                possibleBoard[i] = piece.GetFlag();

                if(colorInCheck(pieceColor, possibleBoard))
                {
                    possibleMoves[i] = false;
                }
            }
        }
    }

    return possibleMoves;
}

bool ChessBoard::MakeMove(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd)
{
    ChessPiece piece(m_boardData[convertChessCoordinateToIndex(xStart, yStart)]);
    if(piece.GetColor() == m_whiteTurn * ChessPieceColor::BLACK)
    {
        return false;
    }

    auto possibleMoves = GetPossibleMoves(xStart, yStart);

    size_t startIndex = xStart - 'A' + 8 * (yStart - 1);
    size_t endIndex = xEnd - 'A' + 8 * (yEnd - 1);
    if(possibleMoves[endIndex])
    {
        // Special case for en passant capture.
        if(piece.GetType() == ChessPieceType::PAWN && xStart != xEnd && m_boardData[endIndex] == 0)
        {
            size_t enPassantCaptureIndex = convertChessCoordinateToIndex(xEnd, yStart);
            m_boardData[enPassantCaptureIndex] = 0;
        }

        m_boardData[endIndex] = m_boardData[startIndex];
        m_boardData[startIndex] = 0;


        m_whiteTurn = !m_whiteTurn;
        m_vecHistory.emplace_back(xStart, yStart, xEnd, yEnd);
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

std::tuple<uint8_t, uint8_t> ChessBoard::convertIndexToChessCoordinate(size_t index) const
{
    return std::make_tuple<uint8_t, uint8_t>(static_cast<uint8_t>(index % 8 + 'A'), static_cast<uint8_t>(index / 8 + 1));
}

bool ChessBoard::coordinatesWithinBoard(uint8_t x, uint8_t y) const
{
    return x <= 'H' && x >= 'A' && y >= 1 && y <= 8;
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


    for(size_t i = 0; i < boardData.size(); i++)
    {

        ChessPiece piece(boardData[i]);
        if(piece.GetColor() == color && piece.GetType() == ChessPieceType::KING)
        {
            auto res = convertIndexToChessCoordinate(i);
            king_x = std::get<0>(res);
            king_y = std::get<1>(res);
            // No need to check for multiple kings
            break;
        }
    }

    if(king_x == 0 || king_y == 0)
    {
        // No king of the specified color found
        return false;
    }

    for(uint8_t i = 0; i < boardData.size(); i++)
    {
        ChessPiece piece(boardData[i]);
        if(piece.GetType() == ChessPieceType::NONE)
        {
            continue;
        }

        if(piece.GetColor() == color)
        {
            continue;
        }

        auto possibleMoves = getPossibleMoves(boardData, i, false);
        if(possibleMoves[convertChessCoordinateToIndex(king_x, king_y)])
        {
            return true;
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
        break;
    case ChessPieceType::BISHOP:
        possibleMoves = getPossibleBishopMoves(board, x, y);
        break;
    case ChessPieceType::KNIGHT:
        possibleMoves = getPossibleKnightMoves(board, x, y);
        break;
    case ChessPieceType::PAWN:
        possibleMoves = getPossiblePawnMoves(board, x, y);
        break;
    default:
        // do nothing
        break;
    }
    return possibleMoves;
}

std::array<bool, 64> ChessBoard::getPossibleKingMoves(const std::array<uint8_t, 64>& board, uint8_t x, uint8_t y) const
{
    // King is allowed to move one step in any direction, so long as it remains on the board.
    // If a friendly piece occupies an eligible position, the King may not move there.
    // If a hostile piece occupies an eligible position, the King may capture it.

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
    // Rook is allowed to move any number of steps horizontally or vertically.
    // If a friendly piece occupies an eligible position, the Rook may not move there, or past it.
    // If a hostile piece occupies an eligible position, the Rook may capture it, but not move past it.

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

std::array<bool, 64> ChessBoard::getPossibleBishopMoves(const std::array<uint8_t, 64>& board, uint8_t x, uint8_t y) const
{
    // Bishop is allowed to move any number of steps in any diagonal direction.
    // If a friendly piece occupies an eligible position, the Bishop may not move there, or past it.
    // If a hostile piece occupies an eligible position, the Bishop may capture it, but not move past it.
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
            // The bishop may not move past friendly pieces.
            return false;
        }

        if(board[targetIndex] != 0)
        {
            // Since the spot is elligible, but not empty, it must be occupied by an enemy piece.
            // The bishop may capture this piece, but may not move past it.
            return false;
        }

        return true;
    };

    // Up right
    for(uint8_t count = 1; x + count <= 'H' && y + count <= 8; count++)
    {
        if(!spotIsNotOccupied(x + count, y + count))
        {
            break;
        }
    }

    // Up left
    for(uint8_t count = 1; x - count >= 'A' && y + count <= 8; count++)
    {
        if(!spotIsNotOccupied(x - count, y + count))
        {
            break;
        }
    }

    // Down right
    for(uint8_t count = 1; x + count <= 'H' && y - count > 0; count++)
    {
        if(!spotIsNotOccupied(x + count, y - count))
        {
            break;
        }
    }

    // Down left
    for(uint8_t count = 1; x - count >= 'A' && y - count > 0; count++)
    {
        if(!spotIsNotOccupied(x - count, y - count))
        {
            break;
        }
    }

    return possibleMoves;
}

std::array<bool, 64> ChessBoard::getPossibleKnightMoves(const std::array<uint8_t, 64>& board, uint8_t x, uint8_t y) const
{
    // Knight is allowed to move in a 'L' pattern, that is the knight may move two steps in a direction that is horisontal or vertical
    // and then move one more step in a 90 degree angle (e.g. the knoght may move in a horisontal direction for the first two steps
    // but must then move oine step vertically).
    // If a friendly piece occupies an eligible position, the Knight may not move there.
    // If a hostile piece occupies an eligible position, the Knight may capture it.
    // To clarify, the knight is not stopped by any pieces that may block the path to a position.
    std::array<bool, 64> possibleMoves = {0};
    size_t currentIndex = convertChessCoordinateToIndex(x, y);

    std::array<std::tuple<uint8_t, uint8_t>, 8> possibleKnightMoves;

    possibleKnightMoves[0] = std::make_tuple<uint8_t, uint8_t>(x+1, y+2);
    possibleKnightMoves[1] = std::make_tuple<uint8_t, uint8_t>(x-1, y+2);
    possibleKnightMoves[2] = std::make_tuple<uint8_t, uint8_t>(x+1, y-2);
    possibleKnightMoves[3] = std::make_tuple<uint8_t, uint8_t>(x-1, y-2);
    possibleKnightMoves[4] = std::make_tuple<uint8_t, uint8_t>(x+2, y+1);
    possibleKnightMoves[5] = std::make_tuple<uint8_t, uint8_t>(x+2, y-1);
    possibleKnightMoves[6] = std::make_tuple<uint8_t, uint8_t>(x-2, y+1);
    possibleKnightMoves[7] = std::make_tuple<uint8_t, uint8_t>(x-2, y-1);

    for(auto move : possibleKnightMoves)
    {
        uint8_t possibleX = std::get<0>(move);
        uint8_t possibleY = std::get<1>(move);
        if(coordinatesWithinBoard(possibleX, possibleY))
        {
            size_t targetIndex = convertChessCoordinateToIndex(possibleX, possibleY);
            possibleMoves[targetIndex] = spotIsEligible(board[currentIndex], board[targetIndex]);
        }
    }
    
    return possibleMoves;
}

std::array<bool, 64> ChessBoard::getPossiblePawnMoves(const std::array<uint8_t, 64>& board, uint8_t x, uint8_t y) const
{
    // Pawn is only allowed to move "forward" (upwards for white and downwards for black), one step at a time.
    // If a friendly or hostile piece blocks the spot in front of the pawn, it may not move there.
    // If a hostile piece is placed one step diagonally in front of the pawn, it may capture that piece. 
    // For example, if a white pawn exist on D5, it could potentially capture a piece on C6 or E6).
    
    // Special rules!
    // If a pawn is making its first move, and only then, it may move up to two steps instead of only one in the forward direction, 
    // however, none of the two spots may be occupied in that case.
    // If a pawn reaches the end of the board, it is promoted into any one of the other chess piece types, except for the king piece.
    // If a pawn uses its first move to advance two steps and lands adjacent to a hostile pawn, then the hostile pawn may capture the 
    // pawn that just made the two step advance (en passant). This may only be done on the turn immediatly after the two step advance.

    std::array<bool, 64> possibleMoves = {0};
    size_t currentIndex = convertChessCoordinateToIndex(x, y);
    ChessPiece pawnPiece(board[currentIndex]);
    bool isBlack = pawnPiece.GetColor() == ChessPieceColor::BLACK;
    int8_t forwardDir = 1 - 2 * isBlack;

    if(!coordinatesWithinBoard(x,y+forwardDir))
    {
        // Something has gone wrong...
        return possibleMoves;
    }

    size_t targetIndex = convertChessCoordinateToIndex(x, y+forwardDir);
    bool pawnMayMoveForward = spotIsEligible(board[currentIndex], board[targetIndex]);

    possibleMoves[targetIndex] = pawnMayMoveForward;

    // Check possible captures
    auto pawnMayCapture = [this, currentIndex, board, &possibleMoves](uint8_t x, uint8_t y)
    {
        if(coordinatesWithinBoard(x, y))
        {
            size_t captureIndex = convertChessCoordinateToIndex(x, y);
            bool notOccupiedByFriendly = spotIsEligible(board[currentIndex], board[captureIndex]);
            possibleMoves[captureIndex] = notOccupiedByFriendly && board[captureIndex] != ChessPieceType::NONE;
        }
    };

    pawnMayCapture(x-1, y+forwardDir);
    pawnMayCapture(x+1, y+forwardDir);

    // Special case, double step
    uint8_t doubleStepOrigin = 2 + 5 * isBlack;
    bool pieceOnCorrectPosition = y == doubleStepOrigin;

    if(pawnMayMoveForward && pieceOnCorrectPosition)
    {
        // Double step is allowed
        uint8_t yDoubleStep = y + 2 * forwardDir;

        targetIndex = convertChessCoordinateToIndex(x, yDoubleStep);
        possibleMoves[targetIndex] = board[targetIndex] == ChessPieceType::NONE;
    }

    // Special case, en passant
    auto pawnMayEnPassant = [this, pawnPiece, board, forwardDir, &possibleMoves](uint8_t x, uint8_t y, const std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>& lastMove)
    {
        if(coordinatesWithinBoard(x, y))
        {
            size_t hostilePieceIndex = convertChessCoordinateToIndex(x, y);
            ChessPiece hostilePiece(board[hostilePieceIndex]);

            if(hostilePiece.GetType() == ChessPieceType::PAWN && 
               hostilePiece.GetColor() != pawnPiece.GetColor())
            {
                // Check if hostile piece made the latest move and if that move was a double step
                uint8_t xStart = std::get<0>(lastMove);
                uint8_t yStart = std::get<1>(lastMove);
                uint8_t xEnd = std::get<2>(lastMove);
                uint8_t yEnd = std::get<3>(lastMove);

                if(xEnd == x && yEnd == y && xEnd == xStart && yStart == yEnd + forwardDir * 2)
                {
                    // As a pawn may not perform the double step, in case there is a piece blocking, assume that there is no piece blocking.
                    possibleMoves[convertChessCoordinateToIndex(x, y + forwardDir)] = true;
                }
            }
        }
    };

    // If there is no history, it is not possible to perform en passant.
    if(m_vecHistory.size() != 0)
    {
        pawnMayEnPassant(x - 1, y, m_vecHistory.back());
        pawnMayEnPassant(x + 1, y, m_vecHistory.back());
    }

    return possibleMoves;
}