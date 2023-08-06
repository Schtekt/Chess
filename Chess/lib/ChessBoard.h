#include <cstdint>
#include <array>
#include <string>

#include "ChessPiece.h"

class ChessBoard
{
public:
    ChessBoard(bool isWhiteTurn = true);
    uint8_t GetNrOfPossibleMoves(uint8_t x, uint8_t y) const;
    std::array<bool, 64> GetPossibleMoves(uint8_t x, uint8_t y) const;
    bool MakeMove(uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end);
    std::string PrintBoard() const;
    bool AddPiece(uint8_t x, uint8_t y, uint8_t flags); // Adds a piece onto the board where x and y are the actual board coordinates e.g. (A,1)
private:
    std::array<bool, 64> getPossibleMoves(const std::array<uint8_t, 64>& board, size_t pieceIndex, bool checkForCheck = true) const;
    size_t convertChessCoordinateToIndex(uint8_t x, uint8_t y) const;
    std::tuple<uint8_t, uint8_t> convertIndexToChessCoordinate(size_t index) const;
    bool spotIsEligible(uint8_t sourceFlag, uint8_t targetFlag) const;
    bool colorInCheck(ChessPieceColor color, std::array<uint8_t, 64> boardData) const;
    std::array<bool, 64> getSpecificPiecePossibleMoves(const std::array<uint8_t, 64>& board, ChessPieceType pieceType, uint8_t x, uint8_t y) const;
    std::array<bool, 64> getPossibleKingMoves(const std::array<uint8_t, 64>& board, uint8_t x, uint8_t y) const;
    std::array<bool, 64> getPossibleRookMoves(const std::array<uint8_t, 64>& board, uint8_t x, uint8_t y) const;
    std::array<bool, 64> getPossibleBishopMoves(const std::array<uint8_t, 64>& board, uint8_t x, uint8_t y) const;

private:
    std::array<uint8_t, 64> m_boardData;
    bool m_whiteTurn;
};