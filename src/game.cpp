#include "game.h"

#include "computerenemy.h"
#include "humanplayer.h"

#include <QWidget>
#include <ctime>
#include <string>

Game::Game()
    : board_(new Board())
    , qtbridge_([this] { nextPlayer(); }) {
}

auto Game::launch() -> void {
    auto self = weak_from_this();
    players_[0].reset(new HumanPlayer(self, "Human"));
    players_[1].reset(new ComputerEnemy(self, "HAL"));
    number_of_players_ = std::size(players_);
    std::srand(std::time(nullptr));
    active_player_index_ = std::rand() % number_of_players_;
    players_[active_player_index_]->wakeUp();
}

auto Game::markSpot(int index) -> bool {
    auto spot = std::make_tuple(static_cast<int>(index / 10), index % 10);
    return markSpot(spot);
}

auto Game::markSpot(Board::Spot spot) -> bool {
    if (board_->isSpotEmpty(spot)) {
        auto &current_player = players_[active_player_index_];
        board_->markSpot(spot, current_player->mark());
        return true;
    }

    return false;
}

auto Game::markAtSpot(int index) const -> const char * {
    switch (auto spot =
                std::make_tuple(static_cast<int>(index / 10), index % 10);
            board_->markAtSpot(spot)) {
    case Figures::O:
        return "O";
    case Figures::X:
        return "X";
    case Figures::Empty:
        return "";
    }
    return "";
}

auto Game::nextPlayer() -> void {
    active_player_index_ = (active_player_index_ + 1) % number_of_players_;
    players_[active_player_index_]->wakeUp();
}

auto Game::aiFinishedTurn(Board::Spot spot) -> void {
    auto [x, y] = spot;
    qtbridge_.endTurn(x * 10 + y);
}

auto Game::isGameOver() const -> bool {
    return board_->isGameOver();
}

auto Game::isBoardFull() const -> bool {
    return board_->isFull();
}

auto Game::boardDimension() const -> Board::Spot {
    return board_->dimensions();
}

auto Game::qtBridge() const -> const QtBridge & {
    return qtbridge_;
}

auto Game::activePlayerName() const -> std::string {
    return players_[active_player_index_]->name();
}

auto Game::emptyFields() const -> std::vector<Board::Spot> {
    return board_->emptyFields();
}

auto Game::isHumanPlayerTurn() const -> bool {
    return players_[active_player_index_]->playerType() ==
           IPlayer::PlayerType::Human;
}

auto Game::isAiPlayerTurn() const -> bool {
    return players_[active_player_index_]->playerType() ==
           IPlayer::PlayerType::AI;
}
