#include <cstdint>
#include <array>
#include <string>

class ChessBoard
{
public:
    ChessBoard(); // Default setup
    ChessBoard(const std::array<uint8_t, 64>& boardData);

    std::string PrintBoard() const;
private:
    bool addPiece(uint8_t x, uint8_t y, uint8_t flags); // Adds a piece onto the board where x and y are the actual board coordinates e.g. (A,1)
    std::array<uint8_t, 64> m_boardData;
};