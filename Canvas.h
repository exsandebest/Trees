#ifndef CANVAS_H
#define CANVAS_H
#include <QGraphicsView>


class Canvas : public QGraphicsView{
    Q_OBJECT
public:
    explicit Canvas(int h, int w, QWidget *parent = 0);
protected:
    QGraphicsScene m_scene;
};




#endif // CANVAS_H
