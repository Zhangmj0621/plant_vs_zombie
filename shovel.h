#ifndef SHOVEL_H
#define SHOVEL_H

#include <QObject>
#include <QWidget>

class Shovel : public QWidget
{
    Q_OBJECT
    QString pix;
public:
    //explicit Shovel(QWidget *parent = nullptr);

    Shovel();
    void mousePressEvent(QMouseEvent *ev) override;

    void paintEvent(QPaintEvent *) override;

signals:
    void clickshovel();
};

#endif // SHOVEL_H
