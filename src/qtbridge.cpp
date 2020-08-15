#include "qtbridge.h"

void QtBridge::activateNextPlayer() {
    callback_();
}

auto QtBridge::endTurn(int index) -> void {
    emit playerFinishedTurn(index);
}
