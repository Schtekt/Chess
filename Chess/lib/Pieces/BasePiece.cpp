#include "BasePiece.h"

// King may move one space horizontally, vertically or diagonally,
// as long as the piece is not placed in check (and stays on the board)
std::vector<PiecePos> King::PossibleMoves(std::vector<BasePiece *> piecesOnBoard)
{
    std::vector<PiecePos> movablePositions;
    // TODO: Add check that king does not place himself in check...

    bool mayMoveLeft = m_pos.x > 0;
    bool mayMoveDown = m_pos.y > 0;
    bool mayMoveRight = m_pos.x < BOARDLENGTH - 1;
    bool mayMoveUp = m_pos.y < BOARDLENGTH - 1;

    if (mayMoveLeft)
    {
        movablePositions.emplace_back(m_pos.x - 1, m_pos.y);
    }

    if (mayMoveDown)
    {
        movablePositions.emplace_back(m_pos.x, m_pos.y - 1);
    }

    if (mayMoveRight)
    {
        movablePositions.emplace_back(m_pos.x + 1, m_pos.y);
    }

    if (mayMoveUp)
    {
        movablePositions.emplace_back(m_pos.x, m_pos.y + 1);
    }

    if (mayMoveLeft && mayMoveDown)
    {
        movablePositions.emplace_back(m_pos.x - 1, m_pos.y - 1);
    }

    if (mayMoveLeft && mayMoveUp)
    {
        movablePositions.emplace_back(m_pos.x - 1, m_pos.y + 1);
    }

    if (mayMoveRight && mayMoveDown)
    {
        movablePositions.emplace_back(m_pos.x + 1, m_pos.y - 1);
    }

    if (mayMoveRight && mayMoveUp)
    {
        movablePositions.emplace_back(m_pos.x + 1, m_pos.y + 1);
    }

    bool removeMove[8] = {false}; // king may at max make 8 moves, allocate mem on stack.
    unsigned int counter = 0;
    for(auto move: movablePositions)
    {
        for(auto piece: piecesOnBoard)
        {
            if(piece == this)
            {
                continue;
            }
            else if(piece->GetPosition() == move)
            {
                removeMove[counter] = true;
                break;
            }
        }
        counter++;
    }

    for(int i = counter - 1; i >= 0; i--)
    {
        if(removeMove[i])
        {
            movablePositions.erase(movablePositions.begin() + i);
        }
    }

    return movablePositions;
}

