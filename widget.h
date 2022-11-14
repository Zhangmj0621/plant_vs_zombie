#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSound>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<grass.h>
#include<QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    QMediaPlayer* player;
    QMediaPlaylist* playerlist;
    Grass* grass[6][10];
    int selectplantnum;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void paintEvent(QPaintEvent *) override;
    //void mousePressEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
