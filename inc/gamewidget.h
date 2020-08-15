#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "game.h"

#include <QPushButton>
#include <QVector>
#include <QWidget>
#include <memory>

class GameWidget : public QWidget {
    Q_OBJECT
private:
    std::shared_ptr<Game> game_ptr_;
    QVector<QPushButton *> visual_board_;

    auto setUp() -> void;
    void connectSignals();
    auto gameOverMessage(const QString &playerName) -> void;
    auto disableVisualBoard() -> void;
    auto updateGameWidget(int index) -> void;

public:
    explicit GameWidget(QWidget *parent = nullptr);

public slots:
    void humanTurn(int index);
    void aiTurn(int index);
    void startNewGame();

signals:
    void nextPlayer();
};

#endif // GAMEWIDGET_H