std::vector<PiecePos> Queen::PossibleMoves(std::vector<BasePiece*> piecesOnBoard)
{
    std::vector<PiecePos> movablePositions;

    uint8_t maxMovesDown = m_pos.y;
    uint8_t maxMovesUp = BOARDLENGTH - 1 - m_pos.y;
    uint8_t maxMovesLeft = m_pos.x;
    uint8_t maxMovesRight = BOARDLENGTH - 1 - m_pos.x;
    uint8_t maxMovesDownLeft = std::min(maxMovesDown, maxMovesLeft);
    uint8_t maxMovesUpLeft = std::min(maxMovesUp, maxMovesLeft);
    uint8_t maxMovesDownRight = std::min(maxMovesDown, maxMovesRight);
    uint8_t maxMovesUpRight = std::min(maxMovesUp, maxMovesRight);
    for(auto piece: piecesOnBoard)
    {
        if(piece == this)
        {
            continue;
        }

        bool mayNotCapture = m_color == piece->GetColor();

        PiecePos otherPiecePos = piece->GetPosition();

        if(otherPiecePos.x == m_pos.x)
        {
            if(otherPiecePos.y < m_pos.y && m_pos.y - otherPiecePos.y < maxMovesDown)
            {
                maxMovesDown = m_pos.y - otherPiecePos.y - 1 * mayNotCapture;
            }
            if(otherPiecePos.y > m_pos.y && otherPiecePos.y - m_pos.y < maxMovesUp)
            {
                maxMovesUp = otherPiecePos.y - m_pos.y - 1 * mayNotCapture;
            }
        }
        else if(otherPiecePos.y == m_pos.y)
        {
            if(otherPiecePos.x < m_pos.x && m_pos.x - otherPiecePos.x < maxMovesLeft)
            {
                maxMovesLeft = m_pos.x - otherPiecePos.x - 1 * mayNotCapture;
            }
            if(otherPiecePos.x > m_pos.x && otherPiecePos.x - m_pos.x < maxMovesRight)
            {
                maxMovesRight = otherPiecePos.x - m_pos.x - 1 * mayNotCapture;
            }
        }

        int8_t deltaRow = otherPiecePos.x - m_pos.x;
        int8_t deltaCol = otherPiecePos.y - m_pos.y;
        uint8_t absDeltaRow = abs(deltaRow);
        uint8_t absDeltaCol = abs(deltaCol);

        // Is on one of the diagonals...
        if(absDeltaRow == absDeltaCol)
        {
            uint8_t distance = std::min(absDeltaRow, absDeltaCol) - 1 * mayNotCapture;
            // Piece is on upper left side diagonal of this queen
            if(deltaRow < 0 && deltaCol > 0 && maxMovesUpLeft > distance)
            {
                maxMovesUpLeft = distance;
            }
            // Piece is on lower left side diagonal of this queen
            else if(deltaRow < 0 && deltaCol < 0 && maxMovesDownLeft > distance)
            {
                maxMovesDownLeft = distance;
            }
            else if(deltaRow > 0 && deltaCol > 0 && maxMovesUpRight > distance)
            {
                maxMovesUpRight = distance;
            }
            else if(deltaRow > 0 && deltaCol < 0 && maxMovesDownRight > distance)
            {
                maxMovesDownRight = distance;
            }
        }
    }

    for(uint8_t i = 0; i < maxMovesDown; i++)
    {
        movablePositions.emplace_back(m_pos.x, m_pos.y - i - 1);
    }

    for(uint8_t i = 0; i < maxMovesLeft; i++)
    {
        movablePositions.emplace_back(m_pos.x - i - 1, m_pos.y);
    }

    for(uint8_t i = 0; i < maxMovesUp; i++)
    {
        movablePositions.emplace_back(m_pos.x, m_pos.y + i + 1);
    }

    for(uint8_t i = 0; i < maxMovesRight; i++)
    {
        movablePositions.emplace_back(m_pos.x + i + 1, m_pos.y);
    }

    for(uint8_t i = 0; i < maxMovesDownLeft; i++)
    {
        movablePositions.emplace_back(m_pos.x - i - 1, m_pos.y - i - 1);
    }

    for(uint8_t i = 0; i < maxMovesUpLeft; i++)
    {
        movablePositions.emplace_back(m_pos.x - i - 1, m_pos.y + i + 1);
    }

    for(uint8_t i = 0; i < maxMovesDownRight; i++)
    {
        movablePositions.emplace_back(m_pos.x + i + 1, m_pos.y - i - 1);
    }

    for(uint8_t i = 0; i < maxMovesUpRight; i++)
    {
        movablePositions.emplace_back(m_pos.x + i + 1, m_pos.y + i + 1);
    }

    return movablePositions;
}

