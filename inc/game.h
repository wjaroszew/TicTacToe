#ifndef GAME_H
#define GAME_H

#include "iplayer.h"
#include "qtbridge.h"

#include <array>
#include <board.h>
#include <memory>
#include <string>

class Game : public std::enable_shared_from_this<Game> {
private:
    using Board_ptr = std::unique_ptr<Board>;
    using Players = std::array<std::unique_ptr<IPlayer>, 2>;
    Board_ptr board_;
    Players players_;
    QtBridge qtbridge_;
    std::uint16_t active_player_index_{0};
    std::uint16_t number_of_players_{0};

public:
    explicit Game();
    auto launch() -> void;
    auto markSpot(int index) -> bool;
    auto markSpot(Board::Spot spot) -> bool;
    auto markAtSpot(int index) const -> const char *;
    auto nextPlayer() -> void;
    auto aiFinishedTurn(Board::Spot spot) -> void;
    auto isGameOver() const -> bool;
    auto isBoardFull() const -> bool;
    auto boardDimension() const -> Board::Spot;
    auto qtBridge() const -> const QtBridge &;
    auto activePlayerName() const -> std::string;
    auto emptyFields() const -> std::vector<Board::Spot>;
    auto isHumanPlayerTurn() const -> bool;
    auto isAiPlayerTurn() const -> bool;
    ~Game() = default;
};

#endif // GAME_H
