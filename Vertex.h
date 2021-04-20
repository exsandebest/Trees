#ifndef VERTEX_H
#define VERTEX_H

#include <QGraphicsItem>
#include <QPainter>

class Vertex : public QGraphicsItem{

public:
    Vertex(int k, QString colorString = "default", bool isNull = false);
    ~Vertex();

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    int key;
    QColor color;
    bool isNull;
};

#endif // VERTEX_H
