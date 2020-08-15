#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "figures.h"
#include "iplayer.h"

#include <game.h>
#include <string>

class HumanPlayer : public IPlayer {
public:
    explicit HumanPlayer(GamePtr game, std::string name)
        : IPlayer(game, Figures::X, name, PlayerType::Human) {
    }

    auto wakeUp() -> void override;
    virtual ~HumanPlayer() = default;
};

#endif // HUMANPLAYER_H
