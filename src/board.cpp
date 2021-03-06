#include "board.h"

#include <cassert>
#include <iomanip>
#include <iostream>

auto Board::isFull() const -> bool {
    auto predicate = [](const auto &board) -> bool {
        for (const auto &row : board) {
            if (std::find(std::begin(row), std::end(row), Figures::Empty) !=
                row.end()) {
                return false;
            }
        }
        return true;
    };

    return predicate(board_);
}

auto Board::threeInARow() const -> bool {
    const auto rows = std::size(board_), columns = std::size(board_[0]);
    for (std::size_t i = 0; i < rows; ++i) {
        auto mark = board_[i][0];
        if (mark == Figures::Empty) {
            continue;
        }

        auto counter = 0;
        for (std::size_t j = 1; j < columns; ++j) {
            if (board_[i][j] == mark) {
            ++counter;
            }
        }

        if (counter == 2) {
            return true;
        }
    }

    return false;
}

auto Board::threeInAColumn() const -> bool {
    const auto rows = std::size(board_), columns = std::size(board_[0]);
    for (std::size_t i = 0; i < rows; ++i) {
        auto mark = board_[0][i];
        if (mark == Figures::Empty) {
            continue;
        }

        auto counter = 0;
        for (std::size_t j = 1; j < columns; ++j) {
            if (board_[j][i] == mark) {
                ++counter;
            }
        }

        if (counter == 2) {
            return true;
        }
    }

    return false;
}

auto Board::threeInAFirstDiagonal() const -> bool {
    const auto rows = std::size(board_);
    auto counter = 0;

    if (auto mark = board_[0][0]; mark != Figures::Empty) {
        for (std::size_t i = 0, j = 0; i < rows; ++i, j = i) {
            if (board_[i][j] == mark) {
                ++counter;
            }
        }
    }

    if (counter == 3) {
        return true;
    }

    return false;
}

auto Board::threeInASecondDiagona() const -> bool {
    const auto rows = std::size(board_), columns = std::size(board_[0]);
    auto counter = 0;

    if (auto mark = board_[0][columns - 1]; mark != Figures::Empty) {
        for (std::size_t i = 0, j = columns - 1; i < rows; ++i, --j) {
            if (board_[i][j] == mark) {
                ++counter;
            }
        }
    }

    if (counter == 3) {
        return true;
    }


    return false;
}

auto Board::isGameOver() const -> bool {
    assert(std::size(board_) > 0 && std::size(board_[0]) > 0);

    return threeInARow() || threeInAColumn() || threeInAFirstDiagonal() || threeInASecondDiagona();
}

auto Board::emptyFields() -> std::vector<Spot> {
    std::vector<Spot> result;
    for (std::size_t i = 0; i < std::size(board_); ++i) {
        for (std::size_t j = 0; j < std::size(board_[i]); ++j) {
            if (board_[i][j] == Figures::Empty) {
                result.emplace_back(std::make_pair(i, j));
            }
        }
    }
    return result;
}

auto Board::isSpotEmpty(Spot spot) -> bool {
    auto [row, col] = spot;
    assert(row <= std::size(board_) && col <= std::size(board_));
    return board_[row][col] == Figures::Empty;
}

auto Board::dimensions() const -> Spot {
    return std::make_tuple(std::size(board_), std::size(board_[0]));
}

auto Board::markSpot(Spot spot, Figures mark) -> void {
    auto [row, col] = spot;
    assert(row <= std::size(board_) && col <= std::size(board_));
    board_[row][col] = mark;
}

auto Board::markAtSpot(Spot spot) const -> Figures {
    auto [row, col] = spot;
    assert(row <= std::size(board_) && col <= std::size(board_));
    return board_[row][col];
}
