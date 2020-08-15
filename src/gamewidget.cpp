#include "gamewidget.h"

#include "figures.h"
#include "qtbridge.h"

#include <QGridLayout>
#include <QMessageBox>
#include <QSignalMapper>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , game_ptr_(new Game()) {
    setUp();
    game_ptr_->launch();
}

auto GameWidget::setUp() -> void {
    QGridLayout *layout = new QGridLayout();

    const auto [rows, columns] = game_ptr_->boardDimension();
    visual_board_.reserve(rows * columns);
    for (std::uint16_t i = 0; i < rows; ++i) {
        for (std::uint16_t j = 0; j < columns; ++j) {
            const int index = 10 * i + j;
            auto button = new QPushButton();
            auto mark = game_ptr_->markAtSpot(index);
            auto enabled = strcmp(mark, "") ? false : true;
            button->setText(mark);
            button->setEnabled(enabled);
            button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            visual_board_.append(button);
            layout->addWidget(button, i, j);
            connect(button, &QPushButton::clicked,
                    [this, index] { humanTurn(index); });
        }
    }
    connectSignals();
    setLayout(layout);
}

void GameWidget::connectSignals() {
    const auto &qtbridge = game_ptr_->qtBridge();
    connect(&qtbridge, &QtBridge::playerFinishedTurn,
            [this](int index) { aiTurn(index); });
    connect(this, &GameWidget::nextPlayer, &qtbridge,
            &QtBridge::activateNextPlayer);
}

auto GameWidget::startNewGame() -> void {
    game_ptr_.reset(new Game());
    const auto [rows, columns] = game_ptr_->boardDimension();
    for (std::uint16_t i = 0; i < rows; ++i) {
        for (std::uint16_t j = 0; j < columns; ++j) {
            const int index = 10 * i + j;
            auto mark = game_ptr_->markAtSpot(index);
            auto enabled = strcmp(mark, "") ? false : true;
            auto index_in_board =
                static_cast<int>(index / 10) * 3 + (index % 10);
            visual_board_[index_in_board]->setText(mark);
            visual_board_[index_in_board]->setEnabled(enabled);
        }
    }
    connectSignals();
    game_ptr_->launch();
}

auto GameWidget::gameOverMessage(const QString &text) -> void {
    QMessageBox msgBox;
    msgBox.setText("GameOver");
    msgBox.setInformativeText(text);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

auto GameWidget::disableVisualBoard() -> void {
    for (auto button : visual_board_) {
        button->setEnabled(false);
    }
}

auto GameWidget::updateGameWidget(int index) -> void {
    auto mark = game_ptr_->markAtSpot(index);
    auto index_in_board = static_cast<int>(index / 10) * 3 + (index % 10);
    visual_board_[index_in_board]->setText(mark);
    visual_board_[index_in_board]->setEnabled(false);
    if (game_ptr_->isGameOver()) {
        disableVisualBoard();
        QString text{game_ptr_->activePlayerName().c_str()};
        QString detailedTxt = QString("Player: %1 won!").arg(text);
        gameOverMessage(detailedTxt);
    } else if (game_ptr_->isBoardFull()) {
        disableVisualBoard();
        QString text{"Draw!"};
        gameOverMessage(text);
    } else {
        emit nextPlayer();
    }
}

auto GameWidget::humanTurn(int index) -> void {
    if (game_ptr_->isHumanPlayerTurn() && game_ptr_->markSpot(index)) {
        updateGameWidget(index);
    }
}

auto GameWidget::aiTurn(int index) -> void {
    if (game_ptr_->isAiPlayerTurn()) {
        updateGameWidget(index);
    }
}
