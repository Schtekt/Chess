#include "Board.h"

ChessBoard::ChessBoard()
{
    setUpDefaultBoard();
}

ChessBoard::~ChessBoard()
{
    for(auto piece: m_vecPieces)
    {
        delete piece;
        piece = nullptr;
    }
}

std::string ChessBoard::GetBoard() const
{
    uint8_t boardArea = BOARDLENGTH * BOARDLENGTH;
    std::string board;
    board.resize(boardArea);
    for(auto& character : board)
    {
        character = ' ';
    }
    for(auto piece: m_vecPieces)
    {
        uint8_t piecePos = piece->GetPosition().x + (BOARDLENGTH) * (BOARDLENGTH - 1) - piece->GetPosition().y * (BOARDLENGTH);
        board[piecePos] = piece->PieceNotation();
    }
    board[boardArea] = 0;
    std::string formattedBoard;
    formattedBoard += '8';
    for(int i = 0; i < boardArea; i++)
    {
        if(i % BOARDLENGTH == 0 && i != 0)
        {
            formattedBoard += "\n";
            formattedBoard += '8' - i / BOARDLENGTH;
        }
        formattedBoard += board[i];
    }
    formattedBoard += "\n ";
    for(int i = 0; i < BOARDLENGTH; i++)
    {
        formattedBoard += 'A' + i;
    }

    return formattedBoard;
}

std::vector<Move> ChessBoard::GetPossibleMoves() const
{
    std::vector<Move> possibleMoves;
    for(auto piece: m_vecPieces)
    {
        if(piece->GetColor() == m_colorTurn)
        {
            std::vector<PiecePos>& possiblePieceMoves = piece->PossibleMoves(m_vecPieces);

            for(auto possiblePieceMove : possiblePieceMoves)
            {
                possibleMoves.emplace_back(piece->GetPosition(), possiblePieceMove);
            }
        }
    }
    return std::vector<Move>();
}

PieceColor ChessBoard::GetColorTurn() const
{
    return m_colorTurn;
}

bool ChessBoard::PerformMove(Move move)
{
    for(auto piece : m_vecPieces)
    {
        if(piece->GetPosition() == move.start)
        {
            if(piece->GetColor() != m_colorTurn)
            {
                // Error, the piece in that position does not belong to the color whos turn it is!
                return false;
            }

            std::vector<PiecePos>& possibleMoves = piece->PossibleMoves(m_vecPieces);

            for(auto possibleMove : possibleMoves)
            {
                if(move.end == possibleMove)
                {
                    m_vecHistory.emplace_back(move.start, move.end);
                    m_colorTurn = static_cast<PieceColor>((m_colorTurn + 1) % PieceColor::NUM_COLORS);
                    piece->SetPos(move.end.x, move.end.y);
                    return true;
                }
            }

            // Error, the move the piece on the given position is not allowed to move to that position!
            return false;
        }
    }

    // Error, there was no piece on the given start position!
    return false;
}

bool ChessBoard::PerformMove(const std::string& SAN)
{
    // Not implemented, needs a parser first.
    return false;
}

const std::vector<Move> &ChessBoard::GetHistory() const
{
    return m_vecHistory;
}

void ChessBoard::setUpDefaultBoard()
{
    m_colorTurn = PieceColor::WHITE;
    // Pawns
    for(uint8_t i = 0; i < BOARDLENGTH; i++)
    {
        m_vecPieces.emplace_back(new Pawn(i, BOARDLENGTH - 2, PieceColor::BLACK));
        m_vecPieces.emplace_back(new Pawn(i, 1, PieceColor::WHITE));
    }

    // Rooks
    m_vecPieces.emplace_back(new Rook(0, 0, PieceColor::WHITE));
    m_vecPieces.emplace_back(new Rook(BOARDLENGTH - 1, 0, PieceColor::WHITE));
    m_vecPieces.emplace_back(new Rook(0, BOARDLENGTH - 1, PieceColor::BLACK));
    m_vecPieces.emplace_back(new Rook(BOARDLENGTH - 1, BOARDLENGTH - 1, PieceColor::BLACK));

    // Knights
    m_vecPieces.emplace_back(new Knight(1, 0, PieceColor::WHITE));
    m_vecPieces.emplace_back(new Knight(BOARDLENGTH - 2, 0, PieceColor::WHITE));
    m_vecPieces.emplace_back(new Knight(1, BOARDLENGTH - 1, PieceColor::BLACK));
    m_vecPieces.emplace_back(new Knight(BOARDLENGTH - 2, BOARDLENGTH - 1, PieceColor::BLACK));

    // Bishops
    m_vecPieces.emplace_back(new Bishop(2, 0, PieceColor::WHITE));
    m_vecPieces.emplace_back(new Bishop(BOARDLENGTH - 3, 0, PieceColor::WHITE));
    m_vecPieces.emplace_back(new Bishop(2, BOARDLENGTH - 1, PieceColor::BLACK));
    m_vecPieces.emplace_back(new Bishop(BOARDLENGTH - 3, BOARDLENGTH - 1, PieceColor::BLACK));

    // Queens
    m_vecPieces.emplace_back(new Queen(3, 0, PieceColor::WHITE));
    m_vecPieces.emplace_back(new Queen(3, BOARDLENGTH - 1, PieceColor::BLACK));

    // Kings
    m_vecPieces.emplace_back(new King(4, 0, PieceColor::WHITE));
    m_vecPieces.emplace_back(new King(4, BOARDLENGTH - 1, PieceColor::BLACK));
}