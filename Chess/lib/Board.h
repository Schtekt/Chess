#include "Pieces/BasePiece.h"

struct Move
{
    Move(PiecePos start, PiecePos end) : start(start), end(end) {}
    bool operator==(const Move& other) const 
    { 
        return start == other.start && end == other.end;
    }
    PiecePos start;
    PiecePos end;
};

class ChessBoard
{
public:
    ChessBoard();
    ~ChessBoard();
    std::string GetBoard() const;
    std::vector<Move> GetPossibleMoves() const;
    PieceColor GetColorTurn() const;
    bool PerformMove(Move move);
    // Perform a move using "Short algebraic Notation"
    bool PerformMove(const std::string& SAN);
    const std::vector<Move>& GetHistory() const;
private:
    void setUpDefaultBoard();
    std::vector<BasePiece*> m_vecPieces;
    std::vector<Move> m_vecHistory;
    PieceColor m_colorTurn;
};