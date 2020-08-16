#ifndef BOARD_H
#define BOARD_H

#include "figures.h"

#include <algorithm>
#include <array>
#include <cassert>

class Board {
private:
    using BoardArray = std::array<std::array<Figures, 3>, 3>;
    BoardArray board_;

public:
    using Spot = std::tuple<std::size_t, std::size_t>;
    explicit Board(BoardArray boardArray = BoardArray{{{Figures::Empty}}})
        : board_(boardArray) {
    }

    auto isFull() const -> bool;
    auto threeInARow() const -> bool;
    auto threeInAColumn() const -> bool;
    auto threeInAFirstDiagonal() const -> bool;
    auto threeInASecondDiagona() const -> bool;
    auto isGameOver() const -> bool;
    auto emptyFields() -> std::vector<Spot>;
    auto isSpotEmpty(Spot spot) -> bool;
    auto dimensions() const -> Spot;
    auto markSpot(Spot spot, Figures mark) -> void;
    auto markAtSpot(Spot spot) const -> Figures;
    ~Board() = default;
};

#endif // BOARD_H
