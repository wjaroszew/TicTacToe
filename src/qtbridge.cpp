#include "qtbridge.h"

void QtBridge::activateNextPlayer() {
    callback_();
}

auto QtBridge::endTurn(int index) const -> void {
    emit playerFinishedTurn(index);
}