std::vector<PiecePos> Bishop::PossibleMoves(std::vector<BasePiece*> piecesOnBoard)
{
    std::vector<PiecePos> movablePositions;
    uint8_t maxMovesDown = m_pos.y;
    uint8_t maxMovesUp = BOARDLENGTH - 1 - m_pos.y;
    uint8_t maxMovesLeft = m_pos.x;
    uint8_t maxMovesRight = BOARDLENGTH - 1 - m_pos.x;
    uint8_t maxMovesDownLeft = std::min(maxMovesDown, maxMovesLeft);
    uint8_t maxMovesUpLeft = std::min(maxMovesUp, maxMovesLeft);
    uint8_t maxMovesDownRight = std::min(maxMovesDown, maxMovesRight);
    uint8_t maxMovesUpRight = std::min(maxMovesUp, maxMovesRight);

    for(auto piece: piecesOnBoard)
    {
        if(piece == this)
        {
            continue;
        }

        int8_t deltaRow = piece->GetPosition().x - m_pos.x;
        int8_t deltaCol = piece->GetPosition().y - m_pos.y;
        uint8_t absDeltaRow = abs(deltaRow);
        uint8_t absDeltaCol = abs(deltaCol);
        
        // Is on one of the diagonals...
        if(absDeltaRow == absDeltaCol)
        {
            bool mayNotCapture = m_color == piece->GetColor();
            uint8_t distance = std::min(absDeltaRow, absDeltaCol) - 1 * mayNotCapture;
            // Piece is on upper left side diagonal of this queen
            if(deltaRow < 0 && deltaCol > 0 && maxMovesUpLeft > distance)
            {
                maxMovesUpLeft = distance;
            }
            // Piece is on lower left side diagonal of this queen
            else if(deltaRow < 0 && deltaCol < 0 && maxMovesDownLeft > distance)
            {
                maxMovesDownLeft = distance;
            }
            else if(deltaRow > 0 && deltaCol > 0 && maxMovesUpRight > distance)
            {
                maxMovesUpRight = distance;
            }
            else if(deltaRow > 0 && deltaCol < 0 && maxMovesDownRight > distance)
            {
                maxMovesDownRight = distance;
            }
        }
    }

    for(uint8_t i = 0; i < maxMovesDownLeft; i++)
    {
        movablePositions.emplace_back(m_pos.x - i - 1, m_pos.y - i - 1);
    }

    for(uint8_t i = 0; i < maxMovesUpLeft; i++)
    {
        movablePositions.emplace_back(m_pos.x - i - 1, m_pos.y + i + 1);
    }

    for(uint8_t i = 0; i < maxMovesDownRight; i++)
    {
        movablePositions.emplace_back(m_pos.x + i + 1, m_pos.y - i - 1);
    }

    for(uint8_t i = 0; i < maxMovesUpRight; i++)
    {
        movablePositions.emplace_back(m_pos.x + i + 1, m_pos.y + i + 1);
    }

    return movablePositions;
}

std::vector<PiecePos> Knight::PossibleMoves(std::vector<BasePiece*> piecesOnBoard)
{
    std::vector<PiecePos> movablePositions;

    if(m_pos.x + 2 < BOARDLENGTH && m_pos.y + 1 < BOARDLENGTH)
    {
        movablePositions.emplace_back(m_pos.x + 2, m_pos.y + 1);
    }

    if(m_pos.x + 2 < BOARDLENGTH && m_pos.y - 1 >= 0)
    {
        movablePositions.emplace_back(m_pos.x + 2, m_pos.y - 1);
    }

    if(m_pos.x - 2 >= 0 && m_pos.y + 1 < BOARDLENGTH)
    {
        movablePositions.emplace_back(m_pos.x - 2, m_pos.y + 1);
    }

    if(m_pos.x - 2 >= 0 && m_pos.y - 1 >= 0)
    {
        movablePositions.emplace_back(m_pos.x - 2, m_pos.y - 1);
    }

    if(m_pos.x + 1 < BOARDLENGTH && m_pos.y + 2 < BOARDLENGTH)
    {
        movablePositions.emplace_back(m_pos.x + 1, m_pos.y + 2);
    }

    if(m_pos.x + 1 < BOARDLENGTH && m_pos.y - 2 >= 0)
    {
        movablePositions.emplace_back(m_pos.x + 1, m_pos.y - 2);
    }

    if(m_pos.x - 1 >= 0 && m_pos.y + 2 < BOARDLENGTH)
    {
        movablePositions.emplace_back(m_pos.x - 1, m_pos.y + 2);
    }

    if(m_pos.x - 1 >= 0 && m_pos.y - 2 >= 0)
    {
        movablePositions.emplace_back(m_pos.x - 1, m_pos.y - 2);
    }

    bool removeMove[8] = {false}; // Knight may at max make 8 moves, allocate mem on stack.
    unsigned int counter = 0;
    for(auto move : movablePositions)
    {
        for(auto piece : piecesOnBoard)
        {
            if(piece == this)
            {
                continue;
            }

            if(piece->GetPosition() == move && piece->GetColor() == m_color)
            {
                removeMove[counter] = true;
                break;
            }
        }
        counter++;
    }

    for(int i = counter - 1; i >= 0; i--)
    {
        if(removeMove[i])
        {
            movablePositions.erase(movablePositions.begin() + i);
        }
    }

    return movablePositions;
}

