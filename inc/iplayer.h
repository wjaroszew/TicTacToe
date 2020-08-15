#ifndef IPLAYER_H
#define IPLAYER_H

#include "figures.h"

#include <memory>
#include <string>

class Game;
class IPlayer {
public:
    enum class PlayerType { Human = 0, AI = 1 };

protected:
    using GamePtr = std::weak_ptr<Game>;
    GamePtr game_;
    const Figures mark_;
    std::string name_;
    const PlayerType playerType_;

public:
    explicit IPlayer(GamePtr game, Figures mark, std::string name,
                     const PlayerType playerType)
        : game_(game)
        , mark_(mark)
        , name_(name)
        , playerType_(playerType) {
    }

    auto virtual wakeUp() -> void = 0;

    auto mark() const -> Figures {
        return this->mark_;
    }

    auto name() const -> std::string {
        return this->name_;
    }

    auto playerType() const -> PlayerType {
        return playerType_;
    }

    virtual ~IPlayer() = default;
};

#endif // IPLAYER_H
