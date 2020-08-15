#ifndef COMPUTERENEMY_H
#define COMPUTERENEMY_H

#include "figures.h"
#include "game.h"
#include "iplayer.h"

#include <ctime>
#include <memory>
#include <random>
#include <string>

class ComputerEnemy : public IPlayer {
private:
    class RandomStrategy {
    private:
        using Dimensions = std::tuple<std::size_t, std::size_t>;

    public:
        auto pickSpot(const std::vector<Dimensions> &vec) {
            srand(std::time(nullptr));
            return vec.at(rand() % std::size(vec));
        }

        RandomStrategy() = default;
        ~RandomStrategy() = default;
    };

    std::unique_ptr<RandomStrategy> strategy_;

    auto makeMove() -> void;

public:
    explicit ComputerEnemy(GamePtr game, std::string name)
        : IPlayer(game, Figures::O, name, PlayerType::AI)
        , strategy_(new RandomStrategy()) {
    }

    auto wakeUp() -> void override;
    virtual ~ComputerEnemy() = default;
};

#endif // COMPUTERENEMY_H