std::vector<PiecePos> Rook::PossibleMoves(std::vector<BasePiece*> piecesOnBoard)
{
    std::vector<PiecePos> movablePositions;
    uint8_t maxMovesDown = m_pos.y;
    uint8_t maxMovesUp = BOARDLENGTH - 1 - m_pos.y;
    uint8_t maxMovesLeft = m_pos.x;
    uint8_t maxMovesRight = BOARDLENGTH - 1 - m_pos.x;

    for(auto piece: piecesOnBoard)
    {
        if(piece == this)
        {
            continue;
        }
        bool mayNotCapture = m_color == piece->GetColor();
        PiecePos otherPiecePos = piece->GetPosition();
        if(otherPiecePos.x == m_pos.x)
        {
            if(otherPiecePos.y < m_pos.y && m_pos.y - otherPiecePos.y < maxMovesDown)
            {
                maxMovesDown = m_pos.y - otherPiecePos.y - 1 * mayNotCapture;
            }
            if(otherPiecePos.y > m_pos.y && otherPiecePos.y - m_pos.y < maxMovesUp)
            {
                maxMovesUp = otherPiecePos.y - m_pos.y - 1 * mayNotCapture;
            }
        }
        else if(otherPiecePos.y == m_pos.y)
        {
            if(otherPiecePos.x < m_pos.x && m_pos.x - otherPiecePos.x < maxMovesLeft)
            {
                maxMovesLeft = m_pos.x - otherPiecePos.x - 1 * mayNotCapture;
            }
            if(otherPiecePos.x > m_pos.x && otherPiecePos.x - m_pos.x < maxMovesRight)
            {
                maxMovesRight = otherPiecePos.x - m_pos.x - 1 * mayNotCapture;
            }
        }
    }

    for(uint8_t i = 0; i < maxMovesDown; i++)
    {
        movablePositions.emplace_back(m_pos.x, m_pos.y - i - 1);
    }

    for(uint8_t i = 0; i < maxMovesLeft; i++)
    {
        movablePositions.emplace_back(m_pos.x - i - 1, m_pos.y);
    }

    for(uint8_t i = 0; i < maxMovesUp; i++)
    {
        movablePositions.emplace_back(m_pos.x, m_pos.y + i + 1);
    }

    for(uint8_t i = 0; i < maxMovesRight; i++)
    {
        movablePositions.emplace_back(m_pos.x + i + 1, m_pos.y);
    }

    return movablePositions;
}

std::vector<PiecePos> Pawn::PossibleMoves(std::vector<BasePiece*> piecesOnBoard)
{
    std::vector<PiecePos> movablePositions;
    uint8_t colorForwardDir = -(m_color * 2 - 1);
    uint8_t forwardPos = m_pos.y + colorForwardDir;
    uint8_t doubleForwardPos = forwardPos + colorForwardDir;

    bool mayMove = forwardPos < BOARDLENGTH && forwardPos >= 0;
    bool mayMoveDouble = (m_pos.y == 1 && m_color == PieceColor::WHITE) || (m_pos.y == BOARDLENGTH - 2 && m_color == PieceColor::BLACK);

    for (auto piece : piecesOnBoard)
    {
        PiecePos otherPiecePos = piece->GetPosition();
        if (otherPiecePos.y == forwardPos && abs(otherPiecePos.x - m_pos.x) == 1 && piece->GetColor() != m_color)
        {
            movablePositions.emplace_back(otherPiecePos.x, otherPiecePos.y);
        }
        else if (otherPiecePos.y == doubleForwardPos && otherPiecePos.x == m_pos.x)
        {
            mayMoveDouble = false;
        }
        else if(otherPiecePos.y == forwardPos && otherPiecePos.x == m_pos.x)
        {
            mayMove = false;
            mayMoveDouble = false;
        }
    }

    if (mayMove)
    {
        movablePositions.emplace_back(m_pos.x, forwardPos);
    }

    if (mayMoveDouble)
    {
        movablePositions.emplace_back(m_pos.x, doubleForwardPos);
    }

    return movablePositions;
}
