#include "computerenemy.h"

auto ComputerEnemy::makeMove() -> void {
    if (auto sp = game_.lock(); sp->isBoardFull() == false) {
        auto spot = strategy_->pickSpot(sp->emptyFields());
        sp->markSpot(spot);
        sp->aiFinishedTurn(spot);
    }
}

auto ComputerEnemy::wakeUp() -> void {
    makeMove();
}
