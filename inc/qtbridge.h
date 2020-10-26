#ifndef QTBRIDGE_H
#define QTBRIDGE_H

#include <QObject>
#include <functional>

class QtBridge : public QObject {
    Q_OBJECT

private:
    using Callback = std::function<void(void)>;
    Callback callback_;

public:
    explicit QtBridge(Callback callback, QObject *parent = nullptr)
        : QObject(parent)
        , callback_(callback) {
    }

    auto endTurn(int index) const -> void;
    virtual ~QtBridge() = default;

public slots:
    void activateNextPlayer();

signals:
    void playerFinishedTurn(int index) const;
};

#endif // QTBRIDGE_H
