#include "Vertex.h"

Vertex::Vertex(int k, QString colorString, bool isNull) : QGraphicsItem(), key(k), isNull(isNull){
    if (colorString == "avl") {
        color = QColor::fromRgb(50, 205, 50);
    } else if (colorString == "red") {
        color = Qt::red;
    } else if (colorString == "black") {
        color = Qt::black;
    } else if (colorString == "splay"){
        color = QColor::fromRgb(106, 90, 205);
    }
}

Vertex::~Vertex(){}

QRectF Vertex::boundingRect() const {
    return QRectF(0, 0, 50, 50);
}

void Vertex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->translate(25, 25);
    painter->scale(1, -1);
    painter->setBrush(color);

    if (isNull) {
        painter->drawRect(-20, -25, 40, 5);
    } else {
        painter->drawEllipse(-25, -25, 50, 50);
        QPen pen;
        pen.setColor(Qt::white);
        QFont f;
        QString s = QString::number(key);
        int sz = s.length() - 1;
        int x = -4 - 4*sz, y = 5;

        f.setFamily("Trebuchet MS");
        f.setPixelSize(15);

        if (sz > 8) {
            f.setPixelSize(8);
            x = -2*sz - 3;
            y = 3;
        } else if (sz > 7) {
            f.setPixelSize(10);
            x = -2*sz - 6;
            y = 4;
        } else if (sz > 5) {
            f.setPixelSize(12);
            x = -3*sz - 3;
        }

        painter->setFont(f);
        painter->setPen(pen);
        painter->drawText(QPoint(x,y), QString::number(key));
    }
}
